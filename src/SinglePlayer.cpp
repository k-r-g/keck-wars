/**************************************************************************
*                                                                         *
* Class Name:    SinglePlayer                                             *
*                                                                         *
* Author:        Matthew Bazar                                            *
*                                                                         *
* Description:   Implementation of SinglePlayer Dialog Box. This file is  *
*                where the buttons are handled.                           *
*                                                                         *
* Methods:       processMissionText(int currentMission):                  *
*                     Gets the text of a mission from a file.             *
*                OnSinglePlayerBack():                                    *
*                     Handles when the 'Back' Button is pressed.          *
*                OnMission1():                                            *
*                     Handles when the 'Mission1' Radio Button is chosen. *
*                OnMission2():                                            *
*                     Handles when the 'Mission2' Radio Button is chosen. *
*                OnMission3():                                            *
*                     Handles when the 'Mission3' Radio Button is chosen. *
*                OnUserDefined():                                         *
*                     Handles when the 'UserDefined' Radio Button is      *
*                     chosen.                                             *
*                OnSetfocusUserfile():                                    *
*                     Handles when the UserFile Edit box is chosen.       *
*                OnLoad():                                                *
*                     Handles when the 'Load' Button is pressed.          *
*                OnSingleGo():                                            *
*                     Handles when the 'Go' Button is pressed.            *
*                                                                         *
* Modifications: Matthew Bazar     11-10-99 ALPHA PRESENTATION            *
*                Matthew Bazar     11-30-99 User-Defined Mission          *
*                                           controls added                *
*                Matthew Bazar     12-08-99 Text box is added a scroll    *
*                                           bar and is uneditable         *
**************************************************************************/
#include "stdafx.h"
#include <mmsystem.h>
#include "SetupMenuConfiguration.h"
#include "SetupMenuConfigurationDlg.h"
#include "SinglePlayer.h"
#include "MultiPlayer.h"
#include "SetupGame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SetupGame *setupGame;

/////////////////////////////////////////////////////////////////////////////
// SinglePlayer dialog                                                     //
/////////////////////////////////////////////////////////////////////////////
SinglePlayer::SinglePlayer(CWnd* pParent /*=NULL*/)
	: CDialog(SinglePlayer::IDD, pParent)
{
	mission = 1;
	//{{AFX_DATA_INIT(SinglePlayer)
	m_UserFile = _T("");
	//}}AFX_DATA_INIT
}
void SinglePlayer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SinglePlayer)
	DDX_Control(pDX, IDC_MISSIONCHOICE, m_MissionChoice);
	DDX_Text(pDX, IDC_USERFILE, m_UserFile);
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(SinglePlayer, CDialog)
	//{{AFX_MSG_MAP(SinglePlayer)
	ON_BN_CLICKED(IDSINGLEBACK, OnSinglePlayerBack)
	ON_BN_CLICKED(IDC_MISSION1, OnMission1)
	ON_BN_CLICKED(IDC_MISSION2, OnMission2)
	ON_BN_CLICKED(IDC_MISSION3, OnMission3)
	ON_BN_CLICKED(IDSINGLEGO, OnSingleGo)
	ON_BN_CLICKED(IDC_USERDEFINED, OnUserDefined)
	ON_BN_CLICKED(IDC_LOAD, OnLoad)
	ON_EN_SETFOCUS(IDC_USERFILE, OnSetfocusUserfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL SinglePlayer::OnInitDialog() 
{
	//PlaySound("2r.wav", NULL, SND_ASYNC);
	CDialog::OnInitDialog();
	CheckDlgButton(IDC_MISSION1, 1);	
	fd = open("mission1.txt", O_RDONLY);
	m_MissionChoice.SetReadOnly(true);
	SetDlgItemText(IDC_MISSIONCHOICE, processMissionText(fd));
	userMissionText = "";

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////
// SinglePlayer message handlers                                           //
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
// Helper method that gets the mission text of a file. //
/////////////////////////////////////////////////////////
CString SinglePlayer::processMissionText(int currentMission)
{		
	int bytesRead = read(currentMission, buffer, 3000);
	CString stringBuffer = buffer;
	int startPos = stringBuffer.Find('*');
	startPos ++;
	int endPos = stringBuffer.Find('%');	
	int bytesToRead = endPos - startPos;
	CString myMission = stringBuffer.Mid(startPos, bytesToRead);	
	return myMission;
}
//////////////////////////////////////////////////////////////////////
// Dialog box for SinglePlayer ends and the CSetupMenuConfiguration //
// dialog box is loaded.                                            //
//////////////////////////////////////////////////////////////////////
void SinglePlayer::OnSinglePlayerBack() 
{
	EndDialog(1);
	CSetupMenuConfigurationDlg dlgMultiPlayer;
	dlgMultiPlayer.DoModal();
}
///////////////////////////////////////////////
// Mission one is displayed in the text box. //
///////////////////////////////////////////////
void SinglePlayer::OnMission1() 
{
	//PlaySound("2r.wav", NULL, SND_ASYNC);
	fd = open("mission1.txt", O_RDONLY);
	SetDlgItemText(IDC_MISSIONCHOICE, processMissionText(fd));
	close(fd);
}
///////////////////////////////////////////////
// Mission two is displayed in the text box. //
///////////////////////////////////////////////
void SinglePlayer::OnMission2() 
{
	//PlaySound("MissionImpossible.wav", NULL, SND_ASYNC);
	fd = open("mission2.txt", O_RDONLY);
	SetDlgItemText(IDC_MISSIONCHOICE, processMissionText(fd));
	close(fd);
}
/////////////////////////////////////////////////
// Mission three is displayed in the text box. //
/////////////////////////////////////////////////
void SinglePlayer::OnMission3() 
{
	//PlaySound("Requiem.wav", NULL, SND_ASYNC);
	fd = open("mission3.txt", O_RDONLY);
	SetDlgItemText(IDC_MISSIONCHOICE, processMissionText(fd));
	close(fd);
}
////////////////////////////////////////////////////////////////////////
// When this radio button is chosen, the current user defined mission //
// text is displayed and the focus is set on the edit text box.       //
////////////////////////////////////////////////////////////////////////
void SinglePlayer::OnUserDefined() 
{
	SetDlgItemText(IDC_MISSIONCHOICE, userMissionText);	
	editUserFile().SetFocus();
}
////////////////////////////////////////////////////////////////////////////
// Upon selecting the edit box directly, the radio button for a User      //
// Defined mission is selected, and all the mission radio buttons for the //
// pre-defined missions are unselected.                                   //
////////////////////////////////////////////////////////////////////////////
void SinglePlayer::OnSetfocusUserfile() 
{
	SetDlgItemText(IDC_MISSIONCHOICE, userMissionText);
	CheckDlgButton(IDC_USERDEFINED,1);
	CheckDlgButton(IDC_MISSION1, 0);
	CheckDlgButton(IDC_MISSION2, 0);
	CheckDlgButton(IDC_MISSION3, 0);
}
///////////////////////////////////////////////////////////////////////////
// The current data in the user defined edit text box is updated, and    //
// the file defined is loaded. If successful, the text from that mission //
// is displayed. If unsuccessful, an error message appears and the focus //
// is set on the edit box                                                //
///////////////////////////////////////////////////////////////////////////
void SinglePlayer::OnLoad() 
{
	UpdateData(TRUE);
	fd = open(m_UserFile.GetBuffer(m_UserFile.GetLength ()), O_RDONLY);
	if (fd == -1)
	{
		MessageBeep(MB_ICONASTERISK);
		AfxMessageBox("ERROR: File Not Found.",
			MB_OK | MB_ICONINFORMATION);
		editUserFile().SetFocus();
	}
	else
	{
		userMissionText = processMissionText(fd);
		SetDlgItemText(IDC_MISSIONCHOICE, userMissionText);

		close(fd);
	}
}
//////////////////////////////////////////////////////////////////////////////////
// The go method from the Setup Game class is called to start the Single Player //
// game. Before this is done, however, the file descriptor is checked to make   //
// sure the text file was read correctly. Upon quitting the game, the dialog    //
// box for SinglePlayer ends and CSetupMenuConfiguation dialog box is loaded.   //
//////////////////////////////////////////////////////////////////////////////////
void SinglePlayer::OnSingleGo() 
{	
	if (fd == -1)
	{
		MessageBeep(MB_ICONASTERISK);
		AfxMessageBox("ERROR: No Game Information in File.",
			MB_OK | MB_ICONINFORMATION);
	}
	else
	{
		PlaySound("Shoot.wav", NULL, SND_ASYNC);
		setupGame->singlePlayer(buffer);
		EndDialog(1);
		CSetupMenuConfigurationDlg dlgSetupMenuConfiguration;
		dlgSetupMenuConfiguration.DoModal();
	}
}
