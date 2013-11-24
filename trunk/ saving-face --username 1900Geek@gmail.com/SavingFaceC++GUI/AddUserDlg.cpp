// AddUserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SavingFaceC++GUI.h"
#include "AddUserDlg.h"
#include "afxdialogex.h"


// AddUserDlg dialog

IMPLEMENT_DYNAMIC(AddUserDlg, CDialogEx)

AddUserDlg::AddUserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(AddUserDlg::IDD, pParent)
	, givenname(_T(""))
	, middlename(_T(""))
	, sirname(_T(""))
{

}

AddUserDlg::~AddUserDlg()
{
}

void AddUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_GIVENNAME, givenname);
	DDX_Text(pDX, IDC_MIDDLENAME, middlename);
	DDX_Text(pDX, IDC_SIRNAME, sirname);
	DDX_Control(pDX, IDC_SALUTATION, salutation);
	salutation.AddString(_T("Mr."));
	salutation.AddString(_T("Mrs."));
	salutation.AddString(_T("Master"));
	salutation.AddString(_T("Miss"));
	salutation.AddString(_T("Dr."));
	salutation.AddString(_T("Prof."));
	DDX_Control(pDX, IDC_SUFFIX, suffix);
	suffix.AddString(_T("Jr."));
	suffix.AddString(_T("II"));
	suffix.AddString(_T("III."));
	suffix.AddString(_T("IV"));
	suffix.AddString(_T("V."));
	suffix.AddString(_T("VI"));
	suffix.AddString(_T("VII"));
	suffix.AddString(_T("VIII"));
}


BEGIN_MESSAGE_MAP(AddUserDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddUserDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &AddUserDlg::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_SALUTATION, &AddUserDlg::OnCbnSelchangeSalutation)
	ON_CBN_SELCHANGE(IDC_SUFFIX, &AddUserDlg::OnCbnSelchangeSuffix)
END_MESSAGE_MAP()


// AddUserDlg message handlers


void AddUserDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CString message;
	CString temp;
	message.Format(_T(""));
	salutation.GetWindowTextW(message);
	temp.Format(givenname.GetString());
	if(temp.GetLength()) message.Append(_T(" ")+temp);
	temp.Format(middlename.GetString());
	if(temp.GetLength()) message.Append(_T(" ")+temp);
	temp.Format(sirname.GetString());
	if(temp.GetLength()) message.Append(_T(" ")+temp);
	suffix.GetWindowTextW(temp);
	if(temp.GetLength()) message.Append(_T(" ")+temp);
	MessageBox(message,0,MB_OK);
	CDialogEx::OnOK();
}


void AddUserDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void AddUserDlg::OnCbnSelchangeSalutation()
{
	// TODO: Add your control notification handler code here
}


void AddUserDlg::OnCbnSelchangeSuffix()
{
	// TODO: Add your control notification handler code here
}
