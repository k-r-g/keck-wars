/**************************************************************************
*                                                                         *
* Class:         SoundPlayer                                              *
*                                                                         *
* Author:        Matthew Bazar                                            *
*                                                                         *
* Description:   This is a simple class used to play a ".wav" sound file. *
*                                                                         *
* Methods:       soundEvent(int soundtype):                               *
*                     This method is called by the PlayerInterface clsas  *
*                     whenever a sound needs to be played for the user.   *
*                     To simplify what is passed into the method          *
*                     definitions of the various sounds have been coded.  *
*                                                                         *
* Modifications: Matthew Bazar     11-10-99 ALPHA PRESENTATION            *
*				 Matthew Bazar     11-21-99 New sounds added              *
*                                                                         *
**************************************************************************/
#include "StdAfx.h"
#include "SoundPlayer.h"
#include <mmsystem.h>

void SoundPlayer::soundEvent(int soundType)
{
	switch (soundType)
	{
	case WEAPONFIRED:
		PlaySound("Shoot.wav", NULL, SND_ASYNC);
		break;
	case HULLHIT:
		PlaySound("HullHit.wav", NULL, SND_ASYNC);
		break;
	case SHIELDHIT:
		PlaySound("ShieldsBeow.wav", NULL, SND_ASYNC);
		break;
	}
}