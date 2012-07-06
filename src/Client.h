/**************************************************************************
*                                                                         *
* Class          CClient                                                  *
*                                                                         *
* Author:        Matthew Bazar                                            *
*                                                                         *
* Description:   Interface of the CClient class.                          *
*                                                                         *
* Modifications: Matthew Bazar     11-10-99 ALPHA PRESENTATION            *
**************************************************************************/
#if !defined(AFX_CLIENT_H__56644F73_9282_11D3_B3A4_00C04F29AE79__INCLUDED_)
#define AFX_CLIENT_H__56644F73_9282_11D3_B3A4_00C04F29AE79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CClient dialog                                                          //
/////////////////////////////////////////////////////////////////////////////

class CClient : public CDialog
{
// Construction
public:
	CClient(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CClient)
	enum { IDD = IDD_CLIENT };
	CString	m_Screen_Name;
	CString	m_Server_Name;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClient)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	inline CEdit& editScreenName() 
      { return *(CEdit*) GetDlgItem(IDC_SCREENNAME); }
	inline CEdit& editServerName() 
      { return *(CEdit*) GetDlgItem(IDC_SERVERNAME); }
	// Generated message map functions
	//{{AFX_MSG(CClient)
	afx_msg void OnClientBack();
	afx_msg void OnClientGo();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENT_H__56644F73_9282_11D3_B3A4_00C04F29AE79__INCLUDED_)
