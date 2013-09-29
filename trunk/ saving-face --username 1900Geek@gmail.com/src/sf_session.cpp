#include <windows.h> // Neccessary for Command line
#include <wchar.h> //Required for WChar
#include <conio.h>
#include <stdio.h>


#include "pxcsession.h" //Required To Make Session
#include "pxcsmartptr.h" //Smart pointers for memory management
#include "util_cmdline.h" //CmdLine for passing options in... Minimizes Code



PXCSmartPtr<PXCSession> session;
UtilCmdLine *cmdl;

//Create the PCSDK Session
