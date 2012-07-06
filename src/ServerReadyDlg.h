/**************************************************************************
*                                                                         *
* Class          ServerReadyDlg                                           *
*                                                                         *
* Author:        Matthew Bazar                                            *
*                                                                         *
* Description:   Interface of the ServerReadyDlg class.                   *
*                                                                         *
* Modifications: Matthew Bazar     11-10-99 ALPHA PRESENTATION            *
*                Matthew Bazar     11-11-99 Default drop down boxes->OPEN *

**************************************************************************/
#if !defined(AFX_SERVERREADYDLG_H__BA43BF06_9631_11D3_B3A8_00C04F29AE8C__INCLUDED_)
#define AFX_SERVERREADYDLG_H__BA43BF06_9631_11D3_B3A8_00C04F29AE8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// ServerReadyDlg dialog                                                   //
/////////////////////////////////////////////////////////////////////////////

class ServerReadyDlg : public CDialog
{
// Construction
public:
	ServerReadyDlg(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(ServerReadyDlg)
	enum { IDD = IDD_SERVERREADY };
	CEdit	m_P8Name;
	CEdit	m_P7Name;
	CEdit	m_P6Name;
	CEdit	m_P5Name;
	CEdit	m_P4Name;
	CEdit	m_P3Name;
	CEdit	m_P2Name;
	CComboBox	m_P8Type;
	CComboBox	m_P7Type;
	CComboBox	m_P6Type;
	CComboBox	m_P5Type;
	CComboBox	m_P4Type;
	CComboBox	m_P2Type;
	CComboBox	m_P3Type;
	CString	m_P1Name;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ServerReadyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	char mybox[20];

	// Generated message map functions
	//{{AFX_MSG(ServerReadyDlg)
	afx_msg void OnServerReadyBack();
	afx_msg void OnServerReadyGo();
	afx_msg void OnSelchangeP2Type();
	afx_msg void OnSelchangeP3Type();
	afx_msg void OnSelchangeP4Type();
	afx_msg void OnSelchangeP5Type();
	afx_msg void OnSelchangeP6Type();
	afx_msg void OnSelchangeP7Type();
	afx_msg void OnSelchangeP8Type();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
		
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERREADYDLG_H__BA43BF06_9631_11D3_B3A8_00C04F29AE8C__INCLUDED_)
