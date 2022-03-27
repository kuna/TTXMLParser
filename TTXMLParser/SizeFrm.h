#pragma once
#include "afxwin.h"


// CSizeFrm dialog

class CSizeFrm : public CDialog
{
	DECLARE_DYNAMIC(CSizeFrm)

public:
	int iSize;

	CSizeFrm(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSizeFrm();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_size;
public:
	afx_msg void OnBnClickedOk();
};
