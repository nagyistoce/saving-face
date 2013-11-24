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
{

}

AddUserDlg::~AddUserDlg()
{
}

void AddUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AddUserDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddUserDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &AddUserDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// AddUserDlg message handlers


void AddUserDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void AddUserDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
