# Microsoft Developer Studio Project File - Name="KeckWars" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=KeckWars - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "KeckWars.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "KeckWars.mak" CFG="KeckWars - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "KeckWars - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "KeckWars - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/KeckWarsUpdated", VCAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "KeckWars - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "KeckWars - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W2 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opengl32.lib glut32.lib glu32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "KeckWars - Win32 Release"
# Name "KeckWars - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChildView.cpp
# End Source File
# Begin Source File

SOURCE=.\Client.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientServer.cpp
# End Source File
# Begin Source File

SOURCE=.\ComputerPilot.cpp
# End Source File
# Begin Source File

SOURCE=.\Exit.cpp
# End Source File
# Begin Source File

SOURCE=.\FlightGraphics.cpp
# End Source File
# Begin Source File

SOURCE=.\GameControl.cpp
# End Source File
# Begin Source File

SOURCE=.\GameEndManager.cpp
# End Source File
# Begin Source File

SOURCE=.\Intro2.cpp
# End Source File
# Begin Source File

SOURCE=.\Intro3.cpp
# End Source File
# Begin Source File

SOURCE=.\KeckWars.rc
# End Source File
# Begin Source File

SOURCE=.\MultiPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\NetworkClient.cpp
# End Source File
# Begin Source File

SOURCE=.\NetworkServer.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerReadyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SetupGame.cpp
# End Source File
# Begin Source File

SOURCE=.\SetupMenuConfiguration.cpp
# End Source File
# Begin Source File

SOURCE=.\SetupMenuConfigurationDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ShipInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\SinglePlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\SoundPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\StartGame.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AccumulationCondition.h
# End Source File
# Begin Source File

SOURCE=.\CameraShip.h
# End Source File
# Begin Source File

SOURCE=.\cargoship.h
# End Source File
# Begin Source File

SOURCE=.\ChildView.h
# End Source File
# Begin Source File

SOURCE=.\Client.h
# End Source File
# Begin Source File

SOURCE=.\ComputerPilot.h
# End Source File
# Begin Source File

SOURCE=.\Condition.h
# End Source File
# Begin Source File

SOURCE=.\Conversion.h
# End Source File
# Begin Source File

SOURCE=.\DepreciationCondition.h
# End Source File
# Begin Source File

SOURCE=.\ee1.h
# End Source File
# Begin Source File

SOURCE=.\ee2.h
# End Source File
# Begin Source File

SOURCE=.\ee3.h
# End Source File
# Begin Source File

SOURCE=.\EquivalenceBoolean.h
# End Source File
# Begin Source File

SOURCE=.\EquivalenceCondition.h
# End Source File
# Begin Source File

SOURCE=.\Exit.h
# End Source File
# Begin Source File

SOURCE=.\FlightGraphics.h
# End Source File
# Begin Source File

SOURCE=.\GameControl.h
# End Source File
# Begin Source File

SOURCE=.\GameEndManager.h
# End Source File
# Begin Source File

SOURCE=.\GameState.h
# End Source File
# Begin Source File

SOURCE=.\GameStateDestination.h
# End Source File
# Begin Source File

SOURCE=.\GEOMETRY.H
# End Source File
# Begin Source File

SOURCE=.\glut.h
# End Source File
# Begin Source File

SOURCE=.\Intro2.h
# End Source File
# Begin Source File

SOURCE=.\Intro3.h
# End Source File
# Begin Source File

SOURCE=.\keckstation.h
# End Source File
# Begin Source File

SOURCE=.\keckwing.h
# End Source File
# Begin Source File

SOURCE=.\MultiPlayer.h
# End Source File
# Begin Source File

SOURCE=.\NetworkClient.h
# End Source File
# Begin Source File

SOURCE=.\NetworkServer.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ServerReadyDlg.h
# End Source File
# Begin Source File

SOURCE=.\SetupGame.h
# End Source File
# Begin Source File

SOURCE=.\SetupMenuConfiguration.h
# End Source File
# Begin Source File

SOURCE=.\SetupMenuConfigurationDlg.h
# End Source File
# Begin Source File

SOURCE=.\ShipInterface.h
# End Source File
# Begin Source File

SOURCE=.\ShipState.h
# End Source File
# Begin Source File

SOURCE=.\SinglePlayer.h
# End Source File
# Begin Source File

SOURCE=.\SoundPlayer.h
# End Source File
# Begin Source File

SOURCE=.\StartGame.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ExitScreen.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\KeckWars.ico
# End Source File
# Begin Source File

SOURCE=.\res\KeckWars.rc2
# End Source File
# Begin Source File

SOURCE=.\res\KickAss.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MultiScreen.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ServerScreen.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SetupMenuConfiguration.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SinglePlayerScreen.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Start1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Start2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\ClientScreen.bmp
# End Source File
# End Target
# End Project
