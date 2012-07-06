/**************************************************************************
*                                                                         *
* Class Name: Condition                                                   *
*                                                                         *
* Author: Brian Birmingham                                                *
*                                                                         *
* Description: This is an abstract class for a condition.  It is made to  *
*              be easy to turn into a list.                               *
*                                                                         *
**************************************************************************/

#ifndef CONDITION_H
#define CONDITION_H

#include <stdlib.h>

class Condition {
public:
	int metValue;
	int *variant;
	bool *variantBool;
	Condition *next;

	virtual bool isMet() = 0;

	Condition(){
		metValue = 0;
		variant = NULL;
		next = NULL;
	}

	bool anyAreMet(){
		if (this->isMet()){
			return true;
		}
		if (next == NULL){
			return false;
		}
		return next->anyAreMet();
	}

	bool areAllMet(){
		if (!this->isMet()){
			return false;
		}
		if (next == NULL){
			return true;
		}
		return next->areAllMet();
	}
};

#endif