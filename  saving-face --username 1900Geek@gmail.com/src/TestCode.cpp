#include "Testing.h"
#ifdef _TEST_CODE
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
#include "util_pipeline.h"//To grab the nose landmark
#include "pxcprojection.h" //To Project Coords to Real-Life and to map depth to image
#include "pxcmetadata.h" 





int wmain(int argc, WCHAR* argv[]) {
	//Create the SDK Session
    PXCSmartPtr<PXCSession> session;
    pxcStatus sts=PXCSession_Create(&session);
    if (sts<PXC_STATUS_NO_ERROR || session==NULL) {
        wprintf_s(L"Failed to create a session\n");
        return 3;
    }

	UtilCmdLine cmdl(session);
	if (!cmdl.Parse(L"-nframes-csize-sdname",argc,argv)) return 3;

	//Util Capture interface hides some of the nasty bits
    UtilCapture capture(session);
    
	//Create a request
    PXCCapture::VideoStream::DataDesc request; 
    memset(&request, 0, sizeof(request)); 

	//Setup To Request Data Streams
    request.streams[0].format=PXCImage::COLOR_FORMAT_RGB32;
    request.streams[1].format=PXCImage::COLOR_FORMAT_DEPTH;
    
	//Submit Request to capture streams
	sts = capture.LocateStreams (&request);
    if (sts<PXC_STATUS_NO_ERROR) {
        wprintf_s(L"Failed to locate video stream(s)\n");
        return 1;
    }
    
    //Get Stream Info For Color
	PXCCapture::VideoStream::ProfileInfo pcolor;
    capture.QueryVideoStream(0)->QueryProfile(&pcolor);

	//Get Stream Info For Depth
    PXCCapture::VideoStream::ProfileInfo pdepth;
    capture.QueryVideoStream(1)->QueryProfile(&pdepth);

	//Make Render View For Depth
    pxcCHAR line[64];
    swprintf_s(line,sizeof(line)/sizeof(pxcCHAR),L"Depth %dx%d", pdepth.imageInfo.width, pdepth.imageInfo.height);
	wprintf(line);//Print to Console
	wprintf(L"\n");
    UtilRender depth_render(line);

    //Make Render View For UV Overlay
	swprintf_s(line,sizeof(line)/sizeof(pxcCHAR),L"UV %dx%d", pcolor.imageInfo.width, pcolor.imageInfo.height);
    UtilRender uv_render(line);
	wprintf(line);
	wprintf(L"\n");

	//Make Render View For Color Data
	wprintf_s(line,sizeof(line)/sizeof(pxcCHAR),L"Projection %dx%d", pcolor.imageInfo.width, pcolor.imageInfo.height);
	wprintf(line);
	wprintf(L"\n");
	UtilRender prj_render(line);

	//TEMP NOTE: YOU ARE HERE

	PXCSmartPtr<PXCProjection> projection;	// determines what projection to apply
    PXCSmartPtr<PXCImage> color2;			// the color image after projection
    PXCPoint3DF32 *pos2d = 0;				// array of depth coordinates to be mapped onto color coordinates
    PXCPointF32 *posc = 0;					// array of mapped color coordinates
    pxcF32 dvalues[2] = {-1};				// special depth values for saturated and low-confidence pixels
	pxcUID prj_value;						// projection serializable identifier
	
	//Keith begin
	 PXCPoint3DF32 *pos3d = 0;				//3D Real world Depth coordinates
	//Keith End
	
	//Get Projection Unique ID
	sts=capture.QueryDevice()->QueryPropertyAsUID(PXCCapture::Device::PROPERTY_PROJECTION_SERIALIZABLE,&prj_value);
	
	if (sts>=PXC_STATUS_NO_ERROR) {
		//Get Confidence values for Depth
    	capture.QueryDevice()->QueryProperty(PXCCapture::Device::PROPERTY_DEPTH_LOW_CONFIDENCE_VALUE,&dvalues[0]);
    	capture.QueryDevice()->QueryProperty(PXCCapture::Device::PROPERTY_DEPTH_SATURATION_VALUE,&dvalues[1]);

        //Create a projection with UID
		session->DynamicCast<PXCMetadata>()->CreateSerializable<PXCProjection>(prj_value, &projection);
        
		//Create an Accelerator
		PXCSmartPtr<PXCAccelerator> accelerator;
        session->CreateAccelerator(&accelerator);

		//Create an image instance to hold the Color Data
        accelerator->CreateImage(&pcolor.imageInfo,0,0,&color2);

		
	    int npoints = pdepth.imageInfo.width*pdepth.imageInfo.height; //Num points from Depth Feed
        
		pos2d=(PXCPoint3DF32 *)new PXCPoint3DF32[npoints]; 
		
		//Keith begin
		pos3d=(PXCPoint3DF32 *)new PXCPoint3DF32[npoints];//Array To Hold 3D Mapped Coords
        //Keith end

		posc=(PXCPointF32 *)new PXCPointF32[npoints];
        
		//Init Arrays x and y values for color mapped depth coords
		int k = 0;
	    for (float y=0;y<pdepth.imageInfo.height;y++)
            for (float x=0;x<pdepth.imageInfo.width;x++,k++)
                pos2d[k].x=x, pos2d[k].y=y;
    }

	//Begin Main Loop
    for (pxcU32 f=0;f<cmdl.m_nframes;f++) {
        //Create 2 image instances
		PXCSmartArray<PXCImage> images(2);

		//Synchronous Pointer
        PXCSmartSP sp;
		//ReadStream If Data Available or Block
        sts=capture.ReadStreamAsync(images,&sp);
		if (sts<PXC_STATUS_NO_ERROR) break;
		
		//Wait for all ASynchronous Modules To Return
        sts=sp->Synchronize();
        if (sts<PXC_STATUS_NO_ERROR) break;
       
		//Render the Depth Image
		if (!depth_render.RenderFrame(images[1])) break;

		//Get Read access to the Depth Image
        PXCImage::ImageData ddepth;
        images[1]->AcquireAccess(PXCImage::ACCESS_READ,&ddepth);

		//
        int dwidth2=ddepth.pitches[0]/sizeof(pxcU16); // aligned depth width

		//Copy Color Data
        if (projection.IsValid()) {
            color2->CopyData(images[0]);
            PXCImage::ImageData dcolor;
            color2->AcquireAccess(PXCImage::ACCESS_READ_WRITE,PXCImage::COLOR_FORMAT_RGB32,&dcolor);
    	    int cwidth2=dcolor.pitches[0]/sizeof(pxcU32); // aligned color width

            for (pxcU32 y=0,k=0;y<pdepth.imageInfo.height;y++)
                for (pxcU32 x=0;x<pdepth.imageInfo.width;x++,k++)
				    pos2d[k].z=((short*)ddepth.planes[0])[y*dwidth2+x];
            
			
			//Keith begin
			//Set up and open file stream, temp for Mathematica
			static int incr= 0;//Image number
			bool bob  =  false;
			int samples = 0;
			std::ofstream arrayData;
			std::stringstream sstrm;
			sstrm << "test\\test_1_" << incr << ".csv";
			arrayData.open(sstrm.str());
			sstrm.clear();
			incr ++;

			/** For Color Images
			planes[0] stores color Data
			**/
			/** For Depth Images
			planes[0] stores DEPTHMAP data or VERTICES data
			planes[1] stores CONFIDENCEMAP data
			planes[2] stores UVMAP data
			**/

			//Map depth to real world
			projection->ProjectImageToRealWorld(pdepth.imageInfo.width*pdepth.imageInfo.height,pos2d,pos3d);

			
			//Map depth to Color
			projection->MapDepthToColorCoordinates(pdepth.imageInfo.width*pdepth.imageInfo.height,pos2d,posc);
			for (pxcU32 y=0,k=0;y<pdepth.imageInfo.height;y++) {
                for (pxcU32 x=0;x<pdepth.imageInfo.width;x++,k++) {
						//wprintf(L"%f,%f,%f", pos3d[k].x,pos3d[k].y,pos3d[k].z);
                    int xx=(int)(posc[k].x+0.5f), yy= (int) (posc[k].y+0.5f);
				    if (xx<0 || yy<0 || xx>=(int) pcolor.imageInfo.width || yy>=(int)pcolor.imageInfo.height) continue;
                    if (pos2d) if (pos2d[k].z==dvalues[0] || pos2d[k].z==dvalues[1]) continue; // no mapping based on unreliable depth values
					((pxcU32 *)dcolor.planes[0])[yy*cwidth2+xx] |= 0x0000FF00;


					arrayData << pos3d[k].x << ", " <<  pos3d[k].y << ", " << pos3d[k].z << "\n";//KS write to file
					
                }
			}
			arrayData.close();//Close the file

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
	if (pos3d) delete [] pos3d;

    return 0;
}
#endif //_TEST_CODE
