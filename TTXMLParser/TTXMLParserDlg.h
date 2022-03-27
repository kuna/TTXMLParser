// TTXMLParserDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "TTXMLParseEngine.h"

// CTTXMLParserDlg 대화 상자
class CTTXMLParserDlg : public CDialog
{
// 생성입니다.
public:
	CTTXMLParserDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TTXMLPARSER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

public:
	CString filepath;

public:
	// for Stack Overflow
	void analyzeFile(CString str);

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
