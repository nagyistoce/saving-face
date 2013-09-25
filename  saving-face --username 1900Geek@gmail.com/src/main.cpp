/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012-2013 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#include <Windows.h>
#include <WindowsX.h>
#include <commctrl.h>
#include "resource.h"
#include "pxcsegmentation.h"
#include "pxcsmartptr.h"

#define IDC_STATUS 10000
#define ID_DEVICEX 21000
#define ID_MODULEX 22000

#define MAXDISTANCE_MIN 800
#define MAXDISTANCE_MAX 1200

HINSTANCE   g_hInst=0;
PXCSession *g_session=0;

/* Panel Bitmap */
HBITMAP     g_bitmap=0;

/* Segmentation algorithm parameter */
pxcCHAR* g_bg_image_file = 0; 
int      g_max_distance = 850; 
PXCSegmentation::BlendMode g_blend_mode = PXCSegmentation::BLEND_ANY; 
PXCSegmentation::FaceMode  g_face_mode = PXCSegmentation::FACE_ALG_DEFAULT; 

/* Threading control */
volatile bool g_running=false;
volatile bool g_stop=true;
CRITICAL_SECTION   g_cs;

/* Control Layout */
int g_controls[]={IDC_Face, IDC_SCALE, IDC_MIRROR, IDC_NOBLEND, IDC_BLENDBLUE, IDC_BLENDWHITE, IDC_BLENDIMAGE, IDC_BLENDALPHA, IDC_SLIDER1, IDC_STATIC2,IDC_STATIC4,IDC_STATIC6, ID_START, ID_STOP };
RECT g_layout[3+sizeof(g_controls)/sizeof(g_controls[0])];

pxcCHAR* GetBackgroundImageFile(void);

void SaveLayout(HWND hwndDlg) {
	GetClientRect(hwndDlg,&g_layout[0]);
	ClientToScreen(hwndDlg,(LPPOINT)&g_layout[0].left);
	ClientToScreen(hwndDlg,(LPPOINT)&g_layout[0].right);
	GetWindowRect(GetDlgItem(hwndDlg,IDC_PANEL),&g_layout[1]);
	GetWindowRect(GetDlgItem(hwndDlg,IDC_STATUS),&g_layout[2]);
	for (int i=0;i<sizeof(g_controls)/sizeof(g_controls[0]);i++)
		GetWindowRect(GetDlgItem(hwndDlg,g_controls[i]),&g_layout[3+i]);
}

void RedoLayout(HWND hwndDlg) {
	RECT rect;
	GetClientRect(hwndDlg,&rect);

	/* Status */
	SetWindowPos(GetDlgItem(hwndDlg,IDC_STATUS),hwndDlg,
		0,
		rect.bottom-(g_layout[2].bottom-g_layout[2].top),
		rect.right-rect.left,
		(g_layout[2].bottom-g_layout[2].top),SWP_NOZORDER);

	/* Panel */
	SetWindowPos(GetDlgItem(hwndDlg,IDC_PANEL),hwndDlg,
		(g_layout[1].left-g_layout[0].left),
		(g_layout[1].top-g_layout[0].top),
		rect.right-(g_layout[1].left-g_layout[0].left)-(g_layout[0].right-g_layout[1].right),
		rect.bottom-(g_layout[1].top-g_layout[0].top)-(g_layout[0].bottom-g_layout[1].bottom),
		SWP_NOZORDER);

	/* Buttons & CheckBoxes */
	for (int i=0;i<sizeof(g_controls)/sizeof(g_controls[0]);i++) {
		SetWindowPos(GetDlgItem(hwndDlg,g_controls[i]),hwndDlg,
			rect.right-(g_layout[0].right-g_layout[3+i].left),
			(g_layout[3+i].top-g_layout[0].top),
			(g_layout[3+i].right-g_layout[3+i].left),
			(g_layout[3+i].bottom-g_layout[3+i].top),
			SWP_NOZORDER);
	}
}

void UpdateBlendMode(HWND hwndDlg, int idc)
{
	if (idc!=IDC_NOBLEND && idc!=IDC_BLENDBLUE && idc!=IDC_BLENDWHITE && idc!=IDC_BLENDIMAGE && idc!=IDC_BLENDALPHA) return;

	if (idc==IDC_BLENDIMAGE && (!g_bg_image_file || g_bg_image_file==L""))
	{
		CheckDlgButton(hwndDlg,IDC_BLENDIMAGE,BST_UNCHECKED);
		return;
	}

	CheckDlgButton(hwndDlg,IDC_NOBLEND,BST_UNCHECKED);
	CheckDlgButton(hwndDlg,IDC_BLENDBLUE,BST_UNCHECKED);
	CheckDlgButton(hwndDlg,IDC_BLENDWHITE,BST_UNCHECKED);
	CheckDlgButton(hwndDlg,IDC_BLENDIMAGE,BST_UNCHECKED);
	CheckDlgButton(hwndDlg,IDC_BLENDALPHA,BST_UNCHECKED);

	switch (idc) {
	case IDC_NOBLEND:
		CheckDlgButton(hwndDlg,IDC_NOBLEND,BST_CHECKED);
		g_blend_mode = PXCSegmentation::BLEND_ANY;
		break;
	case IDC_BLENDBLUE:
		CheckDlgButton(hwndDlg,IDC_BLENDBLUE,BST_CHECKED);
	    g_blend_mode = PXCSegmentation::BLEND_BG_BLUE;
		break;
	case IDC_BLENDWHITE:
		CheckDlgButton(hwndDlg,IDC_BLENDWHITE,BST_CHECKED);
	    g_blend_mode = PXCSegmentation::BLEND_BG_WHITE;
		break;
	case IDC_BLENDIMAGE:
		CheckDlgButton(hwndDlg,IDC_BLENDIMAGE,BST_CHECKED);
	    g_blend_mode = PXCSegmentation::BLEND_BG_IMAGE;
		break;
	case IDC_BLENDALPHA:
		CheckDlgButton(hwndDlg,IDC_BLENDALPHA,BST_CHECKED);
	    g_blend_mode = PXCSegmentation::BLEND_ALPHA_CHANNEL;
		break;
	default:
		break;
	}
}

static void PopulateDevice(HMENU menu) {
	DeleteMenu(menu,0,MF_BYPOSITION);

	PXCSession::ImplDesc desc;
	memset(&desc,0,sizeof(desc));
	desc.group=PXCSession::IMPL_GROUP_SENSOR;
	desc.subgroup=PXCSession::IMPL_SUBGROUP_VIDEO_CAPTURE;
	HMENU menu1=CreatePopupMenu();
	for (int i=0,k=ID_DEVICEX;;i++) {
		PXCSession::ImplDesc desc1;
		if (g_session->QueryImpl(&desc,i,&desc1)<PXC_STATUS_NO_ERROR) break;
		PXCSmartPtr<PXCCapture> capture;
		if (g_session->CreateImpl<PXCCapture>(&desc1,&capture)<PXC_STATUS_NO_ERROR) continue;
		for (int j=0;;j++) {
			PXCCapture::DeviceInfo dinfo;
			if (capture->QueryDevice(j,&dinfo)<PXC_STATUS_NO_ERROR) break;
			AppendMenu(menu1,MF_STRING,k++,dinfo.name);
		}
	}
	CheckMenuRadioItem(menu1,0,GetMenuItemCount(menu1),0,MF_BYPOSITION);
	InsertMenu(menu,0,MF_BYPOSITION|MF_POPUP,(UINT_PTR)menu1,L"Device");
}

static int GetChecked(HMENU menu) {
	for (int i=0;i<GetMenuItemCount(menu);i++)
		if (GetMenuState(menu,i,MF_BYPOSITION)&MF_CHECKED) return i;
	return 0;
}

pxcCHAR* GetCheckedDevice(HWND hwndDlg) {
	HMENU menu=GetSubMenu(GetMenu(hwndDlg),0);	// ID_DEVICE
	static pxcCHAR line[256];
	GetMenuString(menu,GetChecked(menu),line,sizeof(line)/sizeof(pxcCHAR),MF_BYPOSITION);
	return line;
}

static void PopulateModule(HMENU menu) {
	DeleteMenu(menu,1,MF_BYPOSITION);

	PXCSession::ImplDesc desc, desc1;
	memset(&desc,0,sizeof(desc));
	desc.cuids[0]=PXCSegmentation::CUID;
	HMENU menu1=CreatePopupMenu();
	int i;
	for (i=0;;i++) {
		if (g_session->QueryImpl(&desc,i,&desc1)<PXC_STATUS_NO_ERROR) break;
		AppendMenu(menu1,MF_STRING,ID_MODULEX+i,desc1.friendlyName);
	}
	CheckMenuRadioItem(menu1,0,i,0,MF_BYPOSITION);
	InsertMenu(menu,1,MF_BYPOSITION|MF_POPUP,(UINT_PTR)menu1,L"Module");
}

pxcCHAR *GetCheckedModule(HWND hwndDlg) {
	HMENU menu=GetSubMenu(GetMenu(hwndDlg),1);	// ID_MODULE
	static pxcCHAR line[256];
	GetMenuString(menu,GetChecked(menu),line,sizeof(line)/sizeof(pxcCHAR),MF_BYPOSITION);
	return line;
}

static DWORD WINAPI ThreadProc(LPVOID arg) {
	void AdvancedPipeline(HWND hwndDlg);
	void SimplePipeline(HWND hwndDlg);

	if (GetMenuState(GetMenu((HWND)arg),ID_PIPELINE_SIMPLE,MF_BYCOMMAND)&MF_CHECKED) {
		SimplePipeline((HWND)arg); 
	} else {
		AdvancedPipeline((HWND)arg);
	}
 
	PostMessage((HWND)arg,WM_COMMAND,ID_STOP,0);
	g_running=false;
	return 0;
}

void SetStatus(HWND hwndDlg, pxcCHAR *line) {
	HWND hwndStatus=GetDlgItem(hwndDlg,IDC_STATUS);
	SetWindowText(hwndStatus,line);
}

 
bool GetPlaybackState(HWND hwndDlg) {
	return (GetMenuState(GetMenu(hwndDlg),ID_MODE_PLAYBACK,MF_BYCOMMAND)&MF_CHECKED)!=0;
}

bool GetRecordState(HWND hwndDlg) {
	return (GetMenuState(GetMenu(hwndDlg),ID_MODE_RECORD,MF_BYCOMMAND)&MF_CHECKED)!=0;
}

void DrawBitmap(HWND hwndDlg, PXCImage *image) {
	if (!image) return;
    if (g_bitmap) {
        DeleteObject(g_bitmap);
		g_bitmap=0;
    }

    PXCImage::ImageInfo info;
    image->QueryInfo(&info);
    PXCImage::ImageData data;
    if (image->AcquireAccess(PXCImage::ACCESS_READ,PXCImage::COLOR_FORMAT_RGB32, &data)>=PXC_STATUS_NO_ERROR) {
		HWND hwndPanel=GetDlgItem(hwndDlg,IDC_PANEL);
        HDC dc=GetDC(hwndPanel);
		BITMAPINFO binfo;
		memset(&binfo,0,sizeof(binfo));
		binfo.bmiHeader.biWidth=info.width;
		binfo.bmiHeader.biHeight= - (int)info.height;
		binfo.bmiHeader.biBitCount=32;
		binfo.bmiHeader.biPlanes=1;
		binfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
		binfo.bmiHeader.biCompression=BI_RGB;
        g_bitmap=CreateDIBitmap(dc, &binfo.bmiHeader, CBM_INIT, data.planes[0], &binfo, DIB_RGB_COLORS);
        ReleaseDC(hwndPanel, dc);
		image->ReleaseAccess(&data);
    }
}

HBITMAP ResizeBitmap(HWND hwnd, HBITMAP bitmap, bool scale=true, bool mirror=false) {
	RECT rect;
	GetClientRect(hwnd,&rect);

	BITMAP bm;
	GetObject(bitmap,sizeof(BITMAP),&bm);

	if (!scale) {
		rect.right=bm.bmWidth;
		rect.bottom=bm.bmHeight;
	}

	HDC dc=GetDC(hwnd);
	HDC dc2=CreateCompatibleDC(dc);
	SelectObject(dc2,bitmap);

	HBITMAP bitmap2=CreateCompatibleBitmap(dc,rect.right,rect.bottom);
	HDC dc3=CreateCompatibleDC(dc);
	SelectObject(dc3,bitmap2);
	ReleaseDC(hwnd,dc);

	SetStretchBltMode(dc3, HALFTONE);
	if (mirror) {
		StretchBlt(dc3,rect.right-1,0,-rect.right,rect.bottom,dc2,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
	} else {
		if (!scale) {
			BitBlt(dc3,0,0,rect.right,rect.bottom,dc2,0,0,SRCCOPY);
		} else {
			StretchBlt(dc3,0,0,rect.right,rect.bottom,dc2,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
		}
	}
	if (!scale) SetPixel(dc3,0,0,RGB(0,0,0)); // WORKAROUND for SS_CENTERIMAGE

	DeleteObject(dc3);
	DeleteObject(dc2);
	return bitmap2;
}

void UpdatePanel(HWND hwndDlg) {
	if (!g_bitmap) return;

	bool scale=Button_GetState(GetDlgItem(hwndDlg,IDC_SCALE))&BST_CHECKED;
	bool mirror=Button_GetState(GetDlgItem(hwndDlg,IDC_MIRROR))&BST_CHECKED;

	HWND panel=GetDlgItem(hwndDlg,IDC_PANEL);
	HBITMAP bitmap=ResizeBitmap(panel,g_bitmap,scale,mirror);
	DeleteObject(g_bitmap);
	g_bitmap=bitmap;
	SendMessage(panel,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)g_bitmap);
	InvalidateRect(panel,0,TRUE);
}



INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM) { 
	HMENU menu=GetMenu(hwndDlg);
	HMENU menu1;

	HWND hSlider = GetDlgItem(hwndDlg, IDC_SLIDER1);


    switch (message) { 
    case WM_INITDIALOG:
		CheckDlgButton(hwndDlg,IDC_Face,BST_CHECKED);
		CheckDlgButton(hwndDlg,IDC_MIRROR,BST_CHECKED);
		CheckDlgButton(hwndDlg,IDC_NOBLEND,BST_CHECKED);
		PopulateDevice(menu);
		PopulateModule(menu);

		PostMessage(hSlider, TBM_SETRANGEMAX, TRUE, MAXDISTANCE_MAX);
		PostMessage(hSlider, TBM_SETRANGEMIN, TRUE, MAXDISTANCE_MIN);
		PostMessage(hSlider, TBM_SETPOS, TRUE, g_max_distance); 

		// check the first submenu item from 3rd menu on
		for (int k=2; k<GetMenuItemCount(menu); k++) {
			menu1=GetSubMenu(menu,k);
			CheckMenuRadioItem(menu1,0,GetMenuItemCount(menu1),0,MF_BYPOSITION);
		}

		SaveLayout(hwndDlg);
        return TRUE; 
    case WM_COMMAND: 
		menu1=GetSubMenu(menu,0);
		if (LOWORD(wParam)>=ID_DEVICEX && LOWORD(wParam)<ID_DEVICEX+GetMenuItemCount(menu1)) {
			CheckMenuRadioItem(menu1,0,GetMenuItemCount(menu1),LOWORD(wParam)-ID_DEVICEX,MF_BYPOSITION);
			return TRUE;
		}
		menu1=GetSubMenu(menu,1);
		if (LOWORD(wParam)>=ID_MODULEX && LOWORD(wParam)<ID_MODULEX+GetMenuItemCount(menu1)) {
			CheckMenuRadioItem(menu1,0,GetMenuItemCount(menu1),LOWORD(wParam)-ID_MODULEX,MF_BYPOSITION);
			return TRUE;
		}
        switch (LOWORD(wParam)) {
        case IDCANCEL:
			g_stop=true;
			if (g_running) {
				PostMessage(hwndDlg,WM_COMMAND,IDCANCEL,0);
			} else {
				DestroyWindow(hwndDlg); 
				PostQuitMessage(0);
			}
            return TRUE;
		case IDC_Face:
			{
				bool bFace=Button_GetState(GetDlgItem(hwndDlg,IDC_Face))&BST_CHECKED;
				if (!bFace) {
					g_face_mode = PXCSegmentation::FACE_ANY; 
		 			CheckDlgButton(hwndDlg,IDC_Face,BST_UNCHECKED);
				} else {
					g_face_mode = PXCSegmentation::FACE_ALG_DEFAULT; 
					CheckDlgButton(hwndDlg,IDC_Face,BST_CHECKED);
				}
			}
		 	return TRUE;
		case IDC_NOBLEND:
			UpdateBlendMode(hwndDlg, IDC_NOBLEND);
		    return TRUE;
		case IDC_BLENDBLUE:
		    UpdateBlendMode(hwndDlg, IDC_BLENDBLUE); 
		    return TRUE;
		case IDC_BLENDWHITE:
			UpdateBlendMode(hwndDlg, IDC_BLENDWHITE);
		    return TRUE;
		case IDC_BLENDIMAGE:
			{
			pxcCHAR* new_bg_file = GetBackgroundImageFile();
			if (new_bg_file) {
				EnterCriticalSection(&g_cs);
				g_bg_image_file = new_bg_file; 
				LeaveCriticalSection(&g_cs);
			}
			UpdateBlendMode(hwndDlg, IDC_BLENDIMAGE);
		    return TRUE;
			}
		case IDC_BLENDALPHA:
			UpdateBlendMode(hwndDlg, IDC_BLENDALPHA);
		    return TRUE;
		case ID_PIPELINE_SIMPLE:
			CheckMenuItem(menu,ID_PIPELINE_SIMPLE,MF_CHECKED);
			CheckMenuItem(menu,ID_PIPELINE_ADVANCED,MF_UNCHECKED);
			return TRUE;
		case ID_PIPELINE_ADVANCED:
			CheckMenuItem(menu,ID_PIPELINE_SIMPLE,MF_UNCHECKED);
			CheckMenuItem(menu,ID_PIPELINE_ADVANCED,MF_CHECKED);
			return TRUE;
		case ID_START:
			Button_Enable(GetDlgItem(hwndDlg,ID_START),false);
			Button_Enable(GetDlgItem(hwndDlg,ID_STOP),true);
			for (int i=0;i<GetMenuItemCount(menu);i++)
				EnableMenuItem(menu,i,MF_BYPOSITION|MF_GRAYED);
			DrawMenuBar(hwndDlg);
			g_stop=false;
			g_running=true;
			CreateThread(0,0,ThreadProc,hwndDlg,0,0);
			Sleep(0);
			return TRUE;
		case ID_STOP:
			g_stop=true;
			if (g_running) {
				PostMessage(hwndDlg,WM_COMMAND,ID_STOP,0);
			} else {
				for (int i=0;i<GetMenuItemCount(menu);i++)
					EnableMenuItem(menu,i,MF_BYPOSITION|MF_ENABLED);
				DrawMenuBar(hwndDlg);
				Button_Enable(GetDlgItem(hwndDlg,ID_START),true);
				Button_Enable(GetDlgItem(hwndDlg,ID_STOP),false);
			}
			return TRUE;
		case ID_MODE_LIVE:
			CheckMenuItem(menu,ID_MODE_LIVE,MF_CHECKED);
			CheckMenuItem(menu,ID_MODE_PLAYBACK,MF_UNCHECKED);
			CheckMenuItem(menu,ID_MODE_RECORD,MF_UNCHECKED);
			return TRUE;
		case ID_MODE_PLAYBACK:
			CheckMenuItem(menu,ID_MODE_LIVE,MF_UNCHECKED);
			CheckMenuItem(menu,ID_MODE_PLAYBACK,MF_CHECKED);
			CheckMenuItem(menu,ID_MODE_RECORD,MF_UNCHECKED);
			return TRUE;
		case ID_MODE_RECORD:
			CheckMenuItem(menu,ID_MODE_LIVE,MF_UNCHECKED);
			CheckMenuItem(menu,ID_MODE_PLAYBACK,MF_UNCHECKED);
			CheckMenuItem(menu,ID_MODE_RECORD,MF_CHECKED);
			return TRUE;
        } 
		break;
	case WM_SIZE:
		RedoLayout(hwndDlg);
		return TRUE;
	case WM_NOTIFY:
		hSlider = GetDlgItem(hwndDlg, IDC_SLIDER1); 
		int pos = (int) SendMessage(hSlider, TBM_GETPOS, 0, 0);
		if (pos>=MAXDISTANCE_MIN && pos<=MAXDISTANCE_MAX)
			g_max_distance = pos; 
		return TRUE;
    } 
    return FALSE; 
} 

#pragma warning(disable:4706) /* assignment within conditional */
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int) {
	InitCommonControls();
	g_hInst=hInstance;

	pxcStatus sts=PXCSession_Create(&g_session);
	if (sts<PXC_STATUS_NO_ERROR) {
        MessageBoxW(0,L"Failed to create an SDK session",L"Segmentation Viewer",MB_ICONEXCLAMATION|MB_OK);
        return 1;
    }

    HWND hWnd=CreateDialogW(hInstance,MAKEINTRESOURCE(IDD_MAINFRAME),0,DialogProc);
    if (!hWnd)  {
        MessageBoxW(0,L"Failed to create a window",L"Segmentation Viewer",MB_ICONEXCLAMATION|MB_OK);
        return 1;
    }

	HWND hWnd2=CreateStatusWindow(WS_CHILD|WS_VISIBLE,L"OK",hWnd,IDC_STATUS);
	if (!hWnd2) {
        MessageBoxW(0,L"Failed to create a status bar",L"Segmentation Viewer",MB_ICONEXCLAMATION|MB_OK);
        return 1;
	}

	InitializeCriticalSection(&g_cs);
	UpdateWindow(hWnd);

    MSG msg;
	for (int sts;(sts=GetMessageW(&msg,hWnd,0,0));) {
        if (sts == -1) return sts;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

	g_stop=true;
	while (g_running) Sleep(5);
	g_session->Release();
	DeleteCriticalSection(&g_cs);
    return (int)msg.wParam;
}

pxcCHAR* GetPlaybackFile(void) {
	static pxcCHAR file[1024]={0};

	OPENFILENAME ofn;
	memset(&ofn,0,sizeof(ofn));
	ofn.lStructSize=sizeof(ofn);
	ofn.lpstrFilter=L"All Files\0*.*\0\0";
	ofn.lpstrFile=file; file[0]=0;
	ofn.nMaxFile=sizeof(file)/sizeof(pxcCHAR);
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_EXPLORER;
	if (!GetOpenFileName(&ofn)) return 0;
	return file;
}

pxcCHAR* GetBackgroundImageFile(void) {
	static pxcCHAR file[1024]={0};

	OPENFILENAME ofn;
	memset(&ofn,0,sizeof(ofn));
	ofn.lStructSize=sizeof(ofn);
	ofn.lpstrFilter=L"All Files\0*.*\0\0";
	ofn.lpstrFile=file; 
	ofn.nMaxFile=sizeof(file)/sizeof(pxcCHAR);
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_EXPLORER;
	if (!GetOpenFileName(&ofn)) return 0;
	return file;
}

pxcCHAR* GetRecordFile(void) {
	static pxcCHAR file[1024]={0};

	OPENFILENAME ofn;
	memset(&ofn,0,sizeof(ofn));
	ofn.lStructSize=sizeof(ofn);
	ofn.lpstrFilter=L"All Files\0*.*\0\0";
	ofn.lpstrFile=file; file[0]=0;
	ofn.nMaxFile=sizeof(file)/sizeof(pxcCHAR);
	ofn.Flags = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_EXPLORER;
	if (!GetSaveFileName(&ofn)) return 0;
	return file;
}

