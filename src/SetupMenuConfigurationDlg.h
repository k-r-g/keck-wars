/**************************************************************************
*                                                                         *
* Class          CSetupMenuConfigurationDlg                               *
*                                                                         *
* Author:        Matthew Bazar                                            *
*                                                                         *
* Description:   Interface of the CSetupMenuConfigurationDlg class.       *
*                                                                         *
* Modifications: Matthew Bazar     11-10-99 ALPHA PRESENTATION            *
**************************************************************************/
#if !defined(AFX_SETUPMENUCONFIGURATIONDLG_H__14BE77C7_90F3_11D3_B3AE_00C04F29AE50__INCLUDED_)
#define AFX_SETUPMENUCONFIGURATIONDLG_H__14BE77C7_90F3_11D3_B3AE_00C04F29AE50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSetupMenuConfigurationDlg dialog                                       //
/////////////////////////////////////////////////////////////////////////////
class CSetupMenuConfigurationDlg : public CDialog
{
// Construction
public:	
	CSetupMenuConfigurationDlg(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CSetupMenuConfigurationDlg)
	enum { IDD = IDD_SETUPMENUCONFIGURATION_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetupMenuConfigurationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSetupMenuConfigurationDlg)
	afx_msg void OnSingleplayer();
	afx_msg void OnMultiplayer();
	afx_msg void OnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUPMENUCONFIGURATIONDLG_H__14BE77C7_90F3_11D3_B3AE_00C04F29AE50__INCLUDED_)
