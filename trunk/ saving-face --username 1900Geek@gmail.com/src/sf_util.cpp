#include "sf_util.h"
#include <windows.h>
#include <direct.h>

//Note keeping with the full path for the moment because we where already doing it.
//Would also work with partial paths only.


//Appends the partial path onto the current working directory
const string SF::getFullPath(string const partialPath)
{
	string fullPath = _getcwd(NULL, 0);
	fullPath += "\\" + partialPath + "\\";
	return fullPath;
}

bool SF::doesDirectoryExist(string const fullPath)
{
	if (GetFileAttributesA(fullPath.c_str()) == INVALID_FILE_ATTRIBUTES)
		return false;
	else return true;
}

//Creates a directory give a partial path as a string.
SF_STS SF::makeDirectory(string const partialPath)
{
			
	string path = getFullPath(partialPath);
	if(doesDirectoryExist(path))
		return SF_STS_OK;
	else
		if(_mkdir(path.c_str()) == 0)
			return SF_STS_OK;
	return SF_STS_FAIL;
}
	
SF_STS SF::removeDirectory(string const partialPath)
{
	string path = getFullPath(partialPath);
	if(!doesDirectoryExist(path))
		return SF_STS_OK;
	else
		if(_rmdir(path.c_str()) == 0)
			return SF_STS_OK;
	return SF_STS_FAIL;
}
