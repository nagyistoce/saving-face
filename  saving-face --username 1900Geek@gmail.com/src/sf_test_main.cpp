#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <wchar.h>
#include "Testing.h"
#include "sf_sdk_session.h"
#include "sf_model_builder.h"

#ifdef _SF_TEST_MAIN

SF::SF_Session *session;
SF::sf_model_builder *modelBuilder;



int wmain(int argc, WCHAR* argv[]) {
	//Note:: TODO for later
	//create dialog that on error prints the error and error code along with line number and file
	//name. Then exits gracefully.


	//This is test code to verify proper operation.
	//This will later be replaced by the program flow control code.
	//Which can be controlled by case statements.

	//For simplicity the control code will be implemented in C++ and only necessary function calls
	//will be made from c#.
	session = new SF::SF_Session();
	modelBuilder = new SF::sf_model_builder();

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
	session->createColorRenderView();
	session->loadFaceModule();
	session->tempMainLoop();

	modelBuilder->tempTestingModule();

    return 0;
}

#endif //_SF_TEST_MAIN