#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <wchar.h>

#include "Testing.h"
#include "sf_sdk_session.h"

#ifndef _SF_TEST_MAIN

SF::SF_Session *session;


int wmain(int argc, WCHAR* argv[]) {
	session = new SF::SF_Session();

    return 0;
}
#endif //_SF_TEST_MAIN