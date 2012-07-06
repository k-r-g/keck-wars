/**************************************************************************
*                                                                         *
* Class:         SoundPlayer                                              *
*                                                                         *
* Author:        Matthew Bazar                                            *
*                                                                         *
* Description:   Interface of the SoundPlayer class.                      *
*                                                                         *
* Modifications: Matthew Bazar     11-10-99 ALPHA PRESENTATION            *
*                                                                         *
**************************************************************************/
#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <windows.h>

#define WEAPONFIRED 1
#define	HULLHIT 2
#define SHIELDHIT 3	

class SoundPlayer {
public:
	void soundEvent(int soundtype);
};

#endif