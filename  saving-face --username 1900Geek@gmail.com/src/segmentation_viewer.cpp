/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012-2013 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#include <Windows.h>
#include <vector>
#include "util_pipeline.h"
#include "pxcsegmentation.h"
#include "util_image.h"
#define  ARRAY_SIZE 512

extern PXCSession *g_session;
extern volatile bool g_stop;
extern CRITICAL_SECTION   g_cs;
extern pxcCHAR* g_bg_image_file;
extern int g_max_distance; 
extern PXCSegmentation::BlendMode g_blend_mode; 
extern PXCSegmentation::FaceMode  g_face_mode; 


volatile bool g_disconnected=false;
pxcCHAR  g_bg_image_file_inuse[ARRAY_SIZE] = L""; 

void SetStatus(HWND hwndDlg, pxcCHAR *line);
pxcCHAR* GetCheckedDevice(HWND);
pxcCHAR* GetCheckedModule(HWND);
void DrawBitmap(HWND,PXCImage*);
void UpdatePanel(HWND);
bool GetPlaybackState(HWND hwndDlg);
bool GetRecordState(HWND hwndDlg);
pxcCHAR* GetPlaybackFile();
pxcCHAR* GetRecordFile();

static bool DisplayDeviceConnection(HWND hwndDlg, bool state) {
    if (state) {
        if (!g_disconnected) SetStatus(hwndDlg,L"Device Disconnected");
        g_disconnected = true;
    } else {
        if (g_disconnected) SetStatus(hwndDlg, L"Device Reconnected");
        g_disconnected = false;
    }
    return g_disconnected;
}

static void DisplayPicture(HWND hwndDlg, PXCImage *color) {
    PXCImage *image = color;
    bool dispose = false;

	// Calcualte FPS
    static int g_fps_nframes;
    static double g_fps_first;
    if ((g_fps_nframes++)==0) {
        LARGE_INTEGER now, freq;
        QueryPerformanceCounter(&now);
        QueryPerformanceFrequency(&freq);
        g_fps_first=(double)now.QuadPart/(double)freq.QuadPart;
    }
    if (g_fps_nframes>30) {
        LARGE_INTEGER now, freq;
        QueryPerformanceCounter(&now);
        QueryPerformanceFrequency(&freq);
        int fps=(int)((double)g_fps_nframes/((double)now.QuadPart/(double)freq.QuadPart-g_fps_first));

        pxcCHAR line[1024];
        swprintf_s<1024>(line,L"%s (%d fps)",L"Segmentation Viewer", fps);
        SetWindowTextW(hwndDlg,line);
        g_fps_nframes=0;
    }

	DrawBitmap(hwndDlg,image);
    if (dispose) image->Release();
}

static bool CheckBackgroundImage (PXCImage **bgImage)
{
	EnterCriticalSection(&g_cs);

	if (!g_bg_image_file) {
		LeaveCriticalSection(&g_cs);
		return false; 
	}
	if (!wcscmp(g_bg_image_file, g_bg_image_file_inuse)) {
		LeaveCriticalSection(&g_cs);
		return true; 
	}

	wcscpy_s(g_bg_image_file_inuse, g_bg_image_file); 
	PXCSmartPtr<UtilImage> utilImage = new UtilImage (g_session); 
	utilImage->SetFileName(g_bg_image_file_inuse); 
	if (*bgImage) (*bgImage)->Release(); 
	utilImage->Read(bgImage); 
 
	LeaveCriticalSection(&g_cs);
	return true;
}


static bool UpdateSegmentationImage (PXCImage **bgImage)
{
	EnterCriticalSection(&g_cs);

	if ((g_blend_mode!=PXCSegmentation::BLEND_BG_IMAGE) || !g_bg_image_file) {
		LeaveCriticalSection(&g_cs);
		return false; 
	}

	if (!wcscmp(g_bg_image_file, g_bg_image_file_inuse)) {
		LeaveCriticalSection(&g_cs);
		return false; 
	}

	wcscpy_s(g_bg_image_file_inuse, g_bg_image_file); 
	PXCSmartPtr<UtilImage> utilImage = new UtilImage (g_session); 
	utilImage->SetFileName(g_bg_image_file_inuse); 
	if (*bgImage) {
        (*bgImage)->Release(); 
        *bgImage = NULL;
    }
	utilImage->Read(bgImage); 
 
	LeaveCriticalSection(&g_cs);
	return true;
}


void SimplePipeline(HWND hwndDlg) {
	UtilPipeline *pp=0;
	for (int k=0; k<ARRAY_SIZE; k++) g_bg_image_file_inuse[k] = 0;

	/* Set Mode & Source */
	if (GetRecordState(hwndDlg)) {
		pp=new UtilPipeline(0,GetRecordFile(),true);
		pp->QueryCapture()->SetFilter(GetCheckedDevice(hwndDlg));
	} else if (GetPlaybackState(hwndDlg)) {
		pp=new UtilPipeline(0,GetPlaybackFile(),false);
	} else {
		pp=new UtilPipeline();
		pp->QueryCapture()->SetFilter(GetCheckedDevice(hwndDlg));
	}
	bool sts=true;

	/* Set Module */
	pp->EnableSegmentation(GetCheckedModule(hwndDlg));

	/* No depth filtering */
	// pp->QueryCapture()->SetFilter(PXCCapture::Device::PROPERTY_DEPTH_SMOOTHING,false);

	/* Init */
	PXCSmartPtr<PXCImage> bgImage;
	SetStatus(hwndDlg,L"Init Started");
	if (pp->Init()) {
		SetStatus(hwndDlg,L"Streaming");
		g_disconnected=false;

		PXCSegmentation::ProfileInfo pinfo;
	    pp->QuerySegmentation()->QueryProfile(&pinfo); 
		pinfo.faceMode  = g_face_mode;
	    pinfo.blendMode = g_blend_mode;
		pinfo.maxDepthThreshold = g_max_distance; 
        pxcStatus status=pp->QuerySegmentation()->SetProfile(&pinfo);
		if (status<PXC_STATUS_NO_ERROR) {
			SetStatus(hwndDlg,L"Failed to set module profile");
			sts = false; 
			g_stop = true;
		} 

		while (!g_stop) {
			if (UpdateSegmentationImage(&bgImage)) 
				pp->SetSegmentationBGImage(bgImage); 
			
			pp->SetSegmentationBlendMode(g_blend_mode); 
			if ((pinfo.faceMode!=g_face_mode) || (pinfo.blendMode!=g_blend_mode) || (pinfo.maxDepthThreshold!=g_max_distance))
			{
				pinfo.faceMode  = g_face_mode;
				pinfo.blendMode = g_blend_mode;
				pinfo.maxDepthThreshold = g_max_distance;
				status=pp->QuerySegmentation()->SetProfile(&pinfo);
				if (status<PXC_STATUS_NO_ERROR) {
					SetStatus(hwndDlg,L"Failed to set module profile");
					break;
				} 
			}

			if (!pp->AcquireFrame(true)) break;
            if (!DisplayDeviceConnection(hwndDlg, pp->IsDisconnected())) {
				if (g_blend_mode==PXCSegmentation::BLEND_ANY)
					DisplayPicture(hwndDlg, pp->QuerySegmentationImage());
				else
					DisplayPicture(hwndDlg, pp->QuerySegmentationBlendedImage());
				UpdatePanel(hwndDlg);
			}
			pp->ReleaseFrame();
		}
	} else {
		SetStatus(hwndDlg,L"Init Failed");
		sts=false;
	}

	pp->Close();
	pp->Release();
	if (sts) SetStatus(hwndDlg,L"Stopped");
}


void AdvancedPipeline(HWND hwndDlg) {
	pxcStatus sts; 
	for (int k=0; k<ARRAY_SIZE; k++) g_bg_image_file_inuse[k] = 0;

    /* Set Module */
    PXCSession::ImplDesc desc;
	memset(&desc,0,sizeof(desc));
	wcscpy_s<sizeof(desc.friendlyName)/sizeof(pxcCHAR)>(desc.friendlyName,GetCheckedModule(hwndDlg));

    PXCSmartPtr<PXCSegmentation> segmentor;
    sts=g_session->CreateImpl<PXCSegmentation>(&desc, &segmentor);
    if (sts<PXC_STATUS_NO_ERROR) {
        SetStatus(hwndDlg,L"Failed to create the segmentation module");
        return;
    }

    /* Set Source */
    PXCSmartPtr<UtilCapture> capture;
	if (GetRecordState(hwndDlg)) {
		capture=new UtilCaptureFile(g_session,GetRecordFile(),true);
        capture->SetFilter(GetCheckedDevice(hwndDlg));
	} else if (GetPlaybackState(hwndDlg)) {
		capture=new UtilCaptureFile(g_session,GetPlaybackFile(),false);
	} else {
		capture=new UtilCapture(g_session);
        capture->SetFilter(GetCheckedDevice(hwndDlg));
	}

    PXCSegmentation::ProfileInfo pinfo;
    sts=segmentor->QueryProfile(0, &pinfo);
    if (sts<PXC_STATUS_NO_ERROR) {
		SetStatus(hwndDlg,L"Failed to query module profile");
		return;
	}

    sts=capture->LocateStreams(&pinfo.inputs);
    if (sts<PXC_STATUS_NO_ERROR) {
		SetStatus(hwndDlg,L"Failed to pair the segmentation module with I/O");
		return;
	}

	/* no depth filtering */
	// capture->SetFilter(PXCCapture::Device::PROPERTY_DEPTH_SMOOTHING,false);

	pinfo.faceMode  = g_face_mode;
	pinfo.blendMode = g_blend_mode;
    sts=segmentor->SetProfile(&pinfo);
    if (sts<PXC_STATUS_NO_ERROR) {
		SetStatus(hwndDlg,L"Failed to set module profile");
		return;
	} 

    SetStatus(hwndDlg,L"Streaming");
    PXCSmartArray<PXCImage> images;
    PXCSmartSPArray sps(3);
	PXCSmartPtr<PXCImage> bgImage;
	
    while (!g_stop) {
		// Check if face mode or blend mode has been changed
		if ((pinfo.faceMode!=g_face_mode) || (pinfo.blendMode!=g_blend_mode) || (pinfo.maxDepthThreshold!=g_max_distance))
		{
			pinfo.faceMode  = g_face_mode;
			pinfo.blendMode = g_blend_mode;
			pinfo.maxDepthThreshold = g_max_distance;
			sts=segmentor->SetProfile(&pinfo);
			if (sts<PXC_STATUS_NO_ERROR) {
				SetStatus(hwndDlg,L"Failed to set module profile");
				break;
			} 
		}

        sts=capture->ReadStreamAsync(images.ReleaseRefs(),sps.ReleaseRef(0));
        if (DisplayDeviceConnection(hwndDlg,sts==PXC_STATUS_DEVICE_LOST)) continue;
        if (sts<PXC_STATUS_NO_ERROR) break;

		PXCSmartPtr<PXCImage> segImage; 
        sts=segmentor->SegmentImageAsync(images, &segImage, sps.ReleaseRef(1));
        if (sts<PXC_STATUS_NO_ERROR) break;

		bool isBlended = false; 
		PXCSmartPtr<PXCImage> blended_image;
		
		if (g_blend_mode != PXCSegmentation::BLEND_ANY) {
			if (g_blend_mode!=PXCSegmentation::BLEND_BG_IMAGE) {
				isBlended = true; 
				sts=segmentor->BlendImageAsync(capture->QueryImage(images, PXCImage::IMAGE_TYPE_COLOR), segImage, 0, &blended_image, sps.ReleaseRef(2));
			} else {
				if (!CheckBackgroundImage(&bgImage)) {
					SetStatus(hwndDlg,L"Background image is not available");
				 	break;
				}

				isBlended = true; 
				sts=segmentor->BlendImageAsync(capture->QueryImage(images, PXCImage::IMAGE_TYPE_COLOR), segImage, bgImage, &blended_image, sps.ReleaseRef(2));
			}
		}

		sts=sps.SynchronizeEx();
        sts = sps[0]->Synchronize(0); 
		if (DisplayDeviceConnection(hwndDlg,sts==PXC_STATUS_DEVICE_LOST)) continue;
		else if (sts<PXC_STATUS_NO_ERROR) break;

		if (isBlended)
			DisplayPicture(hwndDlg, blended_image);
		else 
			DisplayPicture(hwndDlg, segImage);

        UpdatePanel(hwndDlg);
		
		images.ReleaseRefs();
        blended_image.ReleaseRef();
        segImage.ReleaseRef();
    }
    SetStatus(hwndDlg,L"Stopped");
}