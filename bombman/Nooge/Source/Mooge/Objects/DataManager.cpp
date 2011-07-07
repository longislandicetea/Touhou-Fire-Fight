#include "DataManager.h"

#define MAX 30

std::string DataManager::GetDataPath(const char* appName,const char* keyName,const char* iniName)
{
	char path[MAX];
	GetPrivateProfileStringA(appName,keyName,"null",path,sizeof(path),iniName);

	//CString path;

	std::string spath(path);
	return spath;
}

