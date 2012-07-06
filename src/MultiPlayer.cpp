/**************************************************************************
*                                                                         *
* Class Name:    MultiPlayer                                              *
*                                                                         *
* Author:        Matthew Bazar                                            *
*                                                                         *
* Description:   Implementation of MultiPlayer Dialog Box. This file is   *
*                where the buttons are handled.                           *
*                                                                         *
* Methods:       OnMultiBack():                                           *
*                     Handles when the 'Back' Button is pressed.          *
*                OnClient():                                              *
*                     Handles when the 'Client' Button is pressed.        *
*                OnServer():                                              *
*                     Handles when the 'Server' Button is pressed.        *
*                                                                         *
* Modifications: Matthew Bazar     11-10-99 ALPHA PRESENTATION            *
**************************************************************************/
#include "stdafx.h"
#include "SetupMenuConfiguration.h"
#include "SetupMenuConfigurationDlg.h"
#include "MultiPlayer.h"
#include "Client.h"
#include "ServerReadyDlg.h"
#include "SetupGame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern SetupGame *setupGame;

/////////////////////////////////////////////////////////////////////////////
// MultiPlayer dialog                                                      //
/////////////////////////////////////////////////////////////////////////////
MultiPlayer::MultiPlayer(CWnd* pParent /*=NULL*/)
	: CDialog(MultiPlayer::IDD, pParent)
{
	//{{AFX_DATA_INIT(MultiPlayer)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
void MultiPlayer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MultiPlayer)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(MultiPlayer, CDialog)
	//{{AFX_MSG_MAP(MultiPlayer)
	ON_BN_CLICKED(IDC_MULTIBACK, OnMultiBack)
	ON_BN_CLICKED(IDCLIENT, OnClient)
	ON_BN_CLICKED(IDSERVER, OnServer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MultiPlayer message handlers                                            //
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Dialog box for MuiltiPlayer ends and the CSetupMenuConfiguration dialog box //
// is loaded.                                                                  //
/////////////////////////////////////////////////////////////////////////////////
void MultiPlayer::OnMultiBack() 
{
	EndDialog(1);
	CSetupMenuConfigurationDlg dlgCSetupMenuConfiguration;
	dlgCSetupMenuConfiguration.DoModal();	
}
////////////////////////////////////////////////////////////////////////////
// Dialog box for MuiltiPlayer ends and the CClient dialog box is loaded. //
////////////////////////////////////////////////////////////////////////////
void MultiPlayer::OnClient() 
{
	EndDialog(1);
	CClient dlgClient;
	dlgClient.DoModal();
}
////////////////////////////////////////////////////////////////////////////
// The multiPlayer method from the Setup Game class is called, the dialog //
// box for MuiltiPlayer ends and the ServerReadyDlg dialog box is loaded. //
////////////////////////////////////////////////////////////////////////////
void MultiPlayer::OnServer() 
{
	setupGame->multiPlayer(SERVERMODE, NULL, NULL);
	EndDialog(1);
	ServerReadyDlg dlgServer;
	dlgServer.DoModal();
}