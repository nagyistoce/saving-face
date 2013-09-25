/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#include <wchar.h>
#include "util_image.h"
#include "pxcsmartptr.h"

UtilImage::UtilImage(PXCSession *session) {
    m_session=session;
    m_pIWICFactory=0;
    m_pD2DFactory=0;
    CoInitialize(NULL); 
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
    CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (void **)&m_pIWICFactory);
}

UtilImage::~UtilImage() {
    if (m_pIWICFactory) m_pIWICFactory->Release();
    if (m_pD2DFactory) m_pD2DFactory->Release();
    CoUninitialize(); 
}

void UtilImage::SetFileName(pxcCHAR *file) {
    wcsncpy_s(filename, 1024, file, wcslen(file));
}

bool UtilImage::Read(PXCImage **image) {
    HRESULT hr;

    PXCSmartPtr<IWICBitmapDecoder> decoder;
    hr=m_pIWICFactory->CreateDecoderFromFilename(filename, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder);
    if (!decoder.IsValid()) return false;
    PXCSmartPtr<IWICBitmapFrameDecode> source;
    hr=decoder->GetFrame(0, &source);
    if (!source.IsValid()) return false;
    UINT width, height;
    hr=source->GetSize(&width, &height);

    PXCSmartPtr<IWICFormatConverter> converter;
    hr=m_pIWICFactory->CreateFormatConverter(&converter);
    if (!converter.IsValid()) return false;
    hr=converter->Initialize(source, GUID_WICPixelFormat32bppBGR, WICBitmapDitherTypeNone, NULL, 0.f,WICBitmapPaletteTypeMedianCut);

    PXCSmartPtr<PXCAccelerator> accelerator;
    m_session->CreateAccelerator(&accelerator);
    if (!accelerator.IsValid()) return false;

    PXCImage::ImageInfo info={width, height, PXCImage::COLOR_FORMAT_RGB32};
    pxcStatus sts=accelerator->CreateImage(&info, 0, 0, image);

    PXCImage::ImageData image_data;
    memset(&image_data, 0, sizeof(image_data));
    sts=(*image)->AcquireAccess(PXCImage::ACCESS_WRITE, 0, &image_data);
    hr=converter->CopyPixels(0, image_data.pitches[0], image_data.pitches[0]*height, image_data.planes[0]);
    sts=(*image)->ReleaseAccess(&image_data);

    return true;
}

bool UtilImage::Write(PXCImage *image) {
    HRESULT hr;
    
    PXCSmartPtr<IWICStream> iStream;
    hr=m_pIWICFactory->CreateStream(&iStream);
    if (!iStream.IsValid()) return false;

    hr = iStream->InitializeFromFilename(filename, GENERIC_WRITE);

    GUID container_format=GUID_ContainerFormatBmp;
    if (wcsstr(filename,L".tif") || wcsstr(filename,L".TIF")) container_format=GUID_ContainerFormatTiff;
    if (wcsstr(filename,L".bmp") || wcsstr(filename,L".BMP")) container_format=GUID_ContainerFormatBmp;
    if (wcsstr(filename,L".png") || wcsstr(filename,L".PNG")) container_format=GUID_ContainerFormatPng;

    PXCSmartPtr<IWICBitmapEncoder> iEncoder;
    hr=m_pIWICFactory->CreateEncoder(container_format, NULL, &iEncoder);
    if (!iEncoder.IsValid()) return false;

    hr=iEncoder->Initialize(iStream, WICBitmapEncoderNoCache);

    PXCSmartPtr<IWICBitmapFrameEncode> iBitmapFrame;
    hr=iEncoder->CreateNewFrame(&iBitmapFrame, NULL);
    if (!iBitmapFrame.IsValid()) return false;

    hr=iBitmapFrame->Initialize(NULL);

    PXCImage::ImageInfo info;
    pxcStatus sts=image->QueryInfo(&info);
    hr=iBitmapFrame->SetSize(info.width,info.height);

    WICPixelFormatGUID format1 = GUID_WICPixelFormat32bppBGRA;
    hr=iBitmapFrame->SetPixelFormat(&format1);

    PXCImage::ImageData image_data;
    sts=image->AcquireAccess(PXCImage::ACCESS_READ,PXCImage::COLOR_FORMAT_RGB32,&image_data);
    hr=iBitmapFrame->WritePixels(info.height,image_data.pitches[0],info.height*image_data.pitches[0],image_data.planes[0]);
    sts=image->ReleaseAccess(&image_data);

    hr=iBitmapFrame->Commit();
    hr=iEncoder->Commit();

    return true;
}
