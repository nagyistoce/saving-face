#include "..\include\sf_sdk_session.h"

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
	
	//This will fail if you do not have the camera.

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
		//Need some error checking here
		session->CreateImpl<PXCFaceAnalysis>(&face);
		PXCFaceAnalysis::ProfileInfo pinfo;
		face->QueryProfile(0,&pinfo);
		//capture->LocateStreams(&pinfo.inputs);
		face->SetProfile(&pinfo);
		detector = face->DynamicCast<PXCFaceAnalysis::Detection>();
		PXCFaceAnalysis::Detection::ProfileInfo dinfo;
		detector->QueryProfile(0,&dinfo);
		detector->SetProfile(&dinfo);

		landmark = face->DynamicCast<PXCFaceAnalysis::Landmark>();
		return SF_STS_OK;
	}

	//Constructor should be no fail.
	SF_Session::SF_Session(void)
	{
		cmdl = 0;
	}


	SF_Session::~SF_Session(void)
	{
		if(cmdl) delete cmdl;
	}

	//Temp Code Must be replaced
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
		//sts=sp->Synchronize();
        if (sts<PXC_STATUS_NO_ERROR) break;

		for (int i=0;;i++) {
			pxcUID fid; pxcU64 ts;
			if (face->QueryFace(i,&fid,&ts)<PXC_STATUS_NO_ERROR) break;
			PXCFaceAnalysis::Detection::Data data;
			detector->QueryData(fid,&data);
			PXCFaceAnalysis::Landmark::LandmarkData ldata;
			landmark->QueryLandmarkData(fid,PXCFaceAnalysis::Landmark::LABEL_NOSE_TIP,0,&ldata);
       
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
}