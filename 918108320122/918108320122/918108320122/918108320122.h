
// 918108320122.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CMy918108320122App:
// 有关此类的实现，请参阅 918108320122.cpp 
// 22222

class CMy918108320122App : public CWinApp
{
public:
	CMy918108320122App();

// 重写222
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CMy918108320122App theApp;