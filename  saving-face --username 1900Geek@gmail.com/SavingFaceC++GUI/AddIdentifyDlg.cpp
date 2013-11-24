// AddIdentifyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SavingFaceC++GUI.h"
#include "AddIdentifyDlg.h"
#include "AddUserDlg.h"
#include "afxdialogex.h"


// AddIdentifyDlg dialog

IMPLEMENT_DYNAMIC(AddIdentifyDlg, CDialogEx)

AddIdentifyDlg::AddIdentifyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(AddIdentifyDlg::IDD, pParent)
{

}

AddIdentifyDlg::~AddIdentifyDlg()
{
}

void AddIdentifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AddIdentifyDlg, CDialogEx)
	ON_BN_CLICKED(ID_ADD_USER, &AddIdentifyDlg::OnBnClickedAddUser)
END_MESSAGE_MAP()


// AddIdentifyDlg message handlers


void AddIdentifyDlg::OnBnClickedAddUser()
{
	// TODO: Add your control notification handler code here
	AddUserDlg NewUserDlg;
	NewUserDlg.DoModal();
	CDialogEx::OnOK();
}
