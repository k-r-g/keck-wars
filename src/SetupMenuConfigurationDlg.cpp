/**************************************************************************
*                                                                         *
* Class Name:    CSetupMenuConfigurationDlg                               *
*                                                                         *
* Author:        Matthew Bazar                                            *
*                                                                         *
* Description:   Implementation of CSetupMenuConfigurationDlg Dialog Box. *
*                This file is where the buttons are handled.              *
*                                                                         *
* Methods:       OnSingleplayer():                                        *
*                     Handles when the 'SinglePlayer' Button is pressed.  *
*                OnMultiplayer():                                         *
*                     Handles when the 'MultiPlayer' Button is pressed.   *
*                OnExit():                                                *
*                     Handles when the 'Exit' Button is pressed.          *
*                                                                         *
* Modifications: Matthew Bazar     11-10-99 ALPHA PRESENTATION            *
**************************************************************************/
#include "stdafx.h"
#include <mmsystem.h>
#include "SetupMenuConfiguration.h"
#include "SetupMenuConfigurationDlg.h"
#include "SinglePlayer.h"
#include "MultiPlayer.h"
#include "Exit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupMenuConfigurationDlg dialog                                       //
/////////////////////////////////////////////////////////////////////////////
CSetupMenuConfigurationDlg::CSetupMenuConfigurationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetupMenuConfigurationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetupMenuConfigurationDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
void CSetupMenuConfigurationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupMenuConfigurationDlg)
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(CSetupMenuConfigurationDlg, CDialog)
	//{{AFX_MSG_MAP(CSetupMenuConfigurationDlg)
	ON_BN_CLICKED(IDSINGLEPLAYER, OnSingleplayer)
	ON_BN_CLICKED(IDMULTIPLAYER, OnMultiplayer)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupMenuConfigurationDlg message handlers                             //
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
// Dialog box for CSetupMenuConfigurationDlg ends and the SinglePlayer //
// dialog box is loaded.                                               //
/////////////////////////////////////////////////////////////////////////
void CSetupMenuConfigurationDlg::OnSingleplayer() 
{	
	EndDialog(1);
	SinglePlayer dlgSinglePlayer;
	dlgSinglePlayer.DoModal();
}
////////////////////////////////////////////////////////////////////////
// Dialog box for CSetupMenuConfigurationDlg ends and the MultiPlayer //
// dialog box is loaded.                                              //
////////////////////////////////////////////////////////////////////////
void CSetupMenuConfigurationDlg::OnMultiplayer() 
{
	EndDialog(1);
	MultiPlayer dlgMultiPlayer;
	dlgMultiPlayer.DoModal();
}
//////////////////////////////////////////////////////////////////////////////
// A dialog box pops up asking if the user really wants to quit the         //
// application. If the user chooses 'no', the dialog box closes. If the     //
// user chosees 'yes', the CSetupMenuConfigurationDlg dialog box ends along //
// with the warning dialog box.                                             //
//////////////////////////////////////////////////////////////////////////////
void CSetupMenuConfigurationDlg::OnExit() 
{
	EndDialog(1);
	Exit dlgExit;
	dlgExit.DoModal();
}