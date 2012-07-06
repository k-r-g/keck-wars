/**************************************************************************
*                                                                         *
* Class Name:    Intro3                                                   *
*                                                                         *
* Author:        Matthew Bazar                                            *
*                                                                         *
* Description:   Implementation of Intro3 Dialog Box. This file is where  *
*                the buttons are handled and sounds are played.           *
*                                                                         *
* Methods:       OnIntro3Next():                                          *
*                     Handles when the 'Next' Button is pressed.          *
*                                                                         *
* Modifications: Matthew Bazar     12-08-99 Created                       *
**************************************************************************/
#include "stdafx.h"
#include "keckwars.h"
#include "Intro3.h"
#include "SetupMenuConfigurationDlg.h"
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Intro3 dialog                                                           //
/////////////////////////////////////////////////////////////////////////////
Intro3::Intro3(CWnd* pParent /*=NULL*/)
	: CDialog(Intro3::IDD, pParent)
{
	//{{AFX_DATA_INIT(Intro3)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
void Intro3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Intro3)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(Intro3, CDialog)
	//{{AFX_MSG_MAP(Intro3)
	ON_BN_CLICKED(IDC_INTRO3NEXT, OnIntro3Next)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL Intro3::OnInitDialog() 
{
	CDialog::OnInitDialog();
	PlaySound("Text2.wav", NULL, SND_ASYNC);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// Intro3 message handlers                                                 //
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
// Dialog box for Intro3 ends, the SetupMenuConfiguration dialog   //
// box is loaded and the introductory Battle sound begins to play. //
/////////////////////////////////////////////////////////////////////
void Intro3::OnIntro3Next() 
{
	EndDialog(1);
	CSetupMenuConfigurationDlg dlgSetupMenuConfiguration;
	PlaySound("Battle.wav", NULL, SND_ASYNC);
	dlgSetupMenuConfiguration.DoModal();	
}