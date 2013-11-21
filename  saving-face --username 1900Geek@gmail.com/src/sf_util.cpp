#include "sf_util.h"
#include <windows.h>

string sf_util::getFullPath()
{
	return path;
}

void sf_util::makeDirectory()
{
	wchar_t* buffer;

	// Gets the current working directory  
	buffer = _wgetcwd( NULL, 0 );
			
	//append full file path onto temp
	wchar_t temp[200] = L"";
	wcscat_s(temp, buffer);
	wcscat_s(temp, L"\\database\\");

	DWORD ftyp = GetFileAttributesW(temp);
	delete[] buffer;

	//Creates a folder if it does not exist
	if (ftyp == INVALID_FILE_ATTRIBUTES)
	{
		_wmkdir(temp);
	}
	else if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
	{
		//this already is a directory
	}

	//convert from wide char to narrow char array
	char ch[200];
	char DefChar = ' ';
	WideCharToMultiByte(CP_ACP,0,temp,-1, ch,200,&DefChar, NULL);
    
	//A std:string  using the char* constructor.
	std::string ss(ch);

	//store string to private path variable for later acces
	path = ss;

	delete temp;
	delete ch;
}