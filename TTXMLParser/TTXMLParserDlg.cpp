// TTXMLParserDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "TTXMLParser.h"
#include "TTXMLParserDlg.h"
#include "SizeFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

TTXMLParseEngine tpe;

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTTXMLParserDlg 대화 상자




CTTXMLParserDlg::CTTXMLParserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTTXMLParserDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTTXMLParserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lPost);
	DDX_Control(pDX, IDC_LIST2, m_lCate);
	DDX_Control(pDX, IDC_CHECK4, c_migrational);
	DDX_Control(pDX, IDC_CHECK3, c_notice);
	DDX_Control(pDX, IDC_CHECK1, c_guestbook);
	DDX_Control(pDX, IDC_BUTTON1, b1);
	DDX_Control(pDX, IDC_BUTTON3, b2);
	DDX_Control(pDX, IDC_BUTTON4, b3);
	DDX_Control(pDX, IDC_BUTTON5, b4);
	DDX_Control(pDX, IDC_BUTTON2, b5);
}

BEGIN_MESSAGE_MAP(CTTXMLParserDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CTTXMLParserDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CTTXMLParserDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CTTXMLParserDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CTTXMLParserDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CTTXMLParserDlg 메시지 처리기

BOOL CTTXMLParserDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	c_migrational.SetCheck(TRUE);
	c_notice.SetCheck(TRUE);
	c_guestbook.SetCheck(TRUE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTTXMLParserDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTTXMLParserDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTTXMLParserDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTTXMLParserDlg::analyzeFile(CString str)
{
	if (!tpe.analyzeFile( str.GetBuffer() ))
	{
		AfxMessageBox("파일 읽기에 실패하였습니다.");
		return;
	}

	// clear
	for (int i=0; i<m_lPost.GetCount(); i++)
		m_lPost.DeleteString(0);
	for (int i=0; i<m_lCate.GetCount(); i++)
		m_lCate.DeleteString(0);

	for (int i=0; i<tpe.postCnt; i++)
		m_lPost.AddString( tpe.postData[i].title );
	for (int i=0; i<tpe.catecnt; i++)
		m_lCate.AddString( tpe.categories[i] );

	if (strcmp(tpe.migrational, "true") == 0)
		c_migrational.SetCheck(TRUE);
	else
		c_migrational.SetCheck(FALSE);

	b2.EnableWindow();
	b3.EnableWindow();
	b4.EnableWindow();
}

void CTTXMLParserDlg::OnBnClickedButton1()
{
	CFileDialog fd(TRUE, 0, 0, 4|2, "xml Files|*.xml|All Files|*.*");
	if (fd.DoModal() == IDOK) {
		filepath = fd.GetPathName();
		if (MessageBox("파일을 지금 분석하시겠습니까?\n파일 용량에 따라 수 분이 걸릴 수 있습니다.", "?", MB_YESNO) == IDYES) {
			analyzeFile(filepath);
		}

		// button2 Enabled
	}
}

void CTTXMLParserDlg::OnBnClickedButton4()
{
	tpe.emptyQueue();
	char cate[100];
	int nCount = m_lCate.GetSelCount();

	CArray<int,int> aryListBoxSel;
	aryListBoxSel.SetSize(nCount);
	m_lCate.GetSelItems(nCount, aryListBoxSel.GetData());

	for (int i=0; i<nCount; i++)
	{
		int sel = aryListBoxSel[i];
		m_lCate.GetText(sel, cate);
		tpe.addQueueFromCategory( cate );
	}

	int size = tpe.calcPostSize() / 1024 / 1024;
	CString msg;
	msg.Format("%dMB이상의 용량이 요구됩니다. 계속하시겠습니까?", size);
	if (MessageBox(msg, "?", MB_YESNO) == IDYES)
	{
		CFileDialog fd(FALSE, 0, 0, 4|2, "xml Files|*.xml|All Files|*.*");
		if (fd.DoModal() == IDOK)
		{
			if (c_migrational.GetCheck()) strcpy(tpe.migrational, "true"); else strcpy(tpe.migrational, "false");
			tpe.out_Notice = c_notice.GetCheck();
			tpe.out_Guestbook = c_guestbook.GetCheck();
			tpe.outputTTXMLFile( fd.GetPathName().GetBuffer() );
			AfxMessageBox("성공적으로 저장되었습니다.");
		}
	}
}

void CTTXMLParserDlg::OnBnClickedButton3()
{
	CSizeFrm sfrm;
	if (sfrm.DoModal() == IDOK)
	{
		CFileDialog fd(FALSE, 0, 0, 4|2, "xml Files|*.xml|All Files|*.*");
		if (fd.DoModal() == IDOK)
		{
			char oName[512], nName[512];
			strcpy(oName, fd.GetPathName().GetBuffer() );

			int size = sfrm.iSize * 1024 * 1024;
			
			tpe.emptyQueue();
			for (int i=0; i<tpe.postCnt; i++)
			{
				tpe.addQueue(i);
				if (tpe.calcPostSize() > size || i >= tpe.postCnt-1)
				{
					sprintf(nName, "%s_%d.xml", oName, i+1);

					if (c_migrational.GetCheck()) strcpy(tpe.migrational, "true"); else strcpy(tpe.migrational, "false");
					tpe.out_Notice = c_notice.GetCheck();
					tpe.out_Guestbook = c_guestbook.GetCheck();
					tpe.outputTTXMLFile( nName );
					tpe.emptyQueue();
				}
			}

			AfxMessageBox("성공적으로 저장되었습니다.");
		}
	}
}

void CTTXMLParserDlg::OnBnClickedButton5()
{
	tpe.emptyQueue();
	
	int nCount = m_lPost.GetSelCount();
	CArray<int,int> aryListBoxSel;
	aryListBoxSel.SetSize(nCount);
	m_lPost.GetSelItems(nCount, aryListBoxSel.GetData());
	for (int i=0; i<nCount; i++)
	{
		tpe.addQueue( aryListBoxSel[i] );
	}
	
	int size = tpe.calcPostSize() / 1024 / 1024;
	CString msg;
	msg.Format("%dMB이상의 용량이 요구됩니다. 계속하시겠습니까?", size);
	if (MessageBox(msg, "?", MB_YESNO) == IDYES)
	{
		CFileDialog fd(FALSE, 0, 0, 4|2, "xml Files|*.xml|All Files|*.*");
		if (fd.DoModal() == IDOK)
		{
			if (c_migrational.GetCheck()) strcpy(tpe.migrational, "true"); else strcpy(tpe.migrational, "false");
			tpe.out_Notice = c_notice.GetCheck();
			tpe.out_Guestbook = c_guestbook.GetCheck();
			tpe.outputTTXMLFile( fd.GetPathName().GetBuffer() );
			AfxMessageBox("성공적으로 저장되었습니다.");
		}
	}
}
