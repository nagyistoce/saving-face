#include "AddUser.h"

INT_PTR CALLBACK AddUserProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_CREATE:
		{
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

