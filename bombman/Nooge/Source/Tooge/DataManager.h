#pragma once

#include "windows.h"
#include <string>

class DataManager
{
public:
	static std::string& GetDataPath(const char* appName,const char* keyName,const char* iniName);
private:
};