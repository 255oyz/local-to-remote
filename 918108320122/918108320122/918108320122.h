
// 918108320122.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy918108320122App:
// �йش����ʵ�֣������ 918108320122.cpp
//

class CMy918108320122App : public CWinApp
{
public:
	CMy918108320122App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy918108320122App theApp;