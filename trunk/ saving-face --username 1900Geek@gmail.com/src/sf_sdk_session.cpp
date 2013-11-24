#include "sf_sdk_session.h"

//Temp includes
#include <fstream>
#include <sstream>
#include <math.h>


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
		capture->QueryVideoStream(0)->QueryProfile(&colorProfile);
		capture->QueryVideoStream(1)->QueryProfile(&depthProfile);
		return SF_STS_OK;
	}

	SF_STS SF_Session::createDepthRenderView(){
		pxcCHAR line[64];
		swprintf_s(line,sizeof(line)/sizeof(pxcCHAR),L"Depth %dx%d", depthProfile.imageInfo.width, depthProfile.imageInfo.height);
		wprintf(line);//Print to Console//Temp for debug
		wprintf(L"\n");
		depth_render = new UtilRender(line);
		//Lazy here should check allocation
		return SF_STS_OK;
	}

	SF_STS SF_Session::createColorRenderView(){
		pxcCHAR line[64];
		swprintf_s(line,sizeof(line)/sizeof(pxcCHAR),L"UV %dx%d", colorProfile.imageInfo.width, colorProfile.imageInfo.height);
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
		//Tune performance here 100 = fastest
		dinfo.responsiveness = 0;
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

	SF_STS SF_Session::initLoop()
	{
		if(face == nullptr) return SF_STS_FAIL;//No point in continuing
        //TODO use accelerator to create images for RGBA32
		session->CreateAccelerator(&accelerator);
		
		depthWidth = depthProfile.imageInfo.width;
		depthHeight = depthProfile.imageInfo.height;
		colorWidth = colorProfile.imageInfo.width;
		colorHeight = colorProfile.imageInfo.height;
		nPointsDepth = depthWidth*depthHeight; 
		nPointsColor = colorWidth*colorHeight;
		
		depthXYZCoords=(PXCPoint3DF32 *)new PXCPoint3DF32[nPointsDepth]; 
		depthR3Coords=(PXCPoint3DF32 *)new PXCPoint3DF32[nPointsDepth];
		depthXYToColorXY=(PXCPointF32 *)new PXCPointF32[nPointsDepth];
		
		
		//Get Confidence values for Depth
		
		capture->QueryDevice()->QueryProperty(PXCCapture::Device::PROPERTY_DEPTH_LOW_CONFIDENCE_VALUE,&depthLowConfidence);
		capture->QueryDevice()->QueryProperty(PXCCapture::Device::PROPERTY_DEPTH_SATURATION_VALUE,&depthSaturation);

		//Initialize projection
		//Fail condition to be dealt with
		if (capture->QueryDevice()->QueryPropertyAsUID(PXCCapture::Device::PROPERTY_PROJECTION_SERIALIZABLE,&prj_uid) < PXC_STATUS_NO_ERROR) return SF_STS_FAIL;
		session->DynamicCast<PXCMetadata>()->CreateSerializable<PXCProjection>(prj_uid, &projection);
		
		//Init Arrays x and y values for color mapped depth coords
		int k = 0;
	    for (float y=0; y< depthHeight; y++)
            for (float x=0; x<depthWidth; x++, k++)
                depthXYZCoords[k].x=x, depthXYZCoords[k].y=y;

		return SF_STS_OK;
	}

	SF_STS SF_Session::updateProjections(){
		if(projection->ProjectImageToRealWorld(
			nPointsDepth,
			depthXYZCoords,
			depthR3Coords)
			 < PXC_STATUS_NO_ERROR) 
			 return SF_STS_FAIL;
		if(projection->MapDepthToColorCoordinates(
			nPointsDepth,
			depthXYZCoords,
			depthXYToColorXY
			) < PXC_STATUS_NO_ERROR) 
			return SF_STS_FAIL;
		return SF_STS_OK;
	}
	
	SF_R3_COORD *SF_Session::getLandmarkCoord(SF_R3_COORD *landmark){
		SF_R3_COORD *lm = nullptr;

#define _LM_SIMPLE
//#define _LM_DIRECT		
#ifdef _LM_DIRECT
		lm = &depthR3Coords[(depthWidth) * (int)(landmark->y/2) + (int)(landmark->x/2)];
#endif				
		
#ifdef _LM_SIMPLE
		float acceptableErr = 2;
		PXCPointF32 lmT;
		//Naive approach... will find if it exists.
		int coord = 0;
		for(coord = 0; coord < nPointsDepth; coord++){
			 lmT = depthXYToColorXY[coord];
			 if(abs(lmT.x - landmark->x) < acceptableErr && abs(lmT.y - landmark->y) < acceptableErr)
				 break;
 		}
		if(coord < nPointsDepth)
			lm = &depthR3Coords[coord];
		else return nullptr;
		
		int radius = 10;
		int y,x, coordTemp, smallestCoord;
		float smallestDepth = 20;

		for(y = -radius; y < radius; y++)
			for(x = -radius; x < radius; x++){
				coordTemp = coord + y*depthWidth + x;
				if (depthR3Coords[coordTemp].z < smallestDepth)
				{
					//Find and return smallest;
					smallestDepth = depthR3Coords[coordTemp].z;
					lm = &depthR3Coords[coordTemp];
				}
			}

#endif
		//This is where we can offer improvements of the pixel based algorithm using the depth coords.
		//This is specific to the nose and should be relocated later.
		//Step 1: Steal the underpants.
		//Step 3: Profit.... oops wrong plan

		//Step 1: select the smallest (Closest to the camera Z-Value in Y) within say +-7 pixels.
		//Step 2: select the median/mean X value...(this one is actually kind of tricky and should
		//	be rotated first... Hold off on that one.

		return lm;
	}

	void SF_Session::drawCrossHairsOnLandmark(SF_R3_COORD &landmark, PXCImage::ImageData &image)
	{
		int drawLength = 10;
		int colorByteWidth=image.pitches[0]; // aligned color width
		for(int i = (((int)landmark.x -drawLength)*3<0?0:((int)landmark.x -drawLength)*3); i < colorByteWidth && i < ((int)landmark.x + drawLength)*3; i++)
			image.planes[0][((int)(landmark.y)* colorByteWidth)+ i] = 0xFF;
		for(int i = (((int)landmark.y -drawLength)<0?0:((int)landmark.y -drawLength)); i < colorByteWidth && i < ((int)landmark.y + drawLength); i++){
			image.planes[0][i*colorByteWidth+ (int)(landmark.x)*3] = 0xFF;
			image.planes[0][i*colorByteWidth+ (int)(landmark.x)*3+1] = 0xFF;
			image.planes[0][i*colorByteWidth+ (int)(landmark.x)*3+2] = 0xFF;
		}
	}

	//Hard coded for temporary testing
	//There is a code sample for video recording called camera_viewer
	void SF_Session::saveVideo(string dir, string fileName)
	{
		//Change to inputs.
		makeDirectory("recordedvideo");
		string path = getFullPath("recordedvideo");
		
		size_t newsize = path.size() + 1;
		wchar_t * widePath = new wchar_t[newsize];
		size_t convertedChars = 0;
		mbstowcs_s(&convertedChars, widePath, newsize, path.c_str(), _TRUNCATE);
		
		//The docs say the arguements are as follows yet this line gives errors.  :/
		//Error caused by const wchar_t * ditch the const.
		UtilCaptureFile *utilCaptureFile = new UtilCaptureFile(session, widePath, true);
		
		
		 /*for (std::list<std::pair<PXCSizeU32,pxcU32>>::iterator itrc=cmdl.m_csize.begin();itrc!=cmdl.m_csize.end();itrc++)
        capture.SetFilter(PXCImage::IMAGE_TYPE_COLOR,itrc->first,itrc->second);
		 for (std::list<std::pair<PXCSizeU32,pxcU32>>::iterator itrd=cmdl.m_dsize.begin();itrd!=cmdl.m_dsize.end();itrd++)
        capture.SetFilter(PXCImage::IMAGE_TYPE_DEPTH,itrd->first,itrd->second);*/

		//delete[] arg2;
	}

	void SF_Session::camera_loop
		(
			void (*yprFunc)(SF_YPR*, SF_R3_COORD*),
			void (*processVertex)(SF_R3_COORD&),
			void (*saveImage)(PXCImage::ImageData&),
			void (*newFrame)(int), 
			bool (*continueProcessing)(),
			int numFrames,
			string videoFileName,
			bool multiface
		)	
	{
		//TODO::If needed add support to determine own nose coord and YPR
		//TODO::Add support for save image... Should save only on last frame.
		//TODO::(Later)...implement in seperate class...Compare multiple faces in the same frame.
		//TODO::(RE-FACTOR)... this will be a messy function anyways, but clean it up.
		//TODO::Ensure ypr and landmark are valid... If not decrement frame count and continue.
		if(initLoop() < SF_STS_OK) return;//Loop Initialization Failed
		if(videoFileName != "")
			saveVideo("","");
		//Begin Loop
		//Make num frames an argument parameter
		for (pxcU32 f=0;(numFrames == 0)?true:f < numFrames;) {
			PXCSmartArray<PXCImage> images(2);
			PXCSmartSPArray sp(2);//Synchronous Pointer
			
			//ReadStream If Data Available or Block
			if (capture->ReadStreamAsync(images, &sp[0])<PXC_STATUS_NO_ERROR) break;
			
			//Process Face YPR and Landmarks
			face->ProcessImageAsync(images,&sp[1]);//TODO Check return status. If Fail continue
			//Wait for all ASynchronous Modules To Return
			if (sp.SynchronizeEx()<PXC_STATUS_NO_ERROR) continue;
			
			PXCImage::ImageData depthImageData;
			images[1]->AcquireAccess(PXCImage::ACCESS_READ,&depthImageData);
			int dwidth2=depthImageData.pitches[0]/sizeof(pxcU16);

			for (pxcU32 y=0,k=0;y<depthHeight;y++)
				for (pxcU32 x=0;x<depthWidth;x++,k++)
				    depthXYZCoords[k].z=((short*)depthImageData.planes[0])[y*dwidth2+x];

			if(updateProjections() < SF_STS_OK) continue;
			
			//Begin Processing Image by face.
			for (int i=0;multiface?true:i<1;i++) {
				pxcUID fid; 
				pxcU64 ts;
				//To limit num faces i = 0;
				if (face->QueryFace(i,&fid,&ts)<PXC_STATUS_NO_ERROR) break;//No more faces
				PXCFaceAnalysis::Detection::Data data;
				detector->QueryData(fid,&data);
				PXCFaceAnalysis::Landmark::LandmarkData ldata[7];
				PXCFaceAnalysis::Landmark::PoseData pdata;
			       
				landmark->QueryLandmarkData(fid,PXCFaceAnalysis::Landmark::LABEL_7POINTS,ldata);//Check Return Status and Break
				landmark->QueryPoseData(fid, &pdata);//Check Return Status and Break
				
				if(pdata.yaw<-1000)//Did not get quality data.
					continue;
				
				//This is not working... What is wrong.
				SF_R3_COORD *nose;
				nose = getLandmarkCoord(&ldata[6].position);
				if(nose == nullptr) continue;

				PXCImage::ImageData colorData;
				//Temp Draw Nose on Color
				//Note that the current format is RGB24 we want RGB32
				images[0]->AcquireAccess(PXCImage::ACCESS_READ_WRITE,&colorData);
				drawCrossHairsOnLandmark(ldata[6].position, colorData);
				//drawCrossHairsOnLandmark(ldata[5].position, colorData);
				//drawCrossHairsOnLandmark(ldata[4].position, colorData);
				//drawCrossHairsOnLandmark(ldata[3].position, colorData);
				drawCrossHairsOnLandmark(ldata[2].position, colorData);
				//drawCrossHairsOnLandmark(ldata[1].position, colorData);
				drawCrossHairsOnLandmark(ldata[0].position, colorData);
				images[0]->ReleaseAccess(&colorData);
				

				//Verify All items needed for gaurenteed success before proceding.
				++f;
				//Note::Consider if there is more than one face... HAHA you would get BradJolina
				if(newFrame) newFrame(f);
				
				yprFunc(&pdata,nose);
				
				//Process individual points
				//Huge efficiancy can be gained by subsetting the data to relavent area
				//Based on the relative position of the facial features.
				//Add checks to make sure pos3d never goes out with a bad value
				for (pxcU32 y=0,k=0;y<depthHeight;y++) {
					for (pxcU32 x=0;x<depthWidth;x++,k++) {
						int xx=(int)(depthXYToColorXY[k].x+0.5f), yy= (int) (depthXYToColorXY[k].y+0.5f);
						if (xx<0 || yy<0 || xx>=(int) colorWidth || yy >=(int)colorHeight) continue;//Currently this line does nothing.
						if (depthXYZCoords) if (depthXYZCoords[k].z==depthLowConfidence || depthXYZCoords[k].z==depthSaturation) continue;
						processVertex(depthR3Coords[k]);
					}
				}
			}
			
			//Render the Depth Image
			if (!depth_render->RenderFrame(images[1])) break;
			if (!uv_render->RenderFrame(images[0])) break;

			//Check for terminating condition
			if(continueProcessing)
				if(!continueProcessing())
					break;
		}
		
	}

}