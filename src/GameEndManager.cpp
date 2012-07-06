
#include "Stdafx.h"
#include "GameEndManager.h"

GameEndManager::GameEndManager(){
	victoryConditions = NULL;
	defeatConditions = NULL;
}


int GameEndManager::gameEndingStatus(){
	if (defeatConditions!=NULL && defeatConditions->anyAreMet()){
		return DEFEAT;
	}
	if (victoryConditions!=NULL && victoryConditions->anyAreMet()){
		return VICTORY;
	}
	return RUNNING;
}

void GameEndManager::addVictoryCondition(int *variant, int metValue, 
										 int type){
	if (type == BOOLEAN){
		addVictoryCondition((bool*)variant);
		return;
	}
	if (victoryConditions == NULL){
		switch (type){
		case ACCUMULATION:
			victoryConditions = new AccumulationCondition(variant, 
				metValue);
			break;
		case DEPRECIATION:
			victoryConditions = new DepreciationCondition(variant,
				metValue);
			break;
		case EQUIVALENCE:
			victoryConditions = new EquivalenceCondition(variant,
				metValue);
			break;
		default:
			break;
		}
		lastVC = victoryConditions;
	}
	else{
		switch (type){
		case ACCUMULATION:
			lastVC->next = new AccumulationCondition(variant, 
				metValue);
			break;
		case DEPRECIATION:
			lastVC->next = new DepreciationCondition(variant,
				metValue);
			break;
		case EQUIVALENCE:
			lastVC->next = new EquivalenceCondition(variant,
				metValue);
			break;
		default:
			break;
		}
		lastVC = lastVC->next;
	}
}

void GameEndManager::addDefeatCondition(int *variant, int metValue, 
										 int type){
	if (type == BOOLEAN){
		addDefeatCondition((bool*)variant);
		return;
	}
	if (defeatConditions == NULL){
		switch (type){
		case ACCUMULATION:
			defeatConditions = new AccumulationCondition(variant, 
				metValue);
			break;
		case DEPRECIATION:
			defeatConditions = new DepreciationCondition(variant,
				metValue);
			break;
		case EQUIVALENCE:
			defeatConditions = new EquivalenceCondition(variant,
				metValue);
			break;
		default:
			break;
		}
		lastDC = defeatConditions;
	}
	else{
		switch (type){
		case ACCUMULATION:
			lastDC->next = new AccumulationCondition(variant, 
				metValue);
			break;
		case DEPRECIATION:
			lastDC->next = new DepreciationCondition(variant,
				metValue);
			break;
		case EQUIVALENCE:
			lastDC->next = new EquivalenceCondition(variant,
				metValue);
			break;
		default:
			break;
		}
		lastDC = lastDC->next;
	}
}

void GameEndManager::addVictoryCondition(bool *variant){
	if (victoryConditions == NULL){
		victoryConditions = new EquivalenceBoolean(variant);
		lastVC = victoryConditions;
	}
	else{
		lastVC->next = new EquivalenceBoolean(variant);
		lastVC = lastVC->next;
	}
}

void GameEndManager::addDefeatCondition(bool *variant){
	if (defeatConditions == NULL){
		defeatConditions = new EquivalenceBoolean(variant);
		lastDC = defeatConditions;
	}
	else{
		lastDC->next = new EquivalenceBoolean(variant);
		lastDC = lastDC->next;
	}
}