/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */


#include "sci/engine/kernel.h"
#include "sci/engine/object.h"
#include "sci/engine/seg_manager.h"
#ifdef ENABLE_SCI32
#include "sci/engine/features.h"
#endif

namespace Sci {

extern bool relocateBlock(Common::Array<reg_t> &block, int block_location, SegmentId segment, int location, uint32 heapOffset);


void Object::init(const SciSpan<const byte> &buf, reg_t obj_pos, bool initVariables) {
	const SciSpan<const byte> data = buf.subspan(obj_pos.getOffset());
	_baseObj = data;
	_pos = obj_pos;

	if (getSciVersion() <= SCI_VERSION_1_LATE) {
		const SciSpan<const byte> header = buf.subspan(obj_pos.getOffset() - kOffsetHeaderSize);
		_variables.resize(header.getUint16LEAt(kOffsetHeaderSelectorCounter));

		// Non-class objects do not have a baseVars section
		const uint16 infoSelector = data.getUint16SEAt((_offset + 2) * sizeof(uint16));
		if (infoSelector & kInfoFlagClass) {
			_baseVars.reserve(_variables.size());
			uint baseVarsOffset = _variables.size() * sizeof(uint16);
			for (uint i = 0; i < _variables.size(); ++i) {
				_baseVars.push_back(data.getUint16SEAt(baseVarsOffset));
				baseVarsOffset += sizeof(uint16);
			}
		}

		_methodCount = data.getUint16LEAt(header.getUint16LEAt(kOffsetHeaderFunctionArea) - 2);
		for (uint i = 0; i < _methodCount * sizeof(uint16) + 2; ++i) {
			_baseMethod.push_back(data.getUint16SEAt(header.getUint16LEAt(kOffsetHeaderFunctionArea) + i * sizeof(uint16)));
		}
	} else if (getSciVersion() >= SCI_VERSION_1_1 && getSciVersion() <= SCI_VERSION_2_1_LATE) {
		_variables.resize(data.getUint16SEAt(2));

		// Non-class objects do not have a baseVars section
		const uint16 infoSelector = data.getUint16SEAt((_offset + 2) * sizeof(uint16));
		if (infoSelector & kInfoFlagClass) {
			_baseVars.reserve(_variables.size());
			uint baseVarsOffset = data.getUint16SEAt(4);
			for (uint i = 0; i < _variables.size(); ++i) {
				_baseVars.push_back(buf.getUint16SEAt(baseVarsOffset));
				baseVarsOffset += sizeof(uint16);
			}
		}

		_methodCount = buf.getUint16SEAt(data.getUint16SEAt(6));
		for (uint i = 0; i < _methodCount * sizeof(uint16) + 3; ++i) {
			_baseMethod.push_back(buf.getUint16SEAt(data.getUint16SEAt(6) + i * sizeof(uint16)));
		}
#ifdef ENABLE_SCI32
	} else if (getSciVersion() == SCI_VERSION_3) {
		initSelectorsSci3(buf, initVariables);
#endif
	}

	if (initVariables) {
#ifdef ENABLE_SCI32
		if (getSciVersion() == SCI_VERSION_3) {
			_infoSelectorSci3 = make_reg(0, data.getUint16SEAt(10));
		} else {
#else
		{
#endif
			for (uint i = 0; i < _variables.size(); i++)
				_variables[i] = make_reg(0, data.getUint16SEAt(i * sizeof(uint16)));
		}
	}
}

const Object *Object::getClass(SegManager *segMan) const {
	return isClass() ? this : segMan->getObject(getSuperClassSelector());
}

int Object::locateVarSelector(SegManager *segMan, Selector slc) const {
	const Common::Array<uint16> *buf;
	uint varCount;

#ifdef ENABLE_SCI32
	if (getSciVersion() == SCI_VERSION_3) {
		buf = &_baseVars;
		varCount = getVarCount();
	} else {
#else
	{
#endif
		const Object *obj = getClass(segMan);
		buf = &obj->_baseVars;
		varCount = obj->getVarCount();
	}

	for (uint i = 0; i < varCount; i++)
		if ((*buf)[i] == slc) // Found it?
			return i; // report success

	return -1; // Failed
}

bool Object::relocateSci0Sci21(SegmentId segment, int location, size_t scriptSize) {
	return relocateBlock(_variables, getPos().getOffset(), segment, location, scriptSize);
}

#ifdef ENABLE_SCI32
bool Object::relocateSci3(SegmentId segment, uint32 location, int offset, size_t scriptSize) {
	assert(_propertyOffsetsSci3.size());
	assert(offset >= 0 && (uint)offset < scriptSize);

	for (uint i = 0; i < _variables.size(); ++i) {
		if (location == _propertyOffsetsSci3[i]) {
			_variables[i].setSegment(segment);
			_variables[i].incOffset(offset);
			return true;
		}
	}

	return false;
}
#endif

int Object::propertyOffsetToId(SegManager *segMan, int propertyOffset) const {
	int selectors = getVarCount();

	if (propertyOffset < 0 || (propertyOffset >> 1) >= selectors) {
		error("Applied propertyOffsetToId to invalid property offset %x (property #%d not in [0..%d])",
		          propertyOffset, propertyOffset >> 1, selectors - 1);
		return -1;
	}

	if (getSciVersion() < SCI_VERSION_1_1) {
		const SciSpan<const byte> selectoroffset = _baseObj.subspan(kOffsetSelectorSegment + selectors * 2);
		return selectoroffset.getUint16SEAt(propertyOffset);
	} else {
		const Object *obj = this;
		if (!isClass())
			obj = segMan->getObject(getSuperClassSelector());

		return obj->_baseVars[propertyOffset >> 1];
	}
}

void Object::initSpecies(SegManager *segMan, reg_t addr) {
	uint16 speciesOffset = getSpeciesSelector().getOffset();

	if (speciesOffset == 0xffff)		// -1
		setSpeciesSelector(NULL_REG);	// no species
	else
		setSpeciesSelector(segMan->getClassAddress(speciesOffset, SCRIPT_GET_LOCK, addr.getSegment()));
}

void Object::initSuperClass(SegManager *segMan, reg_t addr) {
	uint16 superClassOffset = getSuperClassSelector().getOffset();

	if (superClassOffset == 0xffff)			// -1
		setSuperClassSelector(NULL_REG);	// no superclass
	else
		setSuperClassSelector(segMan->getClassAddress(superClassOffset, SCRIPT_GET_LOCK, addr.getSegment()));
}

bool Object::initBaseObject(SegManager *segMan, reg_t addr, bool doInitSuperClass) {
	const Object *baseObj = segMan->getObject(getSpeciesSelector());

	if (baseObj) {
		uint originalVarCount = _variables.size();

		if (_variables.size() != baseObj->getVarCount())
			_variables.resize(baseObj->getVarCount());
		// Copy base from species class, as we need its selector IDs
		_baseObj = baseObj->_baseObj;
		assert(_baseObj);
		if (doInitSuperClass)
			initSuperClass(segMan, addr);

		if (_variables.size() != originalVarCount) {
			// These objects are probably broken.
			// An example is 'witchCage' in script 200 in KQ5 (#3034714),
			// but also 'girl' in script 216 and 'door' in script 22.
			// In LSL3 a number of sound objects trigger this right away.
			// SQ4-floppy's bug #3037938 also seems related.

			// The effect is that a number of its method selectors may be
			// treated as variable selectors, causing unpredictable effects.
			int objScript = segMan->getScript(_pos.getSegment())->getScriptNumber();

			// We have to do a little bit of work to get the name of the object
			// before any relocations are done.
			reg_t nameReg = getNameSelector();
			const char *name;
			if (nameReg.isNull()) {
				name = "<no name>";
			} else {
				nameReg.setSegment(_pos.getSegment());
				name = segMan->derefString(nameReg);
				if (!name)
					name = "<invalid name>";
			}

			debugC(kDebugLevelVM, "Object %04x:%04x (name %s, script %d) "
			        "varnum doesn't match baseObj's: obj %d, base %d",
			        PRINT_REG(_pos), name, objScript,
			        originalVarCount, baseObj->getVarCount());

#if 0
			// We enumerate the methods selectors which could be hidden here
			if (getSciVersion() <= SCI_VERSION_2_1) {
				const SegmentRef objRef = segMan->dereference(baseObj->_pos);
				assert(objRef.isRaw);
				uint segBound = objRef.maxSize/2 - baseObj->getVarCount();
				const byte* buf = (const byte *)baseObj->_baseVars;
				if (!buf) {
					// While loading this may happen due to objects being loaded
					// out of order, and we can't proceed then, unfortunately.
					segBound = 0;
				}
				for (uint i = baseObj->getVarCount();
				         i < originalVarCount && i < segBound; ++i) {
					uint16 slc = READ_SCI11ENDIAN_UINT16(buf + 2*i);
					// Skip any numbers which happen to be varselectors too
					bool found = false;
					for (uint j = 0; j < baseObj->getVarCount() && !found; ++j)
						found = READ_SCI11ENDIAN_UINT16(buf + 2*j) == slc;
					if (found) continue;
					// Skip any selectors which aren't method selectors,
					// so couldn't be mistaken for varselectors
					if (lookupSelector(segMan, _pos, slc, 0, 0) != kSelectorMethod) continue;
					warning("    Possibly affected selector: %02x (%s)", slc,
					        g_sci->getKernel()->getSelectorName(slc).c_str());
				}
			}
#endif
		}

		return true;
	}

	return false;
}

#ifdef ENABLE_SCI32
bool Object::mustSetViewVisible(int index, const bool fromPropertyOp) const {
	if (getSciVersion() == SCI_VERSION_3) {
		// In SCI3, visible flag lookups are based on selectors

		if (!fromPropertyOp) {
			// varindexes must be converted to selectors
			index = getVarSelector(index);
		}

		if (index == -1) {
			error("Selector %d is invalid for object %04x:%04x", index, PRINT_REG(_pos));
		}

		return _mustSetViewVisible[index >> 5];
	} else {
		// In SCI2, visible flag lookups are based on varindexes

		if (fromPropertyOp) {
			// property offsets must be converted to varindexes
			assert((index % 2) == 0);
			index >>= 1;
		}

		int minIndex, maxIndex;
		if (g_sci->_features->usesAlternateSelectors()) {
			minIndex = 24;
			maxIndex = 43;
		} else {
			minIndex = 26;
			maxIndex = 44;
		}

		return index >= minIndex && index <= maxIndex;
	}
}

void Object::initSelectorsSci3(const SciSpan<const byte> &buf, const bool initVariables) {
	enum {
		kExtraGroups = 3,
		kGroupSize   = 32
	};

	const SciSpan<const byte> groupInfo = _baseObj.subspan(16);
	const SciSpan<const byte> selectorBase = groupInfo.subspan(kExtraGroups * kGroupSize * sizeof(uint16));

	int numGroups = g_sci->getKernel()->getSelectorNamesSize() / kGroupSize;
	if (g_sci->getKernel()->getSelectorNamesSize() % kGroupSize)
		++numGroups;

	_mustSetViewVisible.resize(numGroups);

	int numMethods = 0;
	int numProperties = 0;

	// Selectors are divided into groups of 32, of which the first
	// two selectors are always reserved (because their storage
	// space is used by the typeMask).
	// We don't know beforehand how many methods and properties
	// there are, so we count them first.
	for (int groupNr = 0; groupNr < numGroups; ++groupNr) {
		byte groupLocation = groupInfo[groupNr];
		const SciSpan<const byte> seeker = selectorBase.subspan(groupLocation * kGroupSize * sizeof(uint16));

		if (groupLocation != 0)	{
			// This object actually has selectors belonging to this group
			int typeMask = seeker.getUint32SEAt(0);

			_mustSetViewVisible[groupNr] = (typeMask & 1);

			for (int bit = 2; bit < kGroupSize; ++bit) {
				int value = seeker.getUint16SEAt(bit * sizeof(uint16));
				if (typeMask & (1 << bit)) { // Property
					++numProperties;
				} else if (value != 0xffff) { // Method
					++numMethods;
				} else {
					// Undefined selector
				}
			}
		} else
			_mustSetViewVisible[groupNr] = false;
	}

	_methodCount = numMethods;
	_variables.resize(numProperties);
	_baseVars.resize(numProperties);
	_propertyOffsetsSci3.resize(numProperties);

	// Go through the whole thing again to get the property values
	// and method pointers
	int propertyCounter = 0;
	for (int groupNr = 0; groupNr < numGroups; ++groupNr) {
		byte groupLocation = groupInfo[groupNr];
		const SciSpan<const byte> seeker = selectorBase.subspan(groupLocation * kGroupSize * sizeof(uint16));

		if (groupLocation != 0)	{
			// This object actually has selectors belonging to this group
			int typeMask = seeker.getUint32SEAt(0);
			int groupBaseId = groupNr * kGroupSize;

			for (int bit = 2; bit < kGroupSize; ++bit) {
				int value = seeker.getUint16SEAt(bit * sizeof(uint16));
				if (typeMask & (1 << bit)) { // Property
					_baseVars[propertyCounter] = groupBaseId + bit;
					if (initVariables) {
						_variables[propertyCounter] = make_reg(0, value);
					}
					uint32 propertyOffset = (seeker + bit * sizeof(uint16)) - buf;
					_propertyOffsetsSci3[propertyCounter] = propertyOffset;
					++propertyCounter;
				} else if (value != 0xffff) { // Method
					_baseMethod.push_back(groupBaseId + bit);
					const uint32 offset = value + buf.getUint32SEAt(0);
					assert(offset <= kOffsetMask);
					_baseMethod.push_back(offset);
				} else {
					// Undefined selector
				}
			}
		}
	}

	if (initVariables) {
		_speciesSelectorSci3 = make_reg(0, _baseObj.getUint16SEAt(4));
		_superClassPosSci3 = make_reg(0, _baseObj.getUint16SEAt(8));
	}
}
#endif

} // End of namespace Sci
