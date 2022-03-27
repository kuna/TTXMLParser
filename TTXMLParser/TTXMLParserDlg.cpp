// TTXMLParserDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "TTXMLParser.h"
#include "TTXMLParserDlg.h"
#include "SizeFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

TTXMLParseEngine tpe;

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CTTXMLParserDlg ��ȭ ����




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


// CTTXMLParserDlg �޽��� ó����

BOOL CTTXMLParserDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	c_migrational.SetCheck(TRUE);
	c_notice.SetCheck(TRUE);
	c_guestbook.SetCheck(TRUE);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CTTXMLParserDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CTTXMLParserDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTTXMLParserDlg::analyzeFile(CString str)
{
	if (!tpe.analyzeFile( str.GetBuffer() ))
	{
		AfxMessageBox("���� �б⿡ �����Ͽ����ϴ�.");
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
		if (MessageBox("������ ���� �м��Ͻðڽ��ϱ�?\n���� �뷮�� ���� �� ���� �ɸ� �� �ֽ��ϴ�.", "?", MB_YESNO) == IDYES) {
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
	msg.Format("%dMB�̻��� �뷮�� �䱸�˴ϴ�. ����Ͻðڽ��ϱ�?", size);
	if (MessageBox(msg, "?", MB_YESNO) == IDYES)
	{
		CFileDialog fd(FALSE, 0, 0, 4|2, "xml Files|*.xml|All Files|*.*");
		if (fd.DoModal() == IDOK)
		{
			if (c_migrational.GetCheck()) strcpy(tpe.migrational, "true"); else strcpy(tpe.migrational, "false");
			tpe.out_Notice = c_notice.GetCheck();
			tpe.out_Guestbook = c_guestbook.GetCheck();
			tpe.outputTTXMLFile( fd.GetPathName().GetBuffer() );
			AfxMessageBox("���������� ����Ǿ����ϴ�.");
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

			AfxMessageBox("���������� ����Ǿ����ϴ�.");
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
	msg.Format("%dMB�̻��� �뷮�� �䱸�˴ϴ�. ����Ͻðڽ��ϱ�?", size);
	if (MessageBox(msg, "?", MB_YESNO) == IDYES)
	{
		CFileDialog fd(FALSE, 0, 0, 4|2, "xml Files|*.xml|All Files|*.*");
		if (fd.DoModal() == IDOK)
		{
			if (c_migrational.GetCheck()) strcpy(tpe.migrational, "true"); else strcpy(tpe.migrational, "false");
			tpe.out_Notice = c_notice.GetCheck();
			tpe.out_Guestbook = c_guestbook.GetCheck();
			tpe.outputTTXMLFile( fd.GetPathName().GetBuffer() );
			AfxMessageBox("���������� ����Ǿ����ϴ�.");
		}
	}
}
