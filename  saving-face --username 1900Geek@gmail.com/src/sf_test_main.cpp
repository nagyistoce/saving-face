#include <fstream>
#include <sstream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <wchar.h>
#include <vector>
#include "pxcsession.h" //Required To Make Session
#include "pxcsmartptr.h" //Smart pointers for memory management
#include "pxccapture.h" //For Capture Instance
#include "util_render.h" //To Render Image
#include "util_capture.h" 
#include "util_cmdline.h"
#include "pxcprojection.h" //To Project Coords to Real-Life and to map depth to image
#include "pxcmetadata.h"
#include "Testing.h"
#include "sf_sdk_session.h"

#ifndef _SF_TEST_MAIN

SF::SF_Session *session;


int wmain(int argc, WCHAR* argv[]) {
	session = new SF::SF_Session();

    return 0;
}
#endif //_SF_TEST_MAIN