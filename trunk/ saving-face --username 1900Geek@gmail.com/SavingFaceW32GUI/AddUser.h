#ifndef SF_ADDUSER						// if we haven't included this file ...
#define SF_ADDUSER						// define so we know we have included this file.

//GUI Defines
#define IDC_MAIN_BUTTON	101			// Button identifier
#define IDC_MAIN_EDIT	102			// Edit box identifier

// include files
#include <windows.h>					// standard windows library files
#include "resource.h"					// access to the dialogs in the resource file

// function prototypes
INT_PTR CALLBACK AddUserProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);// message processing for our dialogbox

#endif //SF_ADDUSER
