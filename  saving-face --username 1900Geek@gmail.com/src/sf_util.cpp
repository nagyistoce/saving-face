#include "sf_util.h"
#include <windows.h>

//should take an argument and return
//Working directory + "\\partialPath\\"
string sf_util::getFullPath()
{
	//Should calculate the path
	return path;
}

//Would rewrite to include partial path...
//Ex makeDirectory("database")
//That way we can have seperate directories for testing and actual use.
//Multiple Databases.
//Should have a wrapper call to getFull("database") that returns the path.
//No need to store the path.
void sf_util::makeDirectory()
{
	wchar_t* buffer;

	// Gets the current working directory  
	buffer = _wgetcwd( NULL, 0 );
			
	//append full file path onto temp
	wchar_t temp[200] = L"";
	wcscat_s(temp, buffer);
	wcscat_s(temp, L"\\database\\");//Hard-coding is bad practice.
	//Instead call getFullPath(partialPath);

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
	path = ss;//No need to store.
	//However making a global macro in sf_defs for DEFAULT_DB_PATH is fine.
	//Probably add one for a testing path as well.

	delete temp;
	delete ch;
}