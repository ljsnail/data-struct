
// MFCApplication1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include <string.h>
#include <vector>
#include "io.h" 
#include "fcntl.h"   
using namespace std;

struct dxfData
{
	
	double LINE[6];
	double CIRCLE[4];
	double ARC[6];
	double LWPOLYLINE[1000];
	double ELLIPSE[];
};
vector<dxfData> vdxfData;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg dialog



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
	, m_data(_T(""))
	, m_disfile(_T(""))
	, m_code(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DXF, mListDXF);

	DDX_Control(pDX, IDC_EDIT1_data, m_showdata);
	DDX_Text(pDX, IDC_Data_edit, m_disfile);
//	DDX_Text(pDX, IDC_Data_edit, m_code);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_FILE, &CMFCApplication1Dlg::OnBnClickedButtonOpenFile)
	ON_BN_CLICKED(IDC_BUTTON_SAVA_DATA, &CMFCApplication1Dlg::OnBnCSavaData)
	ON_BN_CLICKED(IDC_SAVE, &CMFCApplication1Dlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_OPEN2, &CMFCApplication1Dlg::OnBnClickedOpen2)
	ON_BN_CLICKED(IDC_SAVEoriginDATA, &CMFCApplication1Dlg::OnSaveorigindata)
END_MESSAGE_MAP()


// CMFCApplication1Dlg message handlers

BOOL CMFCApplication1Dlg::OnInitDialog()
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
	//m_showdata.SetWindowText(_T("welcome to edit"));
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication1Dlg::OnPaint()
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
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedButtonOpenFile()
{
	// TODO: Add your control notification handler code here
	
	
	OPENFILENAME ofn = { 0 };
	
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST;
	CFileDialog hFileDlg(TRUE, NULL, NULL, ofn.Flags, TEXT("DXF(*.*)|*.*|"), NULL);
	if (hFileDlg.DoModal() == IDOK)
	{
		path = hFileDlg.GetPathName();
		switchkeyword(path);
		/*CStdioFile myFile(path, CFile::modeRead);
		keyword = myFile.ReadString(code);
		mListDXF.ResetContent();*/
		//while (myFile.ReadString(code))
		//{
		//	while ((strcmp(code, "LINE") == 0) || (strcmp(code, "CIRCLE") == 0) || (strcmp(code, "ARC") == 0) || (strcmp(code, "SPLINE") == 0))
		//	{
		//		if ((strcmp(code, "LINE") == 0)) element = 0;
		//		if ((strcmp(code, "CIRCLE") == 0)) element = 1;
		//		if ((strcmp(code, "ARC") == 0)) element = 2;
		//		if ((strcmp(code, "SPLINE") == 0)) element = 3;

		//		switch (element)
		//		{
		//		case LINE:
		//			myFile.ReadString(code);
		//			while ((strcmp(code, "LINE") != 0) && (strcmp(code, "CIRCLE") != 0) && (strcmp(code, "ARC") != 0) && (strcmp(code, "SPLINE") != 0) && (strcmp(code, "ENDSEC") != 0))
		//			{
		//				myFile.ReadString(code);
		//				symbol = atoi(code);
		//				switch (symbol)
		//				{
		//				case 10:
		//					myFile.ReadString(code);
		//					tempDXF.LINE[0] = atof(code);
		//					break;
		//				case 20:
		//					myFile.ReadString(code);
		//					tempDXF.LINE[1] = atof(code);
		//					break;
		//				case 30:
		//					myFile.ReadString(code);
		//					tempDXF.LINE[2] = atof(code);
		//					break;
		//				case 11:
		//					myFile.ReadString(code);
		//					tempDXF.LINE[3] = atof(code);
		//					break;
		//				case 21:
		//					myFile.ReadString(code);
		//					tempDXF.LINE[4] = atof(code);
		//					break;
		//				case 31:
		//					myFile.ReadString(code);
		//					tempDXF.LINE[5] = atof(code);

		//					str.Format("LINE:From: %.4lf, %.4lf, %.4lf To: %.4lf, %.4lf, %.4lf", tempDXF.LINE[0], tempDXF.LINE[1], tempDXF.LINE[2], tempDXF.LINE[3], tempDXF.LINE[4], tempDXF.LINE[5]);
		//					mListDXF.InsertString(-1, str);
		//					vdxfData.push_back(tempDXF);
		//				default: break;
		//				}

		//			}
		//			break;
		//		case CIRCLE:
		//			myFile.ReadString(code);
		//			while ((strcmp(code, "LINE") != 0) && (strcmp(code, "CIRCLE") != 0) && (strcmp(code, "ARC") != 0) && (strcmp(code, "SPLINE") != 0) && (strcmp(code, "ENDSEC") != 0))
		//			{
		//				myFile.ReadString(code);
		//				symbol = atoi(code);
		//				switch (symbol)
		//				{
		//				case 10:
		//					myFile.ReadString(code);
		//					tempDXF.CIRCLE[0] = atof(code);
		//					break;
		//				case 20:
		//					myFile.ReadString(code);
		//					tempDXF.CIRCLE[1] = atof(code);
		//					break;
		//				case 30:
		//					myFile.ReadString(code);
		//					tempDXF.CIRCLE[2] = atof(code);
		//					break;
		//				case 40:
		//					myFile.ReadString(code);
		//					tempDXF.CIRCLE[3] = atof(code);
		//					break;

		//					
		//				default: break;
		//				}
		//				
		//			}
		//			str.Format("CIRCLE: %.4lf, %.4lf, %.4lf , %.4lf", tempDXF.CIRCLE[0], tempDXF.CIRCLE[1], tempDXF.CIRCLE[2], tempDXF.CIRCLE[3]);
		//			mListDXF.InsertString(-1, str);
		//			//vdxfData.push_back(tempDXF);
		//			break;
		//			
		//		case ARC:
		//			myFile.ReadString(code);
		//			while ((strcmp(code, "LINE") != 0) && (strcmp(code, "CIRCLE") != 0) && (strcmp(code, "ARC") != 0) && (strcmp(code, "SPLINE") != 0) && (strcmp(code, "ENDSEC") != 0))
		//			{
		//				myFile.ReadString(code);
		//				symbol = atoi(code);
		//				switch (symbol)
		//				{
		//				case 10:
		//					myFile.ReadString(code);
		//					tempDXF.ARC[0] = atof(code);
		//					break;
		//				case 20:
		//					myFile.ReadString(code);
		//					tempDXF.ARC[1] = atof(code);
		//					break;
		//				case 30:
		//					myFile.ReadString(code);
		//					tempDXF.ARC[2] = atof(code);
		//					break;
		//				case 40:
		//					myFile.ReadString(code);
		//					tempDXF.ARC[3] = atof(code);
		//					break;
		//				case 50:
		//					myFile.ReadString(code);
		//					tempDXF.ARC[4] = atof(code);
		//					break;
		//				case 51:
		//					myFile.ReadString(code);
		//					tempDXF.ARC[5] = atof(code);

		//					str.Format("ACR: %.4lf, %.4lf, %.4lf, %.4lf, %.4lf, %.4lf", tempDXF.ARC[0], tempDXF.ARC[1], tempDXF.ARC[2], tempDXF.ARC[3], tempDXF.ARC[4], tempDXF.ARC[5]);
		//					mListDXF.InsertString(-1, str);
		//					vdxfData.push_back(tempDXF);
		//				default: break;
		//				}

		//			}
		//			break;
		//		default:
		//			break;
		//		}
		//		
		//	}
		//} //End file	
	}
	
}

void CMFCApplication1Dlg::switchkeyword(CString  str)
{
	int b = 4;
	int c = a + b;
	dxfData tempDXF;
	int element = -1;
	int symbol = 0;
	CStdioFile myFile(path, CFile::modeRead);
	 myFile.ReadString(code);
	mListDXF.ResetContent();
	while (myFile.ReadString(code))
	{
		while ((strcmp(code, "LINE") == 0) || (strcmp(code, "CIRCLE") == 0) || (strcmp(code, "ARC") == 0) || (strcmp(code, "SPLINE") == 0) || (strcmp(code, "LWPOLYLINE") == 0))
		{
			if ((strcmp(code, "LINE") == 0)) element = 0;
			if ((strcmp(code, "CIRCLE") == 0)) element = 1;
			if ((strcmp(code, "ARC") == 0)) element = 2;
			if ((strcmp(code, "SPLINE") == 0)) element = 3;
			if ((strcmp(code, "LWPOLYLINE") == 0)) element = 4;

			switch (element)
			{
			case LINE:
				myFile.ReadString(code);//这行代码和下面一行的作用是如果是LINE则让它能进入循环，且没有循环完LINE则不能出来。没有这行则根本下面都进不去，关键是不会存在2个LINE一起存在。
				while ((strcmp(code, "LINE") != 0) && (strcmp(code, "CIRCLE") != 0) && (strcmp(code, "ARC") != 0) && (strcmp(code, "SPLINE") != 0) && (strcmp(code, "LWPOLYLINE") != 0) && (strcmp(code, "ENDSEC") != 0))
				{
					myFile.ReadString(code);
					symbol = atoi(code);
					switch (symbol)
					{
					case 10:
						myFile.ReadString(code);
						tempDXF.LINE[0] = atof(code);
						break;
					case 20:
						myFile.ReadString(code);
						tempDXF.LINE[1] = atof(code);
						break;
					case 30:
						myFile.ReadString(code);
						tempDXF.LINE[2] = atof(code);
						break;
					case 11:
						myFile.ReadString(code);
						tempDXF.LINE[3] = atof(code);
						break;
					case 21:
						myFile.ReadString(code);
						tempDXF.LINE[4] = atof(code);
						break;
					case 31:
						myFile.ReadString(code);
						tempDXF.LINE[5] = atof(code);

						str.Format("LINE:From: %.4lf, %.4lf, %.4lf To: %.4lf, %.4lf, %.4lf", tempDXF.LINE[0], tempDXF.LINE[1], tempDXF.LINE[2], tempDXF.LINE[3], tempDXF.LINE[4], tempDXF.LINE[5]);
						mListDXF.InsertString(-1, str);
					//CString stra =(CString)( tempDXF.LINE[0] + tempDXF[1]);
						//CString pluscode[6], addcode;
						/*for (int i = 0; i < 6; i++)
						{
							addcode + = tempDXF.LINE[i];
						}*/
				
						/*e = itoa( c, string,10);*/
						m_showdata.SetWindowTextA(str);//在这里给个循环，让之前所有累加起来。
						vdxfData.push_back(tempDXF);

					default: break;
					}

				}
				break;
			case CIRCLE:
				myFile.ReadString(code);
				while ((strcmp(code, "LINE") != 0) && (strcmp(code, "CIRCLE") != 0) && (strcmp(code, "ARC") != 0) && (strcmp(code, "SPLINE") != 0) && (strcmp(code, "LWPOLYLINE") != 0) && (strcmp(code, "ENDSEC") != 0))
				{
					myFile.ReadString(code);
					symbol = atoi(code);
					switch (symbol)
					{
					case 10:
						myFile.ReadString(code);
						tempDXF.CIRCLE[0] = atof(code);
						break;
					case 20:
						myFile.ReadString(code);
						tempDXF.CIRCLE[1] = atof(code);
						break;
					case 30:
						myFile.ReadString(code);
						tempDXF.CIRCLE[2] = atof(code);
						break;
					case 40:
						myFile.ReadString(code);
						tempDXF.CIRCLE[3] = atof(code);
						break;


					default: break;
					}

				}
				str.Format("CIRCLE: %.4lf, %.4lf, %.4lf , %.4lf", tempDXF.CIRCLE[0], tempDXF.CIRCLE[1], tempDXF.CIRCLE[2], tempDXF.CIRCLE[3]);
				mListDXF.InsertString(-1, str);
				//vdxfData.push_back(tempDXF);
				break;

			case ARC:
				myFile.ReadString(code);
				while ((strcmp(code, "LINE") != 0) && (strcmp(code, "CIRCLE") != 0) && (strcmp(code, "ARC") != 0) && (strcmp(code, "SPLINE") != 0) && (strcmp(code, "LWPOLYLINE") != 0) && (strcmp(code, "ENDSEC") != 0))
				{
					myFile.ReadString(code);
					symbol = atoi(code);
					switch (symbol)
					{
					case 10:
						myFile.ReadString(code);
						tempDXF.ARC[0] = atof(code);
						break;
					case 20:
						myFile.ReadString(code);
						tempDXF.ARC[1] = atof(code);
						break;
					case 30:
						myFile.ReadString(code);
						tempDXF.ARC[2] = atof(code);
						break;
					case 40:
						myFile.ReadString(code);
						tempDXF.ARC[3] = atof(code);
						break;
					case 50:
						myFile.ReadString(code);
						tempDXF.ARC[4] = atof(code);
						break;
					case 51:
						myFile.ReadString(code);
						tempDXF.ARC[5] = atof(code);

						str.Format("ACR: %.4lf, %.4lf, %.4lf, %.4lf, %.4lf, %.4lf", tempDXF.ARC[0], tempDXF.ARC[1], tempDXF.ARC[2], tempDXF.ARC[3], tempDXF.ARC[4], tempDXF.ARC[5]);
						mListDXF.InsertString(-1, str);
						vdxfData.push_back(tempDXF);
					default: break;
					}

				}
				break;
			case LWPOLYLINE:
				myFile.ReadString(code);
				while ((strcmp(code, "LINE") != 0) && (strcmp(code, "CIRCLE") != 0) && (strcmp(code, "ARC") != 0) && (strcmp(code, "SPLINE") != 0) && (strcmp(code, "LWPOLYLINE") != 0) && (strcmp(code, "ENDSEC") != 0))
				{
					int i = 0;
					int j = 0;
					myFile.ReadString(code);
					symbol = atoi(code);
					switch (symbol)
					{
						
					case 10:
						/*myFile.ReadString(code);
						while ((strcmp(code, "10") != 0&&)*/
						myFile.ReadString(code);
						
						tempDXF.LWPOLYLINE[2*i] = atof(code);
						break;
					case 20:
						
						myFile.ReadString(code);
						tempDXF.LWPOLYLINE[2 * j + 1] = atof(code);
						str.Format("LWPOLYLINE: %.4lf, %.4lf", tempDXF.LWPOLYLINE[2*i], tempDXF.LWPOLYLINE[2*j+1]);
						mListDXF.InsertString(-1, str);
						vdxfData.push_back(tempDXF);
					/*	CFile file;
						file.Open("D:\\1.txt ", CFile::modeWrite | CFile::modeCreate);
						file.Write();*/
					default: break;
					}
					

				}
				break;
			default:
				break;
			}

		}
	} //End file	
}

void CMFCApplication1Dlg::OnBnCSavaData()
{
	// TODO:  在此添加控件通知处理程序代码
	
	CString strText(_T(""));
	GetDlgItemText(IDC_EDIT1_data, strText); //获取edit box中的数据 

	try
	{
		CStdioFile file;
		file.Open(_T("D:\\abc.txt"), CFile::modeCreate | CFile::modeWrite |
			CFile::typeText);
		//打开D盘的txt文件 
		file.WriteString(strText);  //写入edit box中的数据 
		file.Close();
	}
	catch (CFileException* e)
	{
		e->ReportError();
		e->Delete();

	}
}

void CMFCApplication1Dlg::OnBnClickedSave()
{
	// TODO:  在此添加控件通知处理程序代码
	// TODO: Add your control notification handler code here
	CFileDialog* pDlg = new CFileDialog(FALSE, _T("txt"), _T("filename"), OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY,
		_T("文本文件(*.txt)|*.txt||"), this);
	pDlg->m_ofn.lpstrTitle = _T("保存文本文件");

	ASSERT(pDlg);
	if (pDlg->DoModal() == IDOK)
	{
		UpdateData(TRUE);
		int nHandle;
		int retVal;
		//打开文件   
		nHandle = _open(pDlg->GetPathName(), _O_BINARY | _O_CREAT | _O_TRUNC | _O_RDWR);
		if (nHandle == -1)
		{
			MessageBox(_T("不能打开文件!"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
			delete   pDlg;
			return;
		}
		//保存结果   
		retVal = _write(nHandle, (void*)m_data.GetBuffer(m_data.GetLength()), m_data.GetLength());
		if (retVal != m_data.GetLength())
		{
			MessageBox(_T("写文件时出错!"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
			delete   pDlg;
			return;
		}
		//关闭文件   
		_close(nHandle);
	}
	delete   pDlg;
}


void CMFCApplication1Dlg::OnBnClickedOpen2()
{
	// TODO:  在此添加控件通知处理程序代码
	//// TODO: Add your control notification handler code here
	m_disfile.Empty();
	//m_code.Empty();
	//m_edit.Empty();
	CString srd;
	CString m_path;
	OPENFILENAME ofn = { 0 };
	BOOL bSetInitialDir = FALSE;

	CString code;
	CString codevalue;
	CString value;

	ofn.Flags = OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST;

	CFileDialog hFileDlg(true, NULL, NULL, ofn.Flags, TEXT("所有文件(*.*)|*.*|"), NULL);
	if (hFileDlg.DoModal() == IDOK)
	{
		m_path = hFileDlg.GetPathName();
		//m_edit += m_path;
		CStdioFile myfile(m_path, CFile::modeRead);
		while (myfile.ReadString(code))
		{
			m_disfile += code;
			m_disfile += "\r\n";
		}
	}
	UpdateData(FALSE);

	/*OPENFILENAME ofn = { 0 };

	ofn.Flags = OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST;
	CFileDialog hFileDlg(TRUE, NULL, NULL, ofn.Flags, TEXT("DXF(*.*)|*.*|"), NULL);
	if (hFileDlg.DoModal() == IDOK)
	{
		path = hFileDlg.GetPathName();
		switchkeyword(path);
	}*/
}


void CMFCApplication1Dlg::OnSaveorigindata()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strText(_T(""));
	GetDlgItemText(IDC_Data_edit, strText); //获取edit box中的数据 

	try
	{
		CStdioFile file;
		file.Open(_T("D:\\abc.txt"), CFile::modeCreate | CFile::modeWrite |
			CFile::typeText);
		//打开D盘的txt文件 
		file.WriteString(strText);  //写入edit box中的数据 
		file.Close();
	}
	catch (CFileException* e)
	{
		e->ReportError();
		e->Delete();

	}
	
}
