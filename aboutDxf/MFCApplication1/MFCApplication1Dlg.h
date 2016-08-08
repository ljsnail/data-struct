
// MFCApplication1Dlg.h : header file
//

#pragma once
#include "afxwin.h"

// CMFCApplication1Dlg dialog
class CMFCApplication1Dlg : public CDialogEx
{
// Construction
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	void CMFCApplication1Dlg::switchkeyword(CString strR);

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
	enum{ LINE, CIRCLE, ARC, SPLINE, LWPOLYLINE, ELLIPSE };
	CString path, code, dxfFile, str, keyword;
	afx_msg void OnBnClickedButtonOpenFile();
	CListBox mListDXF;

	afx_msg void OnBnCSavaData();
	
	CEdit m_showdata;
	/////////////////////////////
public:
	int a = 3;
	int b = 4;
	int c = a + b;
	char string[25]; 
	//int


	afx_msg void OnBnClickedSave();
public://½«ÄÚÈÝÐ´½øtxt
	CString m_dataa;

	CString m_data;
	afx_msg void OnBnClickedOpen2();
	CString m_disfile;
	CString m_code;
	afx_msg void OnSaveorigindata();
};
