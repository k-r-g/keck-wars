/**************************************************************************
*                                                                         *
* Class Name:    MultiPlayer                                              *
*                                                                         *
* Author:        Matthew Bazar                                            *
*                                                                         *
* Description:   Implementation of MultiPlayer Dialog Box. This file is   *
*                where the buttons are handled.                           *
*                                                                         *
* Methods:       OnServerReadyBack():                                     *
*                     Handles when the 'Back' Button is pressed.          *
*                OnServerReadyGo():                                       *
*                     Handles when the 'Go' Button is pressed.            *
*                OnClient():                                              *
*                     Handles when the 'Client' Button is pressed.        *
*                OnServer():                                              *
*                     Handles when the 'Server' Button is pressed.        *
*                selectionChange(int slotNumber):                         *
*                     Receives a slot to which a change has been made and *
*                     communicates that with the SetupGame class.         *
*                OnTimer(UINT nIDEvent):                                  *
*                     Handles events after an amount of times has passed. *
*                OnSelchangeP[number]Type():                              *
*                     Handles when a change to a type of pilot has been   * 
*                     made to one of the seven drop down boxes.           *
*                     NOTE: There are seven of these methods that all do  *
*                     the same thing. [number] refers to the specific     *
*                     drop down boxes 1 - 7.                              *
*                                                                         *
* Modifications: Matthew Bazar     11-10-99 ALPHA PRESENTATION            *
*                                  11-11-99 Default slots to "open"       *
*                                  11-20-99 Configure edit fields to be   *
*                                           editable or non-editable      *
*                                           depending on what is chosen.  *
*                                  11-30-99 User-Defined missions added   *
**************************************************************************/
#include "stdafx.h"
#include <mmsystem.h>
#include "keckwars.h"
#include "ServerReadyDlg.h"
#include "SetupMenuConfigurationDlg.h"
#include "MultiPlayer.h"
#include "SetupGame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern SetupGame *setupGame;
/////////////////////////////////////////////////////////////////////////////
// ServerReadyDlg dialog                                                   //
/////////////////////////////////////////////////////////////////////////////

ServerReadyDlg::ServerReadyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ServerReadyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ServerReadyDlg)
	m_P1Name = _T("");
	//}}AFX_DATA_INIT
}
void ServerReadyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ServerReadyDlg)
	DDX_Control(pDX, IDC_P8NAME, m_P8Name);
	DDX_Control(pDX, IDC_P7NAME, m_P7Name);
	DDX_Control(pDX, IDC_P6NAME, m_P6Name);
	DDX_Control(pDX, IDC_P5NAME, m_P5Name);
	DDX_Control(pDX, IDC_P4NAME, m_P4Name);
	DDX_Control(pDX, IDC_P3NAME, m_P3Name);
	DDX_Control(pDX, IDC_P2NAME, m_P2Name);
	DDX_Control(pDX, IDC_P8TYPE, m_P8Type);
	DDX_Control(pDX, IDC_P7TYPE, m_P7Type);
	DDX_Control(pDX, IDC_P6TYPE, m_P6Type);
	DDX_Control(pDX, IDC_P5TYPE, m_P5Type);
	DDX_Control(pDX, IDC_P4TYPE, m_P4Type);
	DDX_Control(pDX, IDC_P2TYPE, m_P2Type);
	DDX_Control(pDX, IDC_P3TYPE, m_P3Type);
	DDX_Text(pDX, IDC_P1NAME, m_P1Name);
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(ServerReadyDlg, CDialog)
	//{{AFX_MSG_MAP(ServerReadyDlg)
	ON_BN_CLICKED(IDSERVERREADYBACK, OnServerReadyBack)
	ON_BN_CLICKED(IDSERVERREADYGO, OnServerReadyGo)
	ON_CBN_SELCHANGE(IDC_P2TYPE, OnSelchangeP2Type)
	ON_CBN_SELCHANGE(IDC_P3TYPE, OnSelchangeP3Type)
	ON_CBN_SELCHANGE(IDC_P4TYPE, OnSelchangeP4Type)
	ON_CBN_SELCHANGE(IDC_P5TYPE, OnSelchangeP5Type)
	ON_CBN_SELCHANGE(IDC_P6TYPE, OnSelchangeP6Type)
	ON_CBN_SELCHANGE(IDC_P7TYPE, OnSelchangeP7Type)
	ON_CBN_SELCHANGE(IDC_P8TYPE, OnSelchangeP8Type)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL ServerReadyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetDlgItemText(IDC_P1NAME, setupGame->playerSlot[0]->playerName);	
	SetDlgItemText(IDC_P2NAME, setupGame->playerSlot[1]->playerName);
	SetDlgItemText(IDC_P3NAME, setupGame->playerSlot[2]->playerName);
	SetDlgItemText(IDC_P4NAME, setupGame->playerSlot[3]->playerName);	
	SetDlgItemText(IDC_P5NAME, setupGame->playerSlot[4]->playerName);	
	SetDlgItemText(IDC_P6NAME, setupGame->playerSlot[5]->playerName);	
	SetDlgItemText(IDC_P7NAME, setupGame->playerSlot[6]->playerName);	
	SetDlgItemText(IDC_P8NAME, setupGame->playerSlot[7]->playerName);	

	m_P2Type.SetCurSel(0);
	m_P3Type.SetCurSel(0);
	m_P4Type.SetCurSel(0);
	m_P5Type.SetCurSel(0);
	m_P6Type.SetCurSel(0);
	m_P7Type.SetCurSel(0);
	m_P8Type.SetCurSel(0);

	m_P2Name.SetReadOnly(true);
	m_P3Name.SetReadOnly(true);
	m_P4Name.SetReadOnly(true);
	m_P5Name.SetReadOnly(true);
	m_P6Name.SetReadOnly(true);
	m_P7Name.SetReadOnly(true);
	m_P8Name.SetReadOnly(true);

	SetTimer(IDC_P1TYPE, 500, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// ServerReadyDlg message handlers                                         //
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// Dialog box for ServerReadyDlg ends and the MultiPlayer dialog box is loaded. //
//////////////////////////////////////////////////////////////////////////////////
void ServerReadyDlg::OnServerReadyBack() 
{
	setupGame->endGame();
	EndDialog(1);
	MultiPlayer dlgMultiPlayer;
	dlgMultiPlayer.DoModal();
}
/////////////////////////////////////////////////////////////////////////////////
// The go method from the Setup Game class is called to start the Multi Player //
// game. Upon quitting the game, the dialog box for MuiltiPlayer ends and the  //
// CSetupMenuConfiguation dialog box is loaded.                                //
/////////////////////////////////////////////////////////////////////////////////
void ServerReadyDlg::OnServerReadyGo() 
{
	PlaySound("Shoot.wav", NULL, SND_ASYNC);
	setupGame->go();
	EndDialog(1);	
	CSetupMenuConfigurationDlg dlgSetupMenuConfiguration;
	dlgSetupMenuConfiguration.DoModal();
}
/////////////////////////////////////////////////////////////////////////////
// This method loads into a text field the name of a client. It only calls //
// setupGame if the slot is open.                                          //
/////////////////////////////////////////////////////////////////////////////
void ServerReadyDlg::OnTimer(UINT nIDEvent) 
{	 
	DlgDirSelectComboBox(mybox, IDC_P2TYPE);   
	if (mybox[0] == 'O') SetDlgItemText(IDC_P2NAME, setupGame->playerSlot[1]->playerName);
	DlgDirSelectComboBox(mybox, IDC_P3TYPE);   
	if (mybox[0] == 'O') SetDlgItemText(IDC_P3NAME, setupGame->playerSlot[2]->playerName);
	DlgDirSelectComboBox(mybox, IDC_P4TYPE);   
	if (mybox[0] == 'O') SetDlgItemText(IDC_P4NAME, setupGame->playerSlot[3]->playerName);	
	DlgDirSelectComboBox(mybox, IDC_P5TYPE);   
	if (mybox[0] == 'O') SetDlgItemText(IDC_P5NAME, setupGame->playerSlot[4]->playerName);	
	DlgDirSelectComboBox(mybox, IDC_P6TYPE);   
	if (mybox[0] == 'O') SetDlgItemText(IDC_P6NAME, setupGame->playerSlot[5]->playerName);	
	DlgDirSelectComboBox(mybox, IDC_P7TYPE);   
	if (mybox[0] == 'O') SetDlgItemText(IDC_P7NAME, setupGame->playerSlot[6]->playerName);	
	DlgDirSelectComboBox(mybox, IDC_P8TYPE);   
	if (mybox[0] == 'O') SetDlgItemText(IDC_P8NAME, setupGame->playerSlot[7]->playerName);	

	CDialog::OnTimer(nIDEvent);
}
/////////////////////////////////////////////////////////////////////////////////
// The following seven methods are called when a new selection in a drop down  //
// combo box is made. The current selection is gathered from the combo box and //
// stored in the variable mybox. Next the selectionChange method is called to  //
// communicate with the SetupGame class what the current selection is.         // 
/////////////////////////////////////////////////////////////////////////////////
void ServerReadyDlg::OnSelchangeP2Type() 
{		
	DlgDirSelectComboBox(mybox, IDC_P2TYPE);   
	if (mybox[0] == 'C')
	{			
		setupGame->closePlayerSlot(1);
		m_P2Name.SetReadOnly(true);
		SetDlgItemText(IDC_P2NAME, " ");	
	}
	else if (mybox[0] == 'O')
	{
		m_P2Name.SetReadOnly(true);
		setupGame->playerSlot[1]->playerName = "Player 2";
		setupGame->openPlayerSlot(1);		
	}
	else if (mybox[12] == '1')
	{
		m_P2Name.SetReadOnly(false);
		setupGame->playerSlot[1]->playerName = "Player 2";
		setupGame->createComputerPilotSlot(1, 1);		
	}
	else if (mybox[12] == '2') 
	{
		m_P2Name.SetReadOnly(false);
		setupGame->playerSlot[1]->playerName = "Player 2";
		setupGame->createComputerPilotSlot(1, 2);
	}
	else if (mybox[12] == '3')
	{
		m_P2Name.SetReadOnly(false);
		setupGame->playerSlot[1]->playerName = "Player 2";
		setupGame->createComputerPilotSlot(1, 3);
	}
}
void ServerReadyDlg::OnSelchangeP3Type() 
{
	DlgDirSelectComboBox(mybox, IDC_P3TYPE);   
	if (mybox[0] == 'C')
	{	
		setupGame->closePlayerSlot(2);
		m_P3Name.SetReadOnly(true);
		SetDlgItemText(IDC_P3NAME, " ");	
		
	}
	else if (mybox[0] == 'O')
	{
		m_P3Name.SetReadOnly(true);
		setupGame->playerSlot[2]->playerName = "Player 3";
		setupGame->openPlayerSlot(2);		
	}
	else if (mybox[12] == '1')
	{
		m_P3Name.SetReadOnly(false);
		setupGame->playerSlot[2]->playerName = "Player 3";
		setupGame->createComputerPilotSlot(2, 1);		
	}
	else if (mybox[12] == '2')
	{
		m_P3Name.SetReadOnly(false);
		setupGame->playerSlot[2]->playerName = "Player 3";
		setupGame->createComputerPilotSlot(2, 2);
	}
	else if (mybox[12] == '3')
	{
		m_P3Name.SetReadOnly(false);
		setupGame->playerSlot[2]->playerName = "Player 3";
		setupGame->createComputerPilotSlot(2, 3);
	}
}
void ServerReadyDlg::OnSelchangeP4Type() 
{
	DlgDirSelectComboBox(mybox, IDC_P4TYPE);   
	if (mybox[0] == 'C')
	{			
		setupGame->closePlayerSlot(3);
		m_P4Name.SetReadOnly(true);
		SetDlgItemText(IDC_P4NAME, " ");	
	}
	else if (mybox[0] == 'O')
	{
		m_P4Name.SetReadOnly(true);
		setupGame->playerSlot[3]->playerName = "Player 4";
		setupGame->openPlayerSlot(3);		
	}
	else if (mybox[12] == '1')
	{
		m_P4Name.SetReadOnly(false);
		setupGame->playerSlot[3]->playerName = "Player 4";
		setupGame->createComputerPilotSlot(3, 1);		
	}
	else if (mybox[12] == '2')
	{
		m_P4Name.SetReadOnly(false);
		setupGame->playerSlot[3]->playerName = "Player 4";
		setupGame->createComputerPilotSlot(3, 2);
	}
	else if (mybox[12] == '3')
	{
		m_P4Name.SetReadOnly(false);
		setupGame->playerSlot[3]->playerName = "Player 4";
		setupGame->createComputerPilotSlot(3, 3);
	}
}
void ServerReadyDlg::OnSelchangeP5Type() 
{
	DlgDirSelectComboBox(mybox, IDC_P5TYPE);   
	if (mybox[0] == 'C')
	{			
		setupGame->closePlayerSlot(4);
		m_P5Name.SetReadOnly(true);
		SetDlgItemText(IDC_P5NAME, " ");	
	}
	else if (mybox[0] == 'O')
	{
		m_P5Name.SetReadOnly(true);
		setupGame->playerSlot[4]->playerName = "Player 5";
		setupGame->openPlayerSlot(4);		
	}
	else if (mybox[12] == '1')
	{
		m_P5Name.SetReadOnly(false);
		setupGame->playerSlot[4]->playerName = "Player 5";
		setupGame->createComputerPilotSlot(4, 1);		
	}
	else if (mybox[12] == '2')
	{
		m_P5Name.SetReadOnly(false);
		setupGame->playerSlot[4]->playerName = "Player 5";
		setupGame->createComputerPilotSlot(4, 2);
	}
	else if (mybox[12] == '3')
	{
		m_P5Name.SetReadOnly(false);
		setupGame->playerSlot[4]->playerName = "Player 5";
		setupGame->createComputerPilotSlot(4, 3);
	}
}
void ServerReadyDlg::OnSelchangeP6Type() 
{
	DlgDirSelectComboBox(mybox, IDC_P6TYPE);   
	if (mybox[0] == 'C')
	{			
		setupGame->closePlayerSlot(5);
		m_P6Name.SetReadOnly(true);
		SetDlgItemText(IDC_P6NAME, " ");	
	}
	else if (mybox[0] == 'O')
	{
		m_P6Name.SetReadOnly(true);
		setupGame->playerSlot[5]->playerName = "Player 6";
		setupGame->openPlayerSlot(5);		
	}
	else if (mybox[12] == '1')
	{
		m_P6Name.SetReadOnly(false);
		setupGame->playerSlot[5]->playerName = "Player 6";
		setupGame->createComputerPilotSlot(5, 1);		
	}
	else if (mybox[12] == '2')
	{
		m_P6Name.SetReadOnly(false);
		setupGame->playerSlot[5]->playerName = "Player 6";
		setupGame->createComputerPilotSlot(5, 2);
	}
	else if (mybox[12] == '3')
	{
		m_P6Name.SetReadOnly(false);
		setupGame->playerSlot[5]->playerName = "Player 6";
		setupGame->createComputerPilotSlot(5, 3);
	}
}
void ServerReadyDlg::OnSelchangeP7Type() 
{
	DlgDirSelectComboBox(mybox, IDC_P7TYPE);   
	if (mybox[0] == 'C')
	{			
		setupGame->closePlayerSlot(6);
		m_P7Name.SetReadOnly(true);
		SetDlgItemText(IDC_P7NAME, " ");	
	}
	else if (mybox[0] == 'O')
	{
		m_P7Name.SetReadOnly(true);
		setupGame->playerSlot[6]->playerName = "Player 7";
		setupGame->openPlayerSlot(6);		
	}
	else if (mybox[12] == '1')
	{
		m_P7Name.SetReadOnly(false);
		setupGame->playerSlot[6]->playerName = "Player 7";
		setupGame->createComputerPilotSlot(6, 1);		
	}
	else if (mybox[12] == '2')
	{
		m_P7Name.SetReadOnly(false);
		setupGame->playerSlot[6]->playerName = "Player 7";
		setupGame->createComputerPilotSlot(6, 2);
	}
	else if (mybox[12] == '3')
	{
		m_P7Name.SetReadOnly(false);
		setupGame->playerSlot[6]->playerName = "Player 7";
		setupGame->createComputerPilotSlot(6, 3);
	}
}
void ServerReadyDlg::OnSelchangeP8Type() 
{
	DlgDirSelectComboBox(mybox, IDC_P8TYPE);   
	if (mybox[0] == 'C')
	{			
		setupGame->closePlayerSlot(7);
		m_P8Name.SetReadOnly(true);
		SetDlgItemText(IDC_P8NAME, " ");	
	}
	else if (mybox[0] == 'O')
	{
		m_P8Name.SetReadOnly(true);
		setupGame->playerSlot[7]->playerName = "Player 8";
		setupGame->openPlayerSlot(7);		
	}
	else if (mybox[12] == '1')
	{
		m_P8Name.SetReadOnly(false);
		setupGame->playerSlot[7]->playerName = "Player 8";
		setupGame->createComputerPilotSlot(7, 1);		
	}
	else if (mybox[12] == '2')
	{
		m_P8Name.SetReadOnly(false);
		setupGame->playerSlot[7]->playerName = "Player 8";
		setupGame->createComputerPilotSlot(7, 2);
	}
	else if (mybox[12] == '3')
	{
		m_P8Name.SetReadOnly(false);
		setupGame->playerSlot[7]->playerName = "Player 8";
		setupGame->createComputerPilotSlot(7, 3);
	}
}