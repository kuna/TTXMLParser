// TTXMLParser.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CTTXMLParserApp:
// �� Ŭ������ ������ ���ؼ��� TTXMLParser.cpp�� �����Ͻʽÿ�.
//

class CTTXMLParserApp : public CWinApp
{
public:
	CTTXMLParserApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CTTXMLParserApp theApp;