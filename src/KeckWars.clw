; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=ServerReadyDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "keckwars.h"
LastPage=0

ClassCount=13
Class1=CChildView
Class2=CClient
Class3=MultiPlayer
Class4=Server
Class5=ServerReadyDlg
Class6=CSetupMenuConfigurationApp
Class7=CAboutDlg
Class8=CSetupMenuConfigurationDlg
Class9=SinglePlayer

ResourceCount=14
Resource1=IDD_EXIT
Resource2=IDD_MULTIPLAYER
Resource3=IDD_SERVER
Resource4=IDD_SETUPMENUCONFIGURATION_DIALOG
Resource5=IDD_INTRO2
Resource6=IDD_START
Resource7=IDR_MAINFRAME
Resource8=IDD_SERVERREADY
Resource9=IDD_GOODBYE
Class10=Exit
Resource10=IDD_DIALOG2
Class11=StartGame
Resource11=IDD_SINGLEPLAYER
Resource12=IDD_CLIENT
Resource13=IDD_DIALOG3
Class12=Intro2
Class13=Intro3
Resource14=IDD_INTRO3

[CLS:CChildView]
Type=0
BaseClass=CWnd
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp

[CLS:CClient]
Type=0
BaseClass=CDialog
HeaderFile=Client.h
ImplementationFile=Client.cpp
LastObject=CClient
Filter=D
VirtualFilter=dWC

[CLS:MultiPlayer]
Type=0
BaseClass=CDialog
HeaderFile=MultiPlayer.h
ImplementationFile=MultiPlayer.cpp
LastObject=MultiPlayer

[CLS:Server]
Type=0
BaseClass=CDialog
HeaderFile=Server.h
ImplementationFile=Server.cpp
LastObject=IDC_SERVERSCREENNAME

[CLS:ServerReadyDlg]
Type=0
BaseClass=CDialog
HeaderFile=ServerReadyDlg.h
ImplementationFile=ServerReadyDlg.cpp
LastObject=IDC_P2TYPE
Filter=D
VirtualFilter=dWC

[CLS:CSetupMenuConfigurationApp]
Type=0
BaseClass=CWinApp
HeaderFile=SetupMenuConfiguration.h
ImplementationFile=SetupMenuConfiguration.cpp
LastObject=CSetupMenuConfigurationApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=SetupMenuConfigurationDlg.cpp
ImplementationFile=SetupMenuConfigurationDlg.cpp
LastObject=CAboutDlg

[CLS:CSetupMenuConfigurationDlg]
Type=0
BaseClass=CDialog
HeaderFile=SetupMenuConfigurationDlg.h
ImplementationFile=SetupMenuConfigurationDlg.cpp
LastObject=IDSINGLEPLAYER
Filter=D
VirtualFilter=dWC

[CLS:SinglePlayer]
Type=0
BaseClass=CDialog
HeaderFile=SinglePlayer.h
ImplementationFile=SinglePlayer.cpp
LastObject=IDC_MISSIONCHOICE
Filter=D
VirtualFilter=dWC

[DLG:IDD_CLIENT]
Type=1
Class=CClient
ControlCount=5
Control1=IDCLIENTGO,button,1342242817
Control2=IDC_SCREENNAME,edit,1350631552
Control3=IDC_SERVERNAME,edit,1350631552
Control4=IDCLIENTBACK,button,1342242816
Control5=IDC_STATIC,static,1342177294

[DLG:IDD_MULTIPLAYER]
Type=1
Class=MultiPlayer
ControlCount=4
Control1=IDCLIENT,button,1342242816
Control2=IDSERVER,button,1342242817
Control3=IDC_MULTIBACK,button,1342242816
Control4=IDC_STATIC,static,1342177294

[DLG:IDD_SERVER]
Type=1
Class=Server
ControlCount=5
Control1=IDSERVERGO,button,1342242817
Control2=IDSERVERBACK,button,1342242816
Control3=IDC_STATIC,static,1342177294
Control4=IDC_STATIC,static,1342308352
Control5=IDC_SERVERSCREENNAME,edit,1350631552

[DLG:IDD_SERVERREADY]
Type=1
Class=ServerReadyDlg
ControlCount=27
Control1=IDSERVERREADYGO,button,1342242817
Control2=IDC_P1NAME,edit,1350631552
Control3=IDC_P2TYPE,combobox,1344339971
Control4=IDC_P3TYPE,combobox,1344339971
Control5=IDC_P4TYPE,combobox,1344339971
Control6=IDC_P5TYPE,combobox,1344339971
Control7=IDC_P6TYPE,combobox,1344339971
Control8=IDC_P7TYPE,combobox,1344339971
Control9=IDC_P8TYPE,combobox,1344339971
Control10=IDC_P2NAME,edit,1350631552
Control11=IDC_P3NAME,edit,1350631552
Control12=IDC_P4NAME,edit,1350631552
Control13=IDC_P5NAME,edit,1350631552
Control14=IDC_P6NAME,edit,1350631552
Control15=IDC_P7NAME,edit,1350631552
Control16=IDC_P8NAME,edit,1350631552
Control17=IDSERVERREADYBACK,button,1342242816
Control18=IDC_STATIC,button,1342210055
Control19=IDC_STATIC,button,1342210055
Control20=IDC_STATIC,button,1342210055
Control21=IDC_STATIC,button,1342210055
Control22=IDC_STATIC,button,1342210055
Control23=IDC_STATIC,button,1342210055
Control24=IDC_STATIC,button,1342210055
Control25=IDC_P1TYPE,static,1342308352
Control26=IDC_STATIC,button,1342210055
Control27=IDC_STATIC,static,1342177294

[DLG:IDD_SETUPMENUCONFIGURATION_DIALOG]
Type=1
Class=CSetupMenuConfigurationDlg
ControlCount=4
Control1=IDSINGLEPLAYER,button,1342242816
Control2=IDMULTIPLAYER,button,1342242816
Control3=IDC_EXIT,button,1342242816
Control4=IDC_STATIC,static,1342177294

[DLG:IDD_SINGLEPLAYER]
Type=1
Class=SinglePlayer
ControlCount=11
Control1=IDSINGLEGO,button,1342242817
Control2=IDC_MISSION1,button,1342278921
Control3=IDC_MISSION2,button,1342275593
Control4=IDC_MISSION3,button,1342275593
Control5=IDC_USERDEFINED,button,1342275593
Control6=IDC_LOAD,button,1342242816
Control7=IDSINGLEBACK,button,1342242816
Control8=IDC_USERFILE,edit,1350631552
Control9=IDC_STATIC,button,1342177287
Control10=IDC_MISSIONCHOICE,edit,1352728580
Control11=IDC_STATIC,static,1342177294

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_FILE_PRINT
Command5=ID_APP_ABOUT
CommandCount=5

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_EDIT_UNDO
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_CUT
Command10=ID_EDIT_UNDO
CommandCount=10

[DLG:IDD_GOODBYE]
Type=1
Class=Exit
ControlCount=1
Control1=IDCANCEL,button,1342242816

[CLS:Exit]
Type=0
HeaderFile=Exit.h
ImplementationFile=Exit.cpp
BaseClass=CDialog
Filter=D
LastObject=Exit
VirtualFilter=dWC

[DLG:IDD_EXIT]
Type=1
Class=?
ControlCount=2
Control1=IDC_SKIP,button,1342242816
Control2=IDC_STATIC,static,1342177294

[DLG:IDD_START]
Type=1
Class=StartGame
ControlCount=3
Control1=IDSKIP,button,1342242817
Control2=IDC_STARTNEXT,button,1342242816
Control3=IDC_STATIC,static,1342177294

[CLS:StartGame]
Type=0
HeaderFile=StartGame.h
ImplementationFile=StartGame.cpp
BaseClass=CDialog
Filter=D
LastObject=StartGame
VirtualFilter=dWC

[DLG:IDD_DIALOG2]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342177294

[DLG:IDD_DIALOG3]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342177294

[DLG:IDD_INTRO2]
Type=1
Class=Intro2
ControlCount=2
Control1=IDC_INTRO2NEXT,button,1342242816
Control2=IDC_STATIC,static,1342177294

[DLG:IDD_INTRO3]
Type=1
Class=Intro3
ControlCount=2
Control1=IDC_INTRO3NEXT,button,1342242816
Control2=IDC_STATIC,static,1342177294

[CLS:Intro2]
Type=0
HeaderFile=Intro2.h
ImplementationFile=Intro2.cpp
BaseClass=CDialog
Filter=D
LastObject=Intro2
VirtualFilter=dWC

[CLS:Intro3]
Type=0
HeaderFile=Intro3.h
ImplementationFile=Intro3.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=Intro3

