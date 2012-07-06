/**************************************************************************
*                                                                         *
* Class Name: GameEndManager                                              *
*                                                                         *
* Author: Brian Birmingham                                                *
*                                                                         *
* Description: This class manages the end of the Game using different     *
*              kinds of conditions.                                       *
*                                                                         *
**************************************************************************/

#ifndef GAMEENDMANAGER_H
#define GAMEENDMANAGER_H

//#include "Stdafx.h"
#include <stdlib.h>
#include "AccumulationCondition.h"
#include "DepreciationCondition.h"
#include "EquivalenceCondition.h"
#include "EquivalenceBoolean.h"

#define RUNNING 0
#define VICTORY 1
#define DEFEAT 2

#define ACCUMULATION 0
#define DEPRECIATION 1
#define EQUIVALENCE 2
#define BOOLEAN 3

class GameEndManager {

public:

	GameEndManager();

	int gameEndingStatus();
	// returns VICTORY if the victory conditions are all met, DEFEAT if the
	// defeat conditions are all met, or RUNNING if neither have been met.

	void addVictoryCondition(int* variant, int metValue, int type);
	void addVictoryCondition(bool* variant);

	void addDefeatCondition(int* variant, int metValue, int type);
	void addDefeatCondition(bool* variant);

private:

	//int numberOfPlayers;

	Condition *victoryConditions;
	Condition *lastVC;

	Condition *defeatConditions;
	Condition *lastDC;
};

#endif