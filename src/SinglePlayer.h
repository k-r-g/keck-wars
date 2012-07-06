/**************************************************************************
*                                                                         *
* Class          SinglePlayer                                             *
*                                                                         *
* Author:        Matthew Bazar                                            *
*                                                                         *
* Description:   Interface of the SinglePlayer class.                     *
*                                                                         *
* Modifications: Matthew Bazar     11-10-99 ALPHA PRESENTATION            *
*                Matthew Bazar     11-30-99 User-Defined Mission option   *
*                Brian Birmingham  12-09-99 Calls singlePlayer method in  *
*                                           passing in a buffer           *
**************************************************************************/

#if !defined(AFX_SINGLEPLAYER_H__F5DE95C3_90F9_11D3_B3A1_00C04F29AE79__INCLUDED_)
#define AFX_SINGLEPLAYER_H__F5DE95C3_90F9_11D3_B3A1_00C04F29AE79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/////////////////////////////////////////////////////////////////////////////
// SinglePlayer dialog                                                     //
/////////////////////////////////////////////////////////////////////////////
class SinglePlayer : public CDialog
{
// Construction
public:
	char buffer[3000];
	SinglePlayer(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(SinglePlayer)
	enum { IDD = IDD_SINGLEPLAYER };
	CEdit	m_MissionChoice;
	CString	m_UserFile;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SinglePlayer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	inline CEdit& editUserFile() 
      { return *(CEdit*) GetDlgItem(IDC_USERFILE); }
	int mission;	
	int fd;
	CString userMissionText;

	// Generated message map functions
	//{{AFX_MSG(SinglePlayer)
	virtual BOOL OnInitDialog();
	afx_msg void OnSingleback();
	afx_msg void OnSinglePlayerBack();
	afx_msg void OnMission1();
	afx_msg void OnMission2();
	afx_msg void OnMission3();
	afx_msg void OnSingleGo();
	afx_msg void OnUserDefined();
	afx_msg void OnLoad();
	afx_msg void OnSetfocusUserfile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString processMissionText(int currentMission);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SINGLEPLAYER_H__F5DE95C3_90F9_11D3_B3A1_00C04F29AE79__INCLUDED_)
