// SizeFrm.cpp : implementation file
//

#include "stdafx.h"
#include "TTXMLParser.h"
#include "SizeFrm.h"


// CSizeFrm dialog

IMPLEMENT_DYNAMIC(CSizeFrm, CDialog)

CSizeFrm::CSizeFrm(CWnd* pParent /*=NULL*/)
	: CDialog(CSizeFrm::IDD, pParent)
{

}

CSizeFrm::~CSizeFrm()
{
}

void CSizeFrm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_size);
}


BEGIN_MESSAGE_MAP(CSizeFrm, CDialog)
	ON_BN_CLICKED(IDOK, &CSizeFrm::OnBnClickedOk)
END_MESSAGE_MAP()


// CSizeFrm message handlers

void CSizeFrm::OnBnClickedOk()
{
	char tmp[10];
	m_size.GetWindowTextA(tmp, 10);
	iSize = atoi(tmp);

	OnOK();
}
