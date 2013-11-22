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
	/*
	wchar_t temp[200] = L"";
	wcscat_s(temp, buffer);

	//convert from wide char to narrow char array
	char ch[200];
	char DefChar = ' ';
	WideCharToMultiByte(CP_ACP,0,temp,-1, ch,200,&DefChar, NULL);
    
	//A std:string  using the char* constructor.
	std::string ss(ch);

	ss += "\\" + partialPath +"\\";

	delete[] buffer;
	return ss;*/
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
	/*
	//Convert string to LPCWSTR
	int len;
    int slength = (int)path.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, path.c_str(), slength, 0, 0); 
    wchar_t* buffer = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, path.c_str(), slength, buffer, len);
    wstring wstrPath(buffer);
	LPCWSTR lpcwPath = wstrPath.c_str();
    delete[] buffer;

	DWORD ftyp = GetFileAttributesW(lpcwPath);

	//Creates a folder if it does not exist
	if (ftyp == INVALID_FILE_ATTRIBUTES)
	{
		_wmkdir(lpcwPath);
	}
	else if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
	{
		//this already is a directory
	}*/
	

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
