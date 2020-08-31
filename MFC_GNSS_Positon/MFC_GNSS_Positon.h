
// MFC_GNSS_Positon.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFC_GNSS_PositonApp:
// See MFC_GNSS_Positon.cpp for the implementation of this class
//

class CMFC_GNSS_PositonApp : public CWinApp
{
public:
	CMFC_GNSS_PositonApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFC_GNSS_PositonApp theApp;