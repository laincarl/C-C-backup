
// try2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Ctry2App: 
// �йش����ʵ�֣������ try2.cpp
//

class Ctry2App : public CWinApp
{
public:
	Ctry2App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Ctry2App theApp;