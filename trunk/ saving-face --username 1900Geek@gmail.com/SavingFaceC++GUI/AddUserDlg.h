#pragma once
#include "afxwin.h"


// AddUserDlg dialog

class AddUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddUserDlg)

public:
	AddUserDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~AddUserDlg();

// Dialog Data
	enum { IDD = IDD_ADDUSER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
protected:
	CString givenname;
public:
	CString middlename;
	CString sirname;
	afx_msg void OnCbnSelchangeSalutation();
	CComboBox salutation;
	CComboBox suffix;
	afx_msg void OnCbnSelchangeSuffix();
};
