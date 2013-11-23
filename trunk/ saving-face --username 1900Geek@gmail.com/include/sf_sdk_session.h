#pragma once
#include <windows.h> // Neccessary for Command line
#include <wchar.h> //Required for WChar
#include <conio.h>
#include <stdio.h>
#include "pxcsession.h" //Required To Make Session
#include "pxcsmartptr.h" //Smart pointers for memory management
#include "pxcface.h"
#include "util_cmdline.h" //CmdLine for passing options in... Minimizes Code
#include "util_capture.h" //Allows capture of data streams
#include "util_render.h" //For quick display of feeds
#include "sf_defs.h" //Data types
#include "pxcprojection.h" //To Project Coords to Real-Life and to map depth to image
#include "pxcmetadata.h"   //Necessary for projection

namespace SF
{
	class SF_Session
	{
	public:
	
	//Create the PCSDK Session
	bool createSession();

	//–sdname	Specify an input device name. The default value is DepthSense Device 325.
	//–nframes	Specify the maximum number of frames to render.
	//–csize	    Specify the color picture resolution and frame rate, for example, 640x480x30.
	//–dsize		Specify the depth picture resolution and frame rate, for example, 320x240x30.
	//–file		Specify a file name. Use with –record for recording or alone for playback.
	//–record	Enable the recording mode. Use with –file to specify the recording file name.
	//-load		Load a specific input SDK module into the SDK session.
	bool setOptions(int argc, WCHAR *argv[]);

	//TODO Comment all of these
	SF_STS captureStreams();
	SF_STS loadFaceModule();
	SF_STS createDepthRenderView();
	SF_STS createColorRenderView();
	
	
	//The following are to be replaced by a single function that is well written and includes the following options
	//GetYPR //GetLandmark //Save video //Save Image
	//Following these... A method to compare the saved video to the finished model.
	
	
	void camera_loop
		(
			//Call back to process the YPR, and landmark data.
			void (*yprFunc)(SF_YPR*, SF_R3_COORD*),
			//void (*landMarkFunc)(SF_R3_COORD*),
			//Call back to process a vertex
			void (*processVertex)(SF_R3_COORD&),
			//Call back to a function to save the image
			void (*saveImage)(PXCImage::ImageData&),
			//Call back to specify processing a new frame and give the frame number
			void (*newFrame)(int), 
			//Call back to check to see if a stop condition has been reached
			bool (*continueProcessing)(),
			int numFrames = 0,
			bool multiface = false
			//Add functionality to playback video... (Later)
		);

		SF_Session();
		~SF_Session();

	private:
		SF_STS initLoop();
		SF_R3_COORD *getLandmarkCoord(SF_R3_COORD *landmark);
		void drawCrossHairsOnLandmark(SF_R3_COORD &landmark, PXCImage::ImageData &image);
		SF_STS updateProjections();

		PXCSmartPtr<PXCSession> session;
		PXCSmartPtr<UtilCapture> capture;

		//SDK Easy Render Views...
		PXCSmartPtr<UtilRender> depth_render;
		PXCSmartPtr<UtilRender> uv_render;

		//Face Analysis Module
		PXCSmartPtr<PXCFaceAnalysis> face;
		PXCSmartPtr<PXCFaceAnalysis::Landmark> landmark;
		PXCSmartPtr<PXCFaceAnalysis::Detection> detector;

		PXCSmartPtr<PXCAccelerator> accelerator;

		UtilCmdLine *cmdl;
		PXCCapture::VideoStream::ProfileInfo colorProfile;
		PXCCapture::VideoStream::ProfileInfo depthProfile;

		//Holds depth x,y coords and z value
		PXCPoint3DF32 *depthXYZCoords;
		//Holds R3 Coordinate Projection Data
		PXCPoint3DF32 *depthR3Coords;
		//Holds Conversion from depth XY to Color XY
		PXCPointF32 *depthXYToColorXY; 

		PXCSmartPtr<PXCProjection> projection;
		pxcUID prj_uid;

		int depthWidth;
		int depthHeight;
		int colorWidth;
		int colorHeight;
		int nPointsDepth;
		int nPointsColor;

		pxcF32 depthSaturation;
		pxcF32 depthLowConfidence;
	};

}
