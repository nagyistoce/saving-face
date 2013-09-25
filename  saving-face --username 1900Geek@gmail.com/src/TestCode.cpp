
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <wchar.h>
#include <vector>
//*
#include <fstream>
#include <sstream>

#include "pxcsession.h"
#include "pxcsmartptr.h"
#include "pxccapture.h"
#include "util_render.h"
#include "util_capture.h"
#include "util_cmdline.h"
#include "pxcprojection.h"
#include "pxcmetadata.h"

int wmain(int argc, WCHAR* argv[]) {
	//A Smart Pointer To Automatically Release Resources
    PXCSmartPtr<PXCSession> session;//A Pointer to hold the session
    pxcStatus sts=PXCSession_Create(&session);//Create the session
    if (sts<PXC_STATUS_NO_ERROR || session==NULL) 
	{//Check to see if the session was created
        wprintf_s(L"Failed to create a session\n");
		return 3;
	}

	/*
	//Prints out Devices
	PXCSession::ImplDesc desc1;
	memset(&desc1,0,sizeof(desc1));
	desc1.group=PXCSession::IMPL_GROUP_SENSOR;
	desc1.subgroup=PXCSession::IMPL_SUBGROUP_VIDEO_CAPTURE;

	for (int m=0;;m++) 
	{
		PXCSession::ImplDesc desc2;
		if (session->QueryImpl(&desc1,m,&desc2)<PXC_STATUS_NO_ERROR) 
			break;
		wprintf_s(L"Module[%d]: %s\n", m, desc2.friendlyName);
		PXCSmartPtr<PXCCapture> capture;
		session->CreateImpl<PXCCapture>(&desc2,&capture);
		for (int d=0;;d++) 
		{
			PXCCapture::DeviceInfo dinfo;
			if (capture->QueryDevice(d,&dinfo)<PXC_STATUS_NO_ERROR) break;
			wprintf_s(L"    Device[%d]: %s\n",d,dinfo.name);
			PXCPointF32 color_fov;
	
	//device->QueryPropertyAsPoint(PXCCapture::Device::PROPERTY_COLOR_FIELD_OF_VIEW,&color_fov);

	//PXCPointF32 depth_fov;

	//device->QueryPropertyAsPoint(PXCCapture::Device::PROPERTY_DEPTH_FIELD_OF_VIEW,&depth_fov);
		}
	}*/


	UtilCmdLine cmdl(session);
	if (!cmdl.Parse(L"-nframes-csize-sdname",argc,argv)) return 3;
    UtilCapture capture(session);
    
    PXCCapture::VideoStream::DataDesc request; 
    memset(&request, 0, sizeof(request)); 
    request.streams[0].format=PXCImage::COLOR_FORMAT_RGB32;
    request.streams[1].format=PXCImage::COLOR_FORMAT_DEPTH;
    sts = capture.LocateStreams (&request);
    if (sts<PXC_STATUS_NO_ERROR) {
        wprintf_s(L"Failed to locate video stream(s)\n");
        return 1;
    }
    
    PXCCapture::VideoStream::ProfileInfo pcolor;
    capture.QueryVideoStream(0)->QueryProfile(&pcolor);
    PXCCapture::VideoStream::ProfileInfo pdepth;
    capture.QueryVideoStream(1)->QueryProfile(&pdepth);

    pxcCHAR line[64];
    swprintf_s(line,sizeof(line)/sizeof(pxcCHAR),L"Depth %dx%d", pdepth.imageInfo.width, pdepth.imageInfo.height);
    UtilRender depth_render(line);
    swprintf_s(line,sizeof(line)/sizeof(pxcCHAR),L"UV %dx%d", pcolor.imageInfo.width, pcolor.imageInfo.height);
    UtilRender uv_render(line);
	swprintf_s(line,sizeof(line)/sizeof(pxcCHAR),L"Projection %dx%d", pcolor.imageInfo.width, pcolor.imageInfo.height);
	UtilRender prj_render(line);

	PXCSmartPtr<PXCProjection> projection;
    PXCSmartPtr<PXCImage> color2;   // the color image after projection
    PXCPoint3DF32 *pos2d = 0;       // array of depth coordinates to be mapped onto color coordinates
    PXCPointF32 *posc = 0;          // array of mapped color coordinates
    pxcF32 dvalues[2] = {-1};       // special depth values for saturated and low-confidence pixels
	pxcUID prj_value;               // projection serializable identifier
	sts=capture.QueryDevice()->QueryPropertyAsUID(PXCCapture::Device::PROPERTY_PROJECTION_SERIALIZABLE,&prj_value);
	if (sts>=PXC_STATUS_NO_ERROR) {
    	capture.QueryDevice()->QueryProperty(PXCCapture::Device::PROPERTY_DEPTH_LOW_CONFIDENCE_VALUE,&dvalues[0]);
    	capture.QueryDevice()->QueryProperty(PXCCapture::Device::PROPERTY_DEPTH_SATURATION_VALUE,&dvalues[1]);

        session->DynamicCast<PXCMetadata>()->CreateSerializable<PXCProjection>(prj_value, &projection);
        PXCSmartPtr<PXCAccelerator> accelerator;
        session->CreateAccelerator(&accelerator);
        accelerator->CreateImage(&pcolor.imageInfo,0,0,&color2);

	    int npoints = pdepth.imageInfo.width*pdepth.imageInfo.height; 
        pos2d=(PXCPoint3DF32 *)new PXCPoint3DF32[npoints];
        posc=(PXCPointF32 *)new PXCPointF32[npoints];
        int k = 0;

		/**
		* make file
		*/
		/*static int incr= 0;//Image number
		std::ofstream arrayData;
		std::stringstream sstrm;
		sstrm << "D:\\dimgd\\test" << incr << ".txt";
		arrayData.open(sstrm.str());
		sstrm.clear();
		incr ++;*/
	    for (float y=0;y<pdepth.imageInfo.height;y++)
		{
			//if(y > 0) arrayData << "\n";
            for (float x=0;x<pdepth.imageInfo.width;x++,k++)
			{
				//if(x > 0) arrayData << ", ";
				//arrayData << pos2d[k].x << ", " <<  pos2d[k].y << ", " << pos2d[k].z;
                pos2d[k].x=x,
				pos2d[k].y=y;
			}
		}
		//arrayData.close();
    }

    for (pxcU32 f=0;f<cmdl.m_nframes;f++) {
        PXCSmartArray<PXCImage> images(2);
        PXCSmartSP sp;
        sts=capture.ReadStreamAsync(images,&sp);
		if (sts<PXC_STATUS_NO_ERROR) break;

        sts=sp->Synchronize();
        if (sts<PXC_STATUS_NO_ERROR) break;
        if (!depth_render.RenderFrame(images[1])) break;

        PXCImage::ImageData ddepth;
        images[1]->AcquireAccess(PXCImage::ACCESS_READ,&ddepth);
        int dwidth2=ddepth.pitches[0]/sizeof(pxcU16); // aligned depth width

        if (projection.IsValid()) {
            color2->CopyData(images[0]);
            PXCImage::ImageData dcolor;
            color2->AcquireAccess(PXCImage::ACCESS_READ_WRITE,PXCImage::COLOR_FORMAT_RGB32,&dcolor);
    	    int cwidth2=dcolor.pitches[0]/sizeof(pxcU32); // aligned color width

		/**
		* make file
		*/
			static int incr= 0;//Image number
			bool bob  =  false;
			int samples = 0;
			std::ofstream arrayData;
			std::stringstream sstrm;
			sstrm << "G:\\camera_uvmap\\test\\test" << incr << ".csv";
			arrayData.open(sstrm.str());
			sstrm.clear();
			incr ++;

		
            for (pxcU32 y=0,k=0;y<pdepth.imageInfo.height;y++)
			{
				//if(y > 0) arrayData << "\n";//KS

                for (pxcU32 x=0;x<pdepth.imageInfo.width;x++,k++){
					//if(x > 0) arrayData << ", ";//KS
				    pos2d[k].z=((short*)ddepth.planes[0])[y*dwidth2+x];
					//arrayData << pos2d[k].x << ", " <<  pos2d[k].y << ", " << pos2d[k].z;//KS
				}
			}
            projection->MapDepthToColorCoordinates(pdepth.imageInfo.width*pdepth.imageInfo.height,pos2d,posc);
		    for (pxcU32 y=0,k=0;y<pdepth.imageInfo.height;y++) {
                //if(y > 0) arrayData << "\n";//KS
				for (pxcU32 x=0;x<pdepth.imageInfo.width;x++,k++) {
                    int xx=(int)(posc[k].x+0.5f), yy= (int) (posc[k].y+0.5f);
				    if (xx<0 || yy<0 || xx>=(int) pcolor.imageInfo.width || yy>=(int)pcolor.imageInfo.height) continue;
                    if (pos2d) if (pos2d[k].z==dvalues[0] || pos2d[k].z==dvalues[1]) continue; // no mapping based on unreliable depth values
	                if(bob) arrayData << "\n"; else bob = true;//KS
					samples++;
					arrayData << pos2d[k].x << ", " <<  pos2d[k].y << ", " << pos2d[k].z;//KS
					((pxcU32 *)dcolor.planes[0])[yy*cwidth2+xx] |= 0x0000FF00;
                }
            }

			arrayData.close();//KS
			
			
			if(samples < 100){//KS
				std::remove(sstrm.str().c_str());//KS
				sstrm.clear();//KS
			}
				

            color2->ReleaseAccess(&dcolor);
 		    if (!prj_render.RenderFrame(color2)) break;
        }

        float *uvmap=(float*)ddepth.planes[2];
        if (uvmap) {
            PXCImage::ImageData dcolor;
            images[0]->AcquireAccess(PXCImage::ACCESS_READ_WRITE,PXCImage::COLOR_FORMAT_RGB32,&dcolor);
    	    int cwidth2=dcolor.pitches[0]/sizeof(pxcU32); // aligned color width

            for (int y=0, k=0;y<(int)pdepth.imageInfo.height;y++) {
                for (int x=0;x<(int)pdepth.imageInfo.width;x++,k++) {
                    int xx=(int)(uvmap[(y*dwidth2+x)*2+0]*pcolor.imageInfo.width+0.5f);
                    int yy=(int)(uvmap[(y*dwidth2+x)*2+1]*pcolor.imageInfo.height+0.5f);
                    if (pos2d) if (pos2d[k].z==dvalues[0] || pos2d[k].z==dvalues[1]) continue; // no mapping based on unreliable depth values
                    if (xx>=0 && xx<(int)pcolor.imageInfo.width && yy>=0 && yy<(int)pcolor.imageInfo.height)
                        ((pxcU32 *)dcolor.planes[0])[yy*cwidth2+xx] |= 0x00FF0000;
                }
            }
       		images[0]->ReleaseAccess(&dcolor);
        }
        if (uvmap) if (!uv_render.RenderFrame(images[0])) break;

        images[1]->ReleaseAccess(&ddepth);
    }

	if (pos2d) delete [] pos2d;
	if (posc) delete [] posc;

    return 0;
}
