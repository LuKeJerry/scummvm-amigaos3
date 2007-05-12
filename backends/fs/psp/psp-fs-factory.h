#ifndef PSP_FILESYSTEM_FACTORY_H
#define PSP_FILESYSTEM_FACTORY_H

#include "backends/fs/abstract-fs-factory.h"

/**
 * Creates PSPFilesystemNode objects.
 * 
 * Parts of this class are documented in the base interface class, AbstractFilesystemFactory.
 */
class PSPFilesystemFactory : public AbstractFilesystemFactory, public Common::Singleton<PSPFilesystemFactory> {	
public:
	typedef Common::String String;
		
	virtual AbstractFilesystemNode *makeRootFileNode() const;
	virtual AbstractFilesystemNode *makeCurrentDirectoryFileNode() const;
	virtual AbstractFilesystemNode *makeFileNodePath(const String &path) const;
	
protected:
	PSPFilesystemFactory() {};
		
private:
	friend class Common::Singleton<SingletonBaseType>;
};

#endif /*PSP_FILESYSTEM_FACTORY_H*/
