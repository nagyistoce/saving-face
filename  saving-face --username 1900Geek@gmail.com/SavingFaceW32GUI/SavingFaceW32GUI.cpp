// SavingFaceW32GUI.cpp : Defines the entry point for the application.
//

#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "SavingFaceW32GUI.h"
#include "GlobalVars.h"
#include "AddUser.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

//ComboBoxItems
const char *SalutationItems[] = { "Dr.", "Sir", "Mr.", "Mrs.", "Ms." };
const char *SuffixItems[] = {"Sr.", "Jr.", "I", "II", "III", "IV", "V" };
const char *GenderItems[] = {"Female","Male","Not Given"};


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SAVINGFACEW32GUI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SAVINGFACEW32GUI));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SAVINGFACEW32GUI));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_SAVINGFACEW32GUI);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SAVINGFACEW32GUI));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	savingFace = new sf_controller();
	savingFace->init();

   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
HWND SubDlgHwnd;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(SF_ABOUT_DIALOG), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_ACTIONS_CREATEANEWMODEL:
			DialogBox(hInst, MAKEINTRESOURCE(UDI_DIALOG2), hWnd, UDI_CALLBACK);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void createUserWindow()
{

}

INT_PTR CALLBACK UDI_CALLBACK(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		//Init Combo boxes here
		if ( -1 == SendMessage(GetDlgItem(hDlg, UDI_SALUTATION_CB),  CB_ADDSTRING , 0, reinterpret_cast<LPARAM>((LPCTSTR)SalutationItems[0])))
		{
			MessageBox(hDlg, LPCSTR("Failed to add item to combo box."), LPCSTR("Adding Person Dialog"), MB_OK);
		}
		SendMessage(GetDlgItem(hDlg, UDI_SALUTATION_CB), CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)SalutationItems[1]));
		SendMessage(GetDlgItem(hDlg, UDI_SALUTATION_CB), CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)SalutationItems[2]));
		SendMessage(GetDlgItem(hDlg, UDI_SALUTATION_CB), CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)SalutationItems[3]));
		SendMessage(GetDlgItem(hDlg, UDI_SALUTATION_CB), CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)SalutationItems[4]));

		if ( -1 == SendMessage(GetDlgItem(hDlg, UDI_SUFFIX_CB),  CB_ADDSTRING , 0, reinterpret_cast<LPARAM>((LPCTSTR)SuffixItems[0])))
		{
			MessageBox(hDlg, LPCSTR("Failed to add item to combo box."), LPCSTR("Adding Person Dialog"), MB_OK);
		}
		SendMessage(GetDlgItem(hDlg, UDI_SUFFIX_CB),  CB_ADDSTRING , 0, reinterpret_cast<LPARAM>((LPCTSTR)SuffixItems[1]));
		SendMessage(GetDlgItem(hDlg, UDI_SUFFIX_CB),  CB_ADDSTRING , 0, reinterpret_cast<LPARAM>((LPCTSTR)SuffixItems[2]));
		SendMessage(GetDlgItem(hDlg, UDI_SUFFIX_CB),  CB_ADDSTRING , 0, reinterpret_cast<LPARAM>((LPCTSTR)SuffixItems[3]));
		SendMessage(GetDlgItem(hDlg, UDI_SUFFIX_CB),  CB_ADDSTRING , 0, reinterpret_cast<LPARAM>((LPCTSTR)SuffixItems[4]));
		SendMessage(GetDlgItem(hDlg, UDI_SUFFIX_CB),  CB_ADDSTRING , 0, reinterpret_cast<LPARAM>((LPCTSTR)SuffixItems[5]));
		SendMessage(GetDlgItem(hDlg, UDI_SUFFIX_CB),  CB_ADDSTRING , 0, reinterpret_cast<LPARAM>((LPCTSTR)SuffixItems[6]));

		if ( -1 == SendMessage(GetDlgItem(hDlg, UDI_GENDER_CB),  CB_ADDSTRING , 0, reinterpret_cast<LPARAM>((LPCTSTR)GenderItems[0])))
		{
			MessageBox(hDlg, LPCSTR("Failed to add item to combo box."), LPCSTR("Adding Person Dialog"), MB_OK);
		}

		SendMessage(GetDlgItem(hDlg, UDI_GENDER_CB),  CB_ADDSTRING , 0, reinterpret_cast<LPARAM>((LPCTSTR)GenderItems[1]));
		SendMessage(GetDlgItem(hDlg, UDI_GENDER_CB),  CB_ADDSTRING , 0, reinterpret_cast<LPARAM>((LPCTSTR)GenderItems[2]));
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == UDI_OK)
		{
			

			char* sal = new char[200];
			char* first = new char[200];
			char* middle = new char[200];
			char* last = new char[200];
			char* suffix = new char[200];
			char* gender = new char[200];
			char* email = new char[200];
			GetWindowText(GetDlgItem(hDlg, UDI_SALUTATION_CB),sal,200);
			GetWindowText(GetDlgItem(hDlg, UDI_FIRST_ET),first,200);
			GetWindowText(GetDlgItem(hDlg, UDI_MIDDLE_ET),middle,200);
			GetWindowText(GetDlgItem(hDlg, UDI_LAST_ET),last,200);
			GetWindowText(GetDlgItem(hDlg, UDI_SUFFIX_CB),suffix,200);
			GetWindowText(GetDlgItem(hDlg, UDI_GENDER_CB),gender,200);
			GetWindowText(GetDlgItem(hDlg, UDI_EMAIL_ET),email,200);

			//Check to see if user has entered first and last name
			if(strlen(first) < 1 || strlen(last) < 1)    
			{       
				MessageBox(hDlg, LPCSTR("You must enter at least a first and last name."), LPCSTR("Adding Person Dialog"), MB_OK);
				break;
			} else
			{
				currentModelID = savingFace->createModel(sal,first,middle,last,suffix,gender,email);
				if(currentModelID)
				{
					EndDialog(hDlg, LOWORD(wParam));
					DialogBox(hInst, MAKEINTRESOURCE(UDI_DIALOG3), hDlg, IDD_PHOTO_CALLBACK);
					return (INT_PTR)TRUE;
				}else{
					MessageBox(hDlg, LPCSTR("An error occured."), LPCSTR("Adding Person Dialog"), MB_OK);
					break;
				}
			}
		}
		if(LOWORD(wParam) == UDI_CANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK IDD_PHOTO_CALLBACK(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	//bob *theBob = new bob(); 
	//theBob->controller = savingFace;
	//theBob->modelId = currentModelID;
	switch (message)
	{
	case WM_INITDIALOG:
		//savingFace->takeSnapshot(currentModelID);
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == UDI_OK2)
		{
			//TODO: Verify picture was taken.
			EndDialog(hDlg, LOWORD(wParam));
			//Verify correct functioning.
			MessageBox(hDlg, LPCSTR("Building model."), LPCSTR("Capture Dialog"), MB_OK);
			if (savingFace->buildModel(currentModelID) == SF_STS_OK)
			{
				MessageBox(hDlg, LPCSTR("Model has been built."), LPCSTR("Capture Dialog"), MB_OK);
			}
			else
			{
				MessageBox(hDlg, LPCSTR("An error has occured building the model."), LPCSTR("Capture Dialog"), MB_OK);
			}
			return (INT_PTR)TRUE;
		}else if(LOWORD(wParam) == UDI_CAPTURE)
		{
			//take photo and load it to the image window
			savingFace->takeSnapshot(currentModelID);
			string file = savingFace->getSnapshotPath(currentModelID);
			HBITMAP hImage = (HBITMAP)LoadImage(NULL, LPCSTR(file.c_str()), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			SendMessage(GetDlgItem(hDlg, UDI_PC),STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hImage);
			RedrawWindow(hDlg,0,0,0);
			
			return (INT_PTR)TRUE;
		}
	default:
		return false;
	}
}