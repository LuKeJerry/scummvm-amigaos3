#ifndef RONINCD_FILESYSTEM_FACTORY_H
#define RONINCD_FILESYSTEM_FACTORY_H

#include "backends/fs/abstract-fs-factory.h"

/**
 * Creates RoninCDFilesystemNode objects.
 * 
 * Parts of this class are documented in the base interface class, AbstractFilesystemFactory.
 */
class RoninCDFilesystemFactory : public AbstractFilesystemFactory, public Common::Singleton<RoninCDFilesystemFactory> {	
public:
	typedef Common::String String;
		
	virtual AbstractFilesystemNode *makeRootFileNode() const;
	virtual AbstractFilesystemNode *makeCurrentDirectoryFileNode() const;
	virtual AbstractFilesystemNode *makeFileNodePath(const String &path) const;
	
protected:
	RoninCDFilesystemFactory() {};
		
private:
	friend class Common::Singleton<SingletonBaseType>;
};

#endif /*RONINCD_FILESYSTEM_FACTORY_H*/
