
// PongDlg.cpp : implementation file
#include "stdafx.h"
#include "2017-07-07-pong3.h"
#include "PongDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CAboutDlg dialog used for App About
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};
CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()
// PongDlg dialog
PongDlg::PongDlg(CWnd* pParent /*=NULL*/)
	:CDialogEx(IDD_MY20170707PONG3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	leftbat = new Bat(50, 60, 10, 60);
	ball = new Ball(300, 300, 200, 205);
	boarder = new Boarder(10, 550, 10, 390);
	leftbatfirstmove = true;
	boarderfirstmove = true;
	ballfirstmove = true;
	bricksfirstmove = true;
	hit = false;
	startball.x = 250;
	startball.y = 200;
	srand(((unsigned)time(NULL)));
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 9; j++)
		{
			int k = rand();
			if (k % 3 == 0)
				bricks[9 * i + j] = new HardBrick(340 + 50 * i, 380 + 50 * i, 25 + 40 * j, 55 + 40 * j);
			else if (k % 3 ==1)
				bricks[9 * i + j] = new MediumBrick(340 + 50 * i, 380 + 50 * i, 25 + 40 * j, 55 + 40 * j);
			else
				bricks[9 * i + j] = new EasyBrick(340 + 50 * i, 380 + 50 * i, 25 + 40 * j, 55 + 40 * j);
		}
			
}
void PongDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(PongDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
//	ON_WM_KEYUP()
//	ON_WM_KEYDOWN()
//ON_WM_KEYDOWN()
//ON_WM_KEYUP()
ON_BN_CLICKED(IDC_BUTTON1, &PongDlg::OnBnClickedButtonSave)
ON_BN_CLICKED(IDC_BUTTON2, &PongDlg::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON3, &PongDlg::OnBnClickedButtonOpen)
END_MESSAGE_MAP()
// PongDlg message handlers

BOOL PongDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SetTimer(1, 1, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void PongDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void PongDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
int x = (rect.Width() - cxIcon + 1) / 2;
int y = (rect.Height() - cyIcon + 1) / 2;

// Draw the icon
dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR PongDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void PongDlg::SetBallStart()
{
	CClientDC dc(this);
	CPen mypen1(PS_SOLID, 4, RGB(0, 0, 255));
	dc.SelectObject(&mypen1);
	dc.SetROP2(R2_NOTXORPEN);
	ball->draw(&dc);
	ball->xl = startball.x;
	ball->xr = ball->xl + 5;
	ball->yu = startball.y;
	ball->yd = ball->yu + 5;
	ball->vy = 0;
	ball->vx = -1;
	ballfirstmove = true;
}


void PongDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CClientDC dc(this);
	CPen mypen1(PS_SOLID, 3, RGB(255, 0, 0));
	CPen *oldpen;
	oldpen = dc.SelectObject(&mypen1);
	dc.SetROP2(R2_NOTXORPEN);
	if (leftbatfirstmove != true)
		leftbat->draw(&dc);
	leftbat->yu = point.y;
	leftbat->yd = leftbat->yu + 50;
	leftbat->draw(&dc);
	dc.SelectObject(oldpen);
	leftbatfirstmove = false;
	CDialogEx::OnMouseMove(nFlags, point);
}

void PongDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	CPen mypen1(PS_SOLID, 4, RGB(0, 0, 255));
	CPen mypen2(PS_SOLID, 4, RGB(155, 155, 0));
	CPen mypen3(PS_SOLID, 4, RGB(255, 0, 0));
	CPen *oldpen;
	oldpen = dc.SelectObject(&mypen1);
	dc.SetROP2(R2_NOTXORPEN);
	if (boarderfirstmove == true)
	{
		boarder->draw(&dc);
		boarderfirstmove = false;
	}
	if (bricksfirstmove == true || hit == true)
	{
		for (int i = 0; i < 36; i++)
		{
			if (bricks[i]->hits == 0)
			{
				dc.SelectObject(&mypen1);
				bricks[i]->draw(&dc);
				bricks[i]->xr = 0;
				bricks[i]->xl = 0;
				bricks[i]->yu = 0;
				bricks[i]->yd = 0;
			}
			else if (bricks[i]->hits == 1 && bricks[i]->ishit == true)
			{
				if (bricks[i]->id == 3|| bricks[i]->id == 2 )
				{
					dc.SelectObject(&mypen2);
					bricks[i]->draw(&dc);
				}
				dc.SelectObject(&mypen1);
				bricks[i]->draw(&dc);
				bricks[i]->ishit = false;
				
			}
			else if (bricks[i]->hits == 2 && bricks[i]->ishit == true)
			{
				if (bricks[i]->id == 3)
				{
					dc.SelectObject(&mypen3);
					bricks[i]->draw(&dc);
				}
				dc.SelectObject(&mypen2);
				bricks[i]->draw(&dc);
				bricks[i]->ishit = false;
			}
			else if (bricks[i]->hits == 3 && bricks[i]->ishit == true)
			{
				dc.SelectObject(&mypen3);
				bricks[i]->draw(&dc);
				bricks[i]->ishit = false;
				
			}
			
		}
		bricksfirstmove = false;
		hit = false;
	
	}
	dc.SelectObject(&mypen1);
	if (ballfirstmove != true)
		ball->draw(&dc);
	ball->xl = ball->xl + ball->vx;
	ball->xr = ball->xl + 5;
	ball->yu = ball->yu + ball->vy;
	ball->yd = ball->yu + 5;
	ball->draw(&dc);
	
	ballfirstmove = false;

	if (ball->xl == leftbat->xr && (ball->yu >= leftbat->yu && ball->yu <= leftbat->yd))
	{
		ball->vx *= -1;
		if (ball->yu >= leftbat->yu && ball->yu <= leftbat->yu + 10)
			ball->vy = -2;
		else if (ball->yu >= leftbat->yu + 10 && ball->yu <= leftbat->yu + 20)
			ball->vy = -1;
		else if (ball->yu >= leftbat->yu + 20 && ball->yu <= leftbat->yu + 30)
			ball->vy = 0;
		else if (ball->yu >= leftbat->yu + 30 && ball->yu <= leftbat->yu + 40)
			ball->vy = 1;
		else if (ball->yu >= leftbat->yu + 40 && ball->yu <= leftbat->yu + 50)
			ball->vy = 2;
	}

	for (int i = 0; i < 36; i++)
	{
		if ((ball->xr == bricks[i]->xl && (ball->yu >= bricks[i]->yu && ball->yu <= bricks[i]->yd))
			|| (ball->xl == bricks[i]->xr && (ball->yu >= bricks[i]->yu && ball->yu <= bricks[i]->yd)))
		{
			ball->vx *= -1;
			bricks[i]->hit();
			bricks[i]->ishit = true;
			hit = true;
			bricks[i]->dance(&dc);
		}
		else if ((ball->yd == bricks[i]->yu && (ball->xl >= bricks[i]->xl && ball->xl <= bricks[i]->xr))
			|| (ball->yu == bricks[i]->yu && (ball->xl >= bricks[i]->xl && ball->xl <= bricks[i]->xr))
			|| (ball->yd == bricks[i]->yd && (ball->xl >= bricks[i]->xl && ball->xl <= bricks[i]->xr))
			|| (ball->yu == bricks[i]->yd && (ball->xl >= bricks[i]->xl && ball->xl <= bricks[i]->xr)))
				{
					ball->vy *= -1;
					bricks[i]->hit();
					bricks[i]->ishit = true;
					hit = true;
					bricks[i]->dance(&dc);
				}
	}
	if (ball->xr == boarder->xr)
	{
		ball->vx *= -1;
	}
	else if (ball->xl == boarder->xl)
	{
		SetBallStart();
	}
	if (ball->yu == boarder->yu || ball->yu == boarder->yd)
		ball->vy *= -1;
	dc.SelectObject(oldpen);
	CDialogEx::OnTimer(nIDEvent);
}

//void PongDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: Add your message handler code here and/or call default
//	
//	CClientDC dc(this);
//	CPen mypen1(PS_SOLID, 3, RGB(255, 0, 0));
//	CPen *oldpen;
//	oldpen = dc.SelectObject(&mypen1);
//	dc.SetROP2(R2_NOTXORPEN);
//	if (rightbatfirstmove != true)
//		rightbat->draw(&dc);
//	rightbat->yu = rightbat->yu - 1;
//	rightbat->yd = leftbat->yu + 50;
//	rightbat->draw(&dc);
//	dc.SelectObject(oldpen);
//	rightbatfirstmove = false;
//
//	CDialogEx::OnKeyUp(nChar, nRepCnt, nFlags);
//}


//void PongDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: Add your message handler code here and/or call default
//	CClientDC dc(this);
//	CPen mypen1(PS_SOLID, 3, RGB(255, 0, 0));
//	CPen *oldpen;
//	oldpen = dc.SelectObject(&mypen1);
//	dc.SetROP2(R2_NOTXORPEN);
//	if (rightbatfirstmove != true)
//		rightbat->draw(&dc);
//	rightbat->yu = rightbat->yu +1;
//	rightbat->yd = leftbat->yu + 50;
//	rightbat->draw(&dc);
//	dc.SelectObject(oldpen);
//	rightbatfirstmove = false;
//
//	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
//}

//void PongDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: Add your message handler code here and/or call default
//	int movement;
//	ispressed = true;
//	switch (nChar)
//	{
//	case VK_UP:
//		movement = -1;
//		break;
//	case VK_DOWN:
//		movement = 1;
//		break;
//	}
//	CClientDC dc(this);
//	CPen mypen1(PS_SOLID, 3, RGB(255, 0, 0));
//	CPen *oldpen;
//	oldpen = dc.SelectObject(&mypen1);
//	dc.SetROP2(R2_NOTXORPEN);
//	if (rightbatfirstmove != true)
//		rightbat->draw(&dc);
//	rightbat->yu = rightbat->yu +movement;
//	rightbat->yd = leftbat->yu + 50;
//	rightbat->draw(&dc);
//	dc.SelectObject(oldpen);
//	rightbatfirstmove = false;
//
//	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
//}
//void PongDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: Add your message handler code here and/or call default
//	ispressed = false;
//	CDialogEx::OnKeyUp(nChar, nRepCnt, nFlags);
//}
void PongDlg::OnBnClickedButtonSave()
{
	CFile file;
	file.Open(L"SaveGame.sav", CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store);
	PongDlg::Serialize(ar);
	ar.Close();
	file.Close();
}
void PongDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
}
void PongDlg::OnBnClickedButtonOpen()
{
	// TODO: Add your control notification handler code here

	CFile file;
	file.Open(L"SaveGame.sav", CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	PongDlg::Serialize(ar);
	ar.Close();
	file.Close();
}
void PongDlg::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	
		int i;
		for (i = 0; i < 36; i++)
		{
			ar << bricks[i]->id << bricks[i]->xl << bricks[i]->xr << bricks[i]->yu << bricks[i]->yd << bricks[i]->hits;
		}

	}
	else
	{	// loading code
		int i;
		for (i = 0; i < 36; i++)
		{
			int id;
			int xl;
			int xr;
			int yu;
			int yd;
			int hp;
			ar >> id;
			ar >> xl;
			ar >> xr;
			ar >> yu;
			ar >> yd;
			ar >> hp;
			CClientDC dc(this);
			CPen mypen1(PS_SOLID, 4, RGB(0, 0, 255));
			CPen mypen2(PS_SOLID, 4, RGB(155, 155, 0));
			CPen mypen3(PS_SOLID, 4, RGB(255, 0, 0));
			dc.SetROP2(R2_NOTXORPEN);
			if (bricks[i]->hits == 3)
			{
				dc.SelectObject(&mypen3);
				bricks[i]->draw(&dc);
			}
			else if (bricks[i]->hits == 2)
			{
				dc.SelectObject(&mypen2);
				bricks[i]->draw(&dc);
			}
			else if (bricks[i]->hits == 1)
			{
				dc.SelectObject(&mypen1);
				bricks[i]->draw(&dc);
			}

			delete bricks[i];

			if (id == 3)
			{
				bricks[i] = new HardBrick(xl, xr, yu, yd);
				bricks[i]->hits = hp;
				bricks[i]->ishit = false;
			}
				
			else if (id == 2)
			{
				bricks[i] = new MediumBrick(xl, xr, yu, yd);
				bricks[i]->hits = hp;
				bricks[i]->ishit = false;
			}
				
			else
			{
				bricks[i] = new EasyBrick(xl, xr, yu, yd);
				bricks[i]->hits = hp;
				bricks[i]->ishit = false;
			}
			
			if (bricks[i]->hits == 3)
			{
				dc.SelectObject(&mypen3);
				bricks[i]->draw(&dc);
			}
			else if (bricks[i]->hits == 2)
			{
				dc.SelectObject(&mypen2);
				bricks[i]->draw(&dc);
			}
			else if (bricks[i]->hits == 1)
			{
				dc.SelectObject(&mypen1);
				bricks[i]->draw(&dc);
			}
		}
		ballfirstmove = false;
		SetBallStart();
	}
}
