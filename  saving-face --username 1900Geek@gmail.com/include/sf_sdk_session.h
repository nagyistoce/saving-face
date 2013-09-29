#pragma once
#include <windows.h> // Neccessary for Command line
#include <wchar.h> //Required for WChar
#include <conio.h>
#include <stdio.h>
#include "pxcsession.h" //Required To Make Session
#include "pxcsmartptr.h" //Smart pointers for memory management
#include "util_cmdline.h" //CmdLine for passing options in... Minimizes Code

namespace SF
{
	class SF_Session
	{
	public:
	PXCSmartPtr<PXCSession> session;
	UtilCmdLine *cmdl;

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
	
	SF_Session();
	~SF_Session();
	
	};
}
