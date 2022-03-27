// TTXMLParserDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "TTXMLParseEngine.h"

// CTTXMLParserDlg ��ȭ ����
class CTTXMLParserDlg : public CDialog
{
// �����Դϴ�.
public:
	CTTXMLParserDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TTXMLPARSER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

public:
	CString filepath;

public:
	// for Stack Overflow
	void analyzeFile(CString str);

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_lPost;
public:
	CListBox m_lCate;
public:
	afx_msg void OnBnClickedButton1();
public:
	afx_msg void OnBnClickedButton4();
public:
	afx_msg void OnBnClickedButton3();
public:
	afx_msg void OnBnClickedButton5();
public:
	CButton c_migrational;
public:
	CButton c_notice;
public:
	CButton c_guestbook;
public:
	CButton b1;
public:
	CButton b2;
public:
	CButton b3;
public:
	CButton b4;
public:
	CButton b5;
};
