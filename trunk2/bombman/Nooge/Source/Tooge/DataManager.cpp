#include "DataManager.h"

#define MAX 30

std::string& DataManager::GetDataPath(const char* appName,const char* keyName,const char* iniName)
{
	char path[MAX];
	GetPrivateProfileStringA(appName,keyName,path,"null",sizeof(path),iniName);

	std::string spath(path);
	return spath;
}

