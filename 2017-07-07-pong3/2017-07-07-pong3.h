
// 2017-07-07-pong3.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Pong:
// See 2017-07-07-pong3.cpp for the implementation of this class
//

class Pong : public CWinApp
{
public:
	Pong();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Pong theApp;