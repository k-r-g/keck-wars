/**************************************************************************
*                                                                         *
* Class Name:    CSetupMenuConfigurationApp                               *
*                                                                         *
* Author:        Matthew Bazar                                            *
*                                                                         *
* Description:   Defines the class behaviors for the application.         *
*                                                                         *
* Modifications: Matthew Bazar     11-10-99 ALPHA PRESENTATION            *
**************************************************************************/
#include "stdafx.h"
#include "SetupMenuConfiguration.h"
#include "SetupMenuConfigurationDlg.h"
#include "StartGame.h"
#include "SetupGame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupMenuConfigurationApp                                              //
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CSetupMenuConfigurationApp, CWinApp)
	//{{AFX_MSG_MAP(CSetupMenuConfigurationApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupMenuConfigurationApp construction                                 //
/////////////////////////////////////////////////////////////////////////////
extern SetupGame *setupGame;
CSetupMenuConfigurationApp::CSetupMenuConfigurationApp()
{	
	 setupGame = new SetupGame();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSetupMenuConfigurationApp object                      //
/////////////////////////////////////////////////////////////////////////////
CSetupMenuConfigurationApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSetupMenuConfigurationApp initialization                               //
/////////////////////////////////////////////////////////////////////////////
BOOL CSetupMenuConfigurationApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	StartGame dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
