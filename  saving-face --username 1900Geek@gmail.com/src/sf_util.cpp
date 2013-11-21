#include "sf_util.h"
#include <windows.h>

//Appends the partial path onto the current working directory
string sf_util::getFullPath(string partialPath)
{
	wchar_t* buffer;

	//gets current working directory
	buffer = _wgetcwd( NULL, 0 );

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
	return ss;
}

//Creates a directory give a partial path as a string.
void sf_util::makeDirectory(string partialPath)
{
			
	string path = getFullPath(partialPath);

	//Convert string to LPCWSTR
	int len;
    int slength = (int)path.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, path.c_str(), slength, 0, 0); 
    wchar_t* buffer = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, path.c_str(), slength, buf, len);
    LPCWSTR lpcwPath(buf);
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
	}

	delete[] lpcwPath;
}