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

namespace SF
{
	class SF_Session
	{
	public:
	
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
	PXCCapture::VideoStream::ProfileInfo pcolor;
	PXCCapture::VideoStream::ProfileInfo pdepth;
	

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
	//The following are to be replaced
	void tempMainLoop();
	void tempYPRLoop(void (*yprFunc)(SF_YPR*),void (*landMarkFunc)(SF_R3_COORD*));
	void tempGetVertices(void (*yprFunc)(SF_YPR*),void (*landMarkFunc)(SF_R3_COORD*),void (*getdepth)(const char *test));
	void mathematicaFriendlyFileOut();

	//Figure out arguements
	void getDepthDataFromVertices();

	SF_Session();
	~SF_Session();
	};
}
