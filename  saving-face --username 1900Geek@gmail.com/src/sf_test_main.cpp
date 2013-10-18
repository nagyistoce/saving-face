#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <wchar.h>

#include "Testing.h"
#include "sf_sdk_session.h"

#ifdef _SF_TEST_MAIN

SF::SF_Session *session;


int wmain(int argc, WCHAR* argv[]) {
	//Note:: TODO for later
	//create dialog that on error prints the error and error code along with line number and file
	//name. Then exits gracefully.


	//This is test code to verify proper operation.
	//This will later be replaced by the program flow control code.
	//Which can be controlled by case statements.
	session = new SF::SF_Session();
	if(!(session->createSession())){
        wprintf_s(L"Failed to create a session\n");
        return 3;
    }
	if(!(session->setOptions(argc, argv))){
        wprintf_s(L"Failed to set cmdln options\n");
        return 3;
	}

	if(!(session->captureStreams())){
        return 3;
	}

	session->createDepthRenderView();
	session->tempMainLoop();


	


    return 0;
}
#endif //_SF_TEST_MAIN