
// MFC_GNSS_PositonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFC_GNSS_Positon.h"
#include "MFC_GNSS_PositonDlg.h"
#include "afxdialogex.h"

#include "Serial.h"
#include "PosAverager.h"
#include <string>
#include <iostream>

using namespace std;

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


// CMFC_GNSS_PositonDlg dialog



CMFC_GNSS_PositonDlg::CMFC_GNSS_PositonDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_GNSS_POSITON_DIALOG, pParent)
	, m_edit(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_GNSS_PositonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT1, m_edit);
	DDV_MaxChars(pDX, m_edit, 128);
	DDX_Text(pDX, IDC_EDIT2, m_edit);
	DDX_Text(pDX, IDC_EDIT2, m_edit);
}

BEGIN_MESSAGE_MAP(CMFC_GNSS_PositonDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC_GNSS_PositonDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFC_GNSS_PositonDlg::OnBnClickedButton2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CMFC_GNSS_PositonDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMFC_GNSS_PositonDlg message handlers

BOOL CMFC_GNSS_PositonDlg::OnInitDialog()
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

	SetTimer(1, 1000, 0);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFC_GNSS_PositonDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFC_GNSS_PositonDlg::OnPaint()
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
HCURSOR CMFC_GNSS_PositonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFC_GNSS_PositonDlg::OnBnClickedOk()
{
	serial.Close_Port();
	CDialogEx::OnOK();
}

void CMFC_GNSS_PositonDlg::OnBnClickedButton1()//open button
{
	serial.Open_Port(5);
}

void CMFC_GNSS_PositonDlg::OnBnClickedButton2()// close button
{
	serial.Close_Port();
}
static PosAverager averager(5);
static char buf[128];
static CString sInfo;

void CMFC_GNSS_PositonDlg::OnTimer(UINT_PTR nIDEvent)
{
	int ret = 0;
	int bytesRead = 0;

	memset(buf, 0, sizeof(buf));
	/*
	BOOL PurgeComm(
		HANDLE hFile,
		DWORD  dwFlags
	);
	*/
	ret = serial.ReadDataWaiting();
	if (ret > 0)
	{
		//sizeof(buf)-1: Damit sind die chars im Puffer buf immer ein Null-terminierter String!
		if (ret > sizeof(buf)-1)
		{
			ret = sizeof(buf)-1;
		}
		bytesRead = serial.Read(buf, ret);

		CString s1;
		s1 = "";

		if (bytesRead > 0)
		{
			//OutputDebugStringA("data received\n");
		}

		s1 = CA2W(buf, CP_UTF8);

		sInfo.Append(s1);

		int stringlen = sInfo.GetLength();
		if (stringlen >= 512) {
			sInfo.Delete(0, stringlen - 512);
		}

		m_edit = sInfo;
		UpdateData(FALSE);                       // Variablen --> Felder

		this->newBytesFromUart(buf, bytesRead);//in dieser Funktion den NMEA parser aufrufen
	}

	CDialogEx::OnTimer(nIDEvent);
}
// TODO: verbessern
void CMFC_GNSS_PositonDlg::newBytesFromUart(char * buf, int buflen)
{
	CString rmcString;
	rmcString = "";

	rmcString = CA2W(buf, CP_UTF8);

#pragma region extractRMC

	CString rmc;
	rmc = "RMC";

	int rmc_position = -1;
	int d1 = -1;
	int d2 = -1;

	rmc_position = rmcString.Find(rmc, 0);


	if (rmc_position != -1)
	{
		for (int i = rmc_position; i >= 0; i--)
		{
			if (rmcString[i] == '$')
			{
				d1 = i;
				d2 = rmcString.Find('$', rmc_position);

				break;
			}
		}
		if (d1 != -1 && d2 != -1 && d1 + 68 == d2)
		{
			rmcString = rmcString.Mid(d1, d2 - d1);

			//OutputDebugStringW(rmcString);
		}
	}
	else return;
#pragma endregion

	//CheckForValidness
	if (rmcString[17] == 'A')
	{
		gnss_position pos;

		// bef�llung der gnss_pos struktur
		pos.horizontalCD = rmcString[30];
		
		double degree = _ttof(rmcString.Mid(19, 2));
		double minutes = _ttof(rmcString.Mid(21, 8));

		pos.horizontalDM = degree + minutes / 60;

		pos.verticalCD = rmcString[44];
		
		degree = _ttof(rmcString.Mid(32, 3));
		minutes = _ttof(rmcString.Mid(35, 8));

		pos.verticalDM = degree + minutes / 60;

		pos = averager.insertPosition(pos);		// �bergabe der gnss_pos struktur an den averager


												// Ausgabe des Schwerpunkts
		CString out;
		out = "";
		CString s;
		s.Format(_T("%f"), pos.horizontalDM);
		out += s;
		out += ", ";
		s.Format(_T("%f"), pos.verticalDM);
		out += s;
		out += "\n";

		OutputDebugStringW(out);
		
	}
	return;
}