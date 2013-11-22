#include "sf_sdk_session.h"

//Temp includes
#include <fstream>
#include <sstream>
#include "pxcprojection.h" //To Project Coords to Real-Life and to map depth to image
#include "pxcmetadata.h"   //Necessary for projection

namespace SF
{
	bool SF_Session::createSession()
	{
		pxcStatus sts=PXCSession_Create(&session);
		if (sts<PXC_STATUS_NO_ERROR || session==NULL) {
			wprintf_s(L"Failed to create a session\n");
			return false;
		}
		return true;
	}

	//–sdname	Specify an input device name. The default value is DepthSense Device 325.
	//–nframes	Specify the maximum number of frames to render.
	//–csize	    Specify the color picture resolution and frame rate, for example, 640x480x30.
	//–dsize		Specify the depth picture resolution and frame rate, for example, 320x240x30.
	//–file		Specify a file name. Use with –record for recording or alone for playback.
	//–record	Enable the recording mode. Use with –file to specify the recording file name.
	//-load		Load a specific input SDK module into the SDK session.
	
	
	bool SF_Session::setOptions(int argc, WCHAR *argv[])
	{
		//Set Options
		cmdl = new UtilCmdLine(session);
		if (!cmdl->Parse(L"-nframes-csize-sdname",argc,argv)) return false;
		return true;
	}
	
	

	SF_STS SF_Session::captureStreams(){
		PXCCapture::VideoStream::DataDesc request; 
		memset(&request, 0, sizeof(request)); 
		//Setup To Request Data Streams
		request.streams[0].format=PXCImage::COLOR_FORMAT_RGB32;
		request.streams[1].format=PXCImage::COLOR_FORMAT_DEPTH;
		//Submit Request to capture streams
		capture = new UtilCapture(session);
		pxcStatus sts = capture->LocateStreams (&request);
		if (sts<PXC_STATUS_NO_ERROR) {
			wprintf_s(L"Failed to locate video stream(s)\n");
			return SF_STS_FAIL_STREAMS;
		}
		//Get Stream profile info
		//Should be moved to its own function to account for changes at runtime
		//If the previous code did not fail this will succeed.
		capture->QueryVideoStream(0)->QueryProfile(&pcolor);
		capture->QueryVideoStream(1)->QueryProfile(&pdepth);
		return SF_STS_OK;
	}

	SF_STS SF_Session::createDepthRenderView(){
		pxcCHAR line[64];
		swprintf_s(line,sizeof(line)/sizeof(pxcCHAR),L"Depth %dx%d", pdepth.imageInfo.width, pdepth.imageInfo.height);
		wprintf(line);//Print to Console//Temp for debug
		wprintf(L"\n");
		depth_render = new UtilRender(line);
		//Lazy here should check allocation
		return SF_STS_OK;
	}

	SF_STS SF_Session::createColorRenderView(){
		pxcCHAR line[64];
		swprintf_s(line,sizeof(line)/sizeof(pxcCHAR),L"UV %dx%d", pcolor.imageInfo.width, pcolor.imageInfo.height);
		wprintf(line);//Temp for debug
		wprintf(L"\n");
		uv_render = new UtilRender(line);
		//Lazy here should check allocation
		return SF_STS_OK;
	}
	
	SF_STS SF_Session::loadFaceModule(){
	
		session->CreateImpl<PXCFaceAnalysis>(&face);
		PXCFaceAnalysis::ProfileInfo pinfo;
		face->QueryProfile(0,&pinfo);
		
		face->SetProfile(&pinfo);
		detector = face->DynamicCast<PXCFaceAnalysis::Detection>();
		PXCFaceAnalysis::Detection::ProfileInfo dinfo;
		dinfo.responsiveness = 50;
		detector->QueryProfile(0,&dinfo);
		detector->SetProfile(&dinfo);
		landmark = face->DynamicCast<PXCFaceAnalysis::Landmark>();
		PXCFaceAnalysis::Landmark::ProfileInfo lInfo={0};
		landmark->QueryProfile(1, &lInfo);
		lInfo.labels = PXCFaceAnalysis::Landmark::LABEL_7POINTS;
		landmark->SetProfile(&lInfo);

		return SF_STS_OK;
	}

	
	SF_Session::SF_Session(void)
	{
		cmdl = 0;
	}


	SF_Session::~SF_Session(void)
	{
		if(cmdl) delete cmdl;
	}

	//Use this as a template for other functions. Like detect or build model.
	//Raw Model for detection and Model Capture
	//Currently all it does is display the feeds
	void SF_Session::tempMainLoop()
	{
		//Currently set to iterate over 200 frames.
		for (pxcU32 f=0;f<200;f++) {
			//Create 2 image instances
			//Should auto delete as it goes out of scope...
			//Consider moving to a local variable to eleminate repetitive allocation.
			PXCSmartArray<PXCImage> images(2);

			//Synchronous Pointer
			PXCSmartSPArray sp(2);
			//ReadStream If Data Available or Block
			pxcStatus sts = capture->ReadStreamAsync(images, &sp[0]);
			if (sts<PXC_STATUS_NO_ERROR) break;
		
			if(face)
				face->ProcessImageAsync(images,&sp[1]);
		
			//Wait for all ASynchronous Modules To Return
			sts=sp.SynchronizeEx();
		
			if (sts<PXC_STATUS_NO_ERROR) break;

			for (int i=0;;i++) {
				pxcUID fid; pxcU64 ts;
				if (face->QueryFace(i,&fid,&ts)<PXC_STATUS_NO_ERROR) break;
				PXCFaceAnalysis::Detection::Data data;
				detector->QueryData(fid,&data);
				PXCFaceAnalysis::Landmark::LandmarkData ldata;
				PXCFaceAnalysis::Landmark::PoseData pdata;
			       
				landmark->QueryLandmarkData(fid,PXCFaceAnalysis::Landmark::LABEL_NOSE_TIP,0,&ldata);
				landmark->QueryPoseData(fid, &pdata);
				/****
				This is where we would put in the calls to our SF Module.
				Please use function calls instead of writing the code inline.
				You can however inline the functions.
				****/

				//Use the detector to limit the input pixels
				//Use the landmark to get Yaw Pitch Roll and the center coord.
			}
			//Render the Depth Image
			if (!depth_render->RenderFrame(images[1])) break;
			if (!uv_render->RenderFrame(images[0])) break;
		}
	}

	void SF_Session::tempYPRLoop(void (*yprFunc)(SF_YPR*),void (*landMarkFunc)(SF_R3_COORD*))
	{
		for (pxcU32 f=0;f<255;f++) {//Currently set to iterate over 255 frames.
			//Create 2 image instances
			PXCSmartArray<PXCImage> images(2);//Consider moving to a local variable to eleminate repetitive allocation.
	
			PXCSmartSPArray sp(2);//Synchronous Pointer

			pxcStatus sts = capture->ReadStreamAsync(images, &sp[0]);//ReadStream If Data Available or Block
			if (sts<PXC_STATUS_NO_ERROR) break;
			if(face)
				face->ProcessImageAsync(images,&sp[1]);

			//Wait for all ASynchronous Modules To Return
			sts=sp.SynchronizeEx();
		
			if (sts<PXC_STATUS_NO_ERROR) break;

			for (int i=0;;i++) {
				pxcUID fid; pxcU64 ts;
				if (face->QueryFace(i,&fid,&ts)<PXC_STATUS_NO_ERROR) break;
				PXCFaceAnalysis::Detection::Data data;
				detector->QueryData(fid,&data);
				PXCFaceAnalysis::Landmark::LandmarkData ldata[7];
				PXCFaceAnalysis::Landmark::PoseData pdata;
			       
				landmark->QueryLandmarkData(fid,PXCFaceAnalysis::Landmark::LABEL_7POINTS,ldata);
				landmark->QueryPoseData(fid, &pdata);
				
				/**Return ypr**/
				yprFunc(&pdata);
				landMarkFunc(&ldata[6].position);
			}
			//Render the Depth Image
			if (!depth_render->RenderFrame(images[1])) break;
			if (!uv_render->RenderFrame(images[0])) break;
		}
	}

	void SF_Session::tempGetVertices(void (*yprFunc)(SF_YPR*),void (*landMarkFunc)(SF_R3_COORD*),void (*getdepth)(const char *test))
	{
		if(face == nullptr) return;//No point in continuing
        session->CreateAccelerator(&accelerator);
		
		//Create arrays to hold the data
		PXCPoint3DF32 *pos2d = 0, *pos3d = 0;
		PXCPointF32 *posc = 0;
		int npoints = pdepth.imageInfo.width*pdepth.imageInfo.height; //Num points from Depth Feed
		pos2d=(PXCPoint3DF32 *)new PXCPoint3DF32[npoints]; 
		pos3d=(PXCPoint3DF32 *)new PXCPoint3DF32[npoints];
		posc=(PXCPointF32 *)new PXCPointF32[npoints];
		
		//Get Confidence values for Depth
		pxcF32 dvalues[2] = {-1};
    	capture->QueryDevice()->QueryProperty(PXCCapture::Device::PROPERTY_DEPTH_LOW_CONFIDENCE_VALUE,&dvalues[0]);
    	capture->QueryDevice()->QueryProperty(PXCCapture::Device::PROPERTY_DEPTH_SATURATION_VALUE,&dvalues[1]);

		//Initialize projection
		PXCSmartPtr<PXCProjection> projection;
		pxcUID prj_value;
		
		//Fail condition to be dealt with
		if (capture->QueryDevice()->QueryPropertyAsUID(PXCCapture::Device::PROPERTY_PROJECTION_SERIALIZABLE,&prj_value) < PXC_STATUS_NO_ERROR) return;
		session->DynamicCast<PXCMetadata>()->CreateSerializable<PXCProjection>(prj_value, &projection);
		
		//Init Arrays x and y values for color mapped depth coords
		int k = 0;
	    for (float y=0;y<pdepth.imageInfo.height;y++)
            for (float x=0;x<pdepth.imageInfo.width;x++,k++)
                pos2d[k].x=x, pos2d[k].y=y;

		//Begin Loop
		//Make num frames an argument parameter
		for (pxcU32 f=0;f<10;f++) {

			PXCSmartArray<PXCImage> images(2);//Consider moving to a local variable to eleminate repetitive allocation.
	
			PXCSmartSPArray sp(2);//Synchronous Pointer
			
			//ReadStream If Data Available or Block
			if (capture->ReadStreamAsync(images, &sp[0])<PXC_STATUS_NO_ERROR) break;
			
			//Process Face YPR and Landmarks
			if(face)
				face->ProcessImageAsync(images,&sp[1]);

			//Wait for all ASynchronous Modules To Return
			if (sp.SynchronizeEx()<PXC_STATUS_NO_ERROR) continue;
			
			PXCImage::ImageData ddepth;
				images[1]->AcquireAccess(PXCImage::ACCESS_READ,&ddepth);
				int dwidth2=ddepth.pitches[0]/sizeof(pxcU16);

            for (pxcU32 y=0,k=0;y<pdepth.imageInfo.height;y++)
                for (pxcU32 x=0;x<pdepth.imageInfo.width;x++,k++)
				    pos2d[k].z=((short*)ddepth.planes[0])[y*dwidth2+x];

			//Put projection in RealWorld Coords
			projection->ProjectImageToRealWorld(pdepth.imageInfo.width*pdepth.imageInfo.height,pos2d,pos3d);
			
			//Map depth to Color
			projection->MapDepthToColorCoordinates(pdepth.imageInfo.width*pdepth.imageInfo.height,pos2d,posc);
		
			//Begin Processing Image by face.
			for (int i=0;;i++) {
				pxcUID fid; 
				pxcU64 ts;
				//To limit num faces i = 0;
				if (face->QueryFace(i,&fid,&ts)<PXC_STATUS_NO_ERROR) break;//No more faces
				PXCFaceAnalysis::Detection::Data data;
				detector->QueryData(fid,&data);
				PXCFaceAnalysis::Landmark::LandmarkData ldata[7];
				PXCFaceAnalysis::Landmark::PoseData pdata;
			       
				landmark->QueryLandmarkData(fid,PXCFaceAnalysis::Landmark::LABEL_7POINTS,ldata);
				landmark->QueryPoseData(fid, &pdata);
				
				//**Return ypr**
				yprFunc(&pdata);
				landMarkFunc(&ldata[6].position);//Nose
				
				
				//PXCSmartPtr<PXCImage> color2;

				//The following code is just prototyping... and will be replaced
				//accelerator->CreateImage(&pcolor.imageInfo,0,0,&color2);
				//PXCImage::ImageData dcolor;
				
				std::string str;
				/*for (pxcU32 y=0,k=0;y<pdepth.imageInfo.height;y++){
					str += "\n";
					for (pxcU32 x=0;x<pdepth.imageInfo.width;x++,k++)
					{
						char temp[10];
						sprintf_s(temp,10,"%d ", ((short*)ddepth.planes[0])[y*dwidth2+x]);
						str.append(temp);
					}					
				}*/
				
				
				//Process individual points
				//Huge efficiancy can be gained by subsetting the data to relavent area
				//Based on the relative position of the facial features.
				for (pxcU32 y=0,k=0;y<pdepth.imageInfo.height;y++) {
					{
						//Temp
						str.append("\n");
					for (pxcU32 x=0;x<pdepth.imageInfo.width;x++,k++) {
						int xx=(int)(posc[k].x+0.5f), yy= (int) (posc[k].y+0.5f);
						if (xx<0 || yy<0 || xx>=(int) pcolor.imageInfo.width || yy>=(int)pcolor.imageInfo.height) continue;
						if (pos2d) if (pos2d[k].z==dvalues[0] || pos2d[k].z==dvalues[1]) continue; // no mapping based on unreliable depth values
						//((pxcU32 *)dcolor.planes[0])[yy*cwidth2+xx] |= 0x0000FF00;
						//arrayData << pos3d[k].x << ", " <<  pos3d[k].y << ", " << pos3d[k].z << "\n";//KS write to file
						//*** This is where you send a coordinate for processing **
						char temp[40];
						sprintf_s(temp,40,"(%f, %f, %f) ",  pos3d[k].x,  pos3d[k].y,  pos3d[k].z);
						str.append(temp);
					}	
					}
				}
				getdepth(str.c_str());
			}
			
			//Render the Depth Image
			if (!depth_render->RenderFrame(images[1])) break;
			if (!uv_render->RenderFrame(images[0])) break;

		}
		
	}

	//TODO figure out arguements and return
	//void SF_Session::getDepthDataFromVertices()
	//{

	//}
	

}