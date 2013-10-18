#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <wchar.h>

#include "Testing.h"
#include "sf_sdk_session.h"

#ifdef _SF_TEST_MAIN

SF::SF_Session *session;


int wmain(int argc, WCHAR* argv[]) {
	//This is test code to verify proper operation.
	//This will later be replaced by the program flow control code.
	session = new SF::SF_Session();
	if(!(session->createSession())){
        wprintf_s(L"Failed to create a session\n");
        return 3;
    }

	if(!(session->setOptions(argc, argv))){
        wprintf_s(L"Failed to set cmdln options\n");
        return 3;
	}


    return 0;
}
#endif //_SF_TEST_MAIN