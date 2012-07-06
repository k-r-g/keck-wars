/**************************************************************************
*                                                                         *
* Class Name:    CClient                                                  *
*                                                                         *
* Author:        Matthew Bazar                                            *
*                                                                         *
* Description:   Implementation of Client Dialog Box. This file is where  *
*                the buttons and edit fields are handled.                 *
*                                                                         *
* Methods:       OnClientBack():                                          *
*                     Handles when the 'Back' Button is pressed.          *
*                OnClientGo():                                            *
*                     Handles when the 'Go' Button is pressed.            *
*                                                                         *
* Modifications: Matthew Bazar     11-10-99 ALPHA PRESENTATION            *
**************************************************************************/
#include "stdafx.h"
#include <mmsystem.h>
#include "SetupMenuConfiguration.h"
#include "SetupMenuConfigurationDlg.h"
#include "Client.h"
#include "MultiPlayer.h"
#include "SetupGame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern SetupGame *setupGame;

/////////////////////////////////////////////////////////////////////////////
// CClient dialog                                                          //
/////////////////////////////////////////////////////////////////////////////
CClient::CClient(CWnd* pParent /*=NULL*/)
	: CDialog(CClient::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClient)
	m_Screen_Name = _T("");
	m_Server_Name = _T("");
	//}}AFX_DATA_INIT
}
void CClient::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClient)
	DDX_Text(pDX, IDC_SCREENNAME, m_Screen_Name);
	DDX_Text(pDX, IDC_SERVERNAME, m_Server_Name);
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(CClient, CDialog)
	//{{AFX_MSG_MAP(CClient)
	ON_BN_CLICKED(IDCLIENTBACK, OnClientBack)
	ON_BN_CLICKED(IDCLIENTGO, OnClientGo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CClient::OnInitDialog() 
{	
	CDialog::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////
// CClient message handlers                                                //
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Dialog box for Client ends and the MultiPlayer dialog box is loaded. //
//////////////////////////////////////////////////////////////////////////
void CClient::OnClientBack() 
{
	EndDialog(1);
	MultiPlayer dlgMultiPlayer;
	dlgMultiPlayer.DoModal();
}
/////////////////////////////////////////////////////////////////////////////////
// If no input is entered in the Screen Name and Server Name fields, an error  //
// message will appear and then prompt the user for input. Otherwise, the      //
// multiPlayer method in the Setup Game class is called to begin game play.    //
// Upon returning from game play, the Client dialog box ends and the main menu //
// dialog box (CSetupMenuConfiguration) is loaded.                             //
/////////////////////////////////////////////////////////////////////////////////
void CClient::OnClientGo() 
{	
	UpdateData(TRUE);
	if (m_Screen_Name.GetLength() == 0) 
	{
		MessageBeep(MB_ICONASTERISK);
		AfxMessageBox("ERROR: Blank Field. A Value must be entered for Screen Name.",
			MB_OK | MB_ICONINFORMATION);
		editScreenName().SetFocus();
	}
	else if (m_Server_Name.GetLength() == 0)
	{
		MessageBeep(MB_ICONASTERISK);
		AfxMessageBox("ERROR: Blank Field. A Value must be entered for Server Name.",
			MB_OK | MB_ICONINFORMATION);
		editServerName().SetFocus();
	}
   	else
	{	
		PlaySound("Shoot.wav", NULL, SND_ASYNC);
		setupGame->multiPlayer(CLIENTMODE, m_Server_Name.GetBuffer(m_Server_Name.GetLength ()), 
			m_Screen_Name.GetBuffer(m_Screen_Name.GetLength()) );
		EndDialog(1);
		CSetupMenuConfigurationDlg dlgCSetupMenuConfiguration;
		dlgCSetupMenuConfiguration.DoModal();
	}
}
