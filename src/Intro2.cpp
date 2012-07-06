/**************************************************************************
*                                                                         *
* Class Name:    Intro2                                                   *
*                                                                         *
* Author:        Matthew Bazar                                            *
*                                                                         *
* Description:   Implementation of Intro2 Dialog Box. This file is where  *
*                the buttons are handled and sounds are played.           *
*                                                                         *
* Methods:       OnIntro2Next():                                          *
*                     Handles when the 'Next' Button is pressed.          *
*                                                                         *
* Modifications: Matthew Bazar     12-08-99 Created                       *
**************************************************************************/
#include "stdafx.h"
#include <mmsystem.h>
#include "keckwars.h"
#include "Intro2.h"
#include "Intro3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Intro2 dialog                                                           //
/////////////////////////////////////////////////////////////////////////////
Intro2::Intro2(CWnd* pParent /*=NULL*/)
	: CDialog(Intro2::IDD, pParent)
{
	//{{AFX_DATA_INIT(Intro2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
void Intro2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Intro2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(Intro2, CDialog)
	//{{AFX_MSG_MAP(Intro2)
	ON_BN_CLICKED(IDC_INTRO2NEXT, OnIntro2Next)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL Intro2::OnInitDialog() 
{
	PlaySound("Text1.wav", NULL, SND_ASYNC);
	CDialog::OnInitDialog();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}/////////////////////////////////////////////////////////////////////////////
// Intro2 message handlers                                                 //
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
// Dialog box for Intro2 ends and the Intro3 dialog box is loaded. //
/////////////////////////////////////////////////////////////////////
void Intro2::OnIntro2Next() 
{
	EndDialog(1);
	Intro3 dlgIntro3;
	dlgIntro3.DoModal();	
}
