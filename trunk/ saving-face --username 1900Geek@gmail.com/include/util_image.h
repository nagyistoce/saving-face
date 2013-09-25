/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#ifndef __UTIL_IMAGE_H__
#define __UTIL_IMAGE_H__
#include <windows.h>
#include <wincodec.h>
#include <d2d1.h>
#include "pxcsession.h"
#include "pxcimage.h"

class UtilImage {
public:

    UtilImage(PXCSession *session);
    ~UtilImage(void);

    void SetFileName(pxcCHAR *filename);
    bool Read(PXCImage **image);
    bool Write(PXCImage *image);

    void Release() { ::delete this; }

    static pxcCHAR* ImageColorFormat2String(PXCImage::ColorFormat format) {
        switch (format) {
        case PXCImage::COLOR_FORMAT_YUY2: return L"YUY2";
        case PXCImage::COLOR_FORMAT_NV12: return L"NV12";
        case PXCImage::COLOR_FORMAT_RGB32: return L"RGB32";
        case PXCImage::COLOR_FORMAT_RGB24: return L"RGB24";
        case PXCImage::COLOR_FORMAT_GRAY: return L"Gray";
        case PXCImage::COLOR_FORMAT_DEPTH: return L"DEPTH";
        case PXCImage::COLOR_FORMAT_VERTICES: return L"VERTICES";
        }
        return L"Unknown";
    }

protected:
    PXCSession          *m_session;
    pxcCHAR             filename[1024];
    ID2D1Factory        *m_pD2DFactory;
    IWICImagingFactory  *m_pIWICFactory;
};

#endif
