#include "AddUser.h"

INT_PTR CALLBACK AddUserProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_CREATE:
		{
			MessageBox(hWnd, L"Creating buttons", L"Adding Person Dialog", MB_OK);
			// Create an edit box
			HWND hEdit = CreateWindowEx(WS_EX_CLIENTEDGE,
				LPCWSTR("EDIT"),
				LPCWSTR(""),
				WS_CHILD|WS_VISIBLE|
				ES_MULTILINE|ES_AUTOVSCROLL|ES_AUTOHSCROLL,
				0,
				0,
				200,
				100,
				hWnd,
				(HMENU)IDC_MAIN_EDIT,
				GetModuleHandle(NULL),
				NULL);
			HGDIOBJ hfDefault=GetStockObject(DEFAULT_GUI_FONT);
			SendMessage(hEdit,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));
			SendMessage(hEdit,
				WM_SETTEXT,
				NULL,
				(LPARAM)"Insert text here...");

			// Create a push button
			HWND hWndButton=CreateWindowEx(NULL,
				LPCWSTR("BUTTON"),
				LPCWSTR("OK"),
				WS_TABSTOP|WS_VISIBLE|
				WS_CHILD|BS_DEFPUSHBUTTON,
				50,
				220,
				100,
				24,
				hWnd,
				(HMENU)IDC_MAIN_BUTTON,
				GetModuleHandle(NULL),
				NULL);
			SendMessage(hWndButton,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));

				UpdateWindow(hWnd);
		}
		break;

		case WM_COMMAND:
			switch(LOWORD(wParam))
            {
/*				case IDC_MAIN_BUTTON:
				{
					WCHAR text[256];
					GetDlgItemText(hWnd, IDC_EDIT1, (LPWSTR)text,255);
					MessageBox(NULL,
						(LPCWSTR)text,
						L"Information",
						MB_OK);
				}
				break;*/
				case IDCANCEL:
					DestroyWindow(hWnd); 
					PostQuitMessage(0);
					return TRUE;
			}
			break;

		case WM_DESTROY:
		{
			DestroyWindow(hWnd);
			PostQuitMessage(0);
			return true;
		}
		break;
	}

	return false;
}

