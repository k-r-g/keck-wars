/**************************************************************************
*                                                                         *
* Class Name:    Exit                                                     *
*                                                                         *
* Author:        Matthew Bazar                                            *
*                                                                         *
* Description:   Implementation of Exit Dialog Box. This file is where    *
*                the buttons are handled and sounds are played.           *
*                                                                         *
* Methods:       OnSkip():                                                *
*                     Handles when the 'Skip' Button is pressed.          *
*                OnStartNext():                                           *
*                     Handles when the 'Next' Button is pressed.          *
*                                                                         *
* Modifications: Matthew Bazar     12-08-99 Created                       *
**************************************************************************/
#include "stdafx.h"
#include <mmsystem.h>
#include "keckwars.h"
#include "StartGame.h"
#include "SetupMenuConfigurationDlg.h"
#include "Intro2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// StartGame dialog                                                        //
/////////////////////////////////////////////////////////////////////////////
StartGame::StartGame(CWnd* pParent /*=NULL*/)
	: CDialog(StartGame::IDD, pParent)
{
	//{{AFX_DATA_INIT(StartGame)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
void StartGame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(StartGame)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(StartGame, CDialog)
	//{{AFX_MSG_MAP(StartGame)
	ON_BN_CLICKED(IDSKIP, OnSkip)
	ON_BN_CLICKED(IDC_STARTNEXT, OnStartNext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL StartGame::OnInitDialog() 
{	
	CDialog::OnInitDialog();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// StartGame message handlers                                              //
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
// Dialog box for StartGame ends and the SetupMenuConfiguration dialog //
// box is loaded. (For users who do not wish to hear the introduction) //
/////////////////////////////////////////////////////////////////////////
void StartGame::OnSkip() 
{
	EndDialog(1);
	CSetupMenuConfigurationDlg dlgSetupMenuConfiguration;
	PlaySound("Battle.wav", NULL, SND_ASYNC);
	dlgSetupMenuConfiguration.DoModal();	
}
////////////////////////////////////////////////////////////////////////
// Dialog box for StartGame ends and the Intro2 dialog box is loaded. //
////////////////////////////////////////////////////////////////////////
void StartGame::OnStartNext() 
{
	EndDialog(1);
	Intro2 dlgIntro2;
	dlgIntro2.DoModal();	
}