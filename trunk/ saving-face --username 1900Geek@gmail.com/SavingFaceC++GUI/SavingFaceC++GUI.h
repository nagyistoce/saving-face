
// SavingFaceC++GUI.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "global.h"

// CSavingFaceCGUIApp:
// See SavingFaceC++GUI.cpp for the implementation of this class
//

class CSavingFaceCGUIApp : public CWinApp
{
public:
	CSavingFaceCGUIApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CSavingFaceCGUIApp theApp;