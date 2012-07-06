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
*                     Handles when the 'Exit' Button is pressed.          *
*                                                                         *
* Modifications: Matthew Bazar     12-08-99 Created                       *
**************************************************************************/
#include "stdafx.h"
#include <mmsystem.h>
#include "keckwars.h"
#include "Exit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Exit dialog                                                             //
/////////////////////////////////////////////////////////////////////////////
Exit::Exit(CWnd* pParent /*=NULL*/)
	: CDialog(Exit::IDD, pParent)
{
	//{{AFX_DATA_INIT(Exit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
void Exit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Exit)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(Exit, CDialog)
	//{{AFX_MSG_MAP(Exit)
	ON_BN_CLICKED(IDC_SKIP, OnSkip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL Exit::OnInitDialog() 
{
	PlaySound("AxelF.wav", NULL, SND_ASYNC);
	CDialog::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// Exit message handlers                                                   //
/////////////////////////////////////////////////////////////////////////////

///////////////////////////////
// Dialog box for Exit ends. // 
///////////////////////////////
void Exit::OnSkip() 
{
	EndDialog(1);	
	
}