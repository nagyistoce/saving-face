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
	CString middlename;
	CString sirname;
	int genderRadioButton;
	CComboBox salutation;
	CComboBox suffix;

public:
	afx_msg void OnCbnSelchangeSalutation();
	afx_msg void OnCbnSelchangeSuffix();
	afx_msg void OnBnClickedRadioMale();
	CString emailAddr;
	afx_msg void OnEnChangeEmail();
};
