
// MFC_GNSS_PositonDlg.h : header file
//

#pragma once

#include "Serial.h"
#include "afxwin.h"

// CMFC_GNSS_PositonDlg dialog
class CMFC_GNSS_PositonDlg : public CDialogEx
{
// Construction
public:
	CMFC_GNSS_PositonDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_GNSS_POSITON_DIALOG };
#endif

	CSerial serial;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
//	CEdit uart_output;
//	CString m_edit;
	CString m_edit;
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedOk();
};
