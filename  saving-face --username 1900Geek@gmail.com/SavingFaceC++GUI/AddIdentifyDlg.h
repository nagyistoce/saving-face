#pragma once


// AddIdentifyDlg dialog

class AddIdentifyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddIdentifyDlg)

public:
	AddIdentifyDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~AddIdentifyDlg();

// Dialog Data
	enum { IDD = IDD_ADD_OR_ID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAddUser();
};
