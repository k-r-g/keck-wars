/**************************************************************************
*                                                                         *
* Class Name: Condition                                                   *
*                                                                         *
* Author: Brian Birmingham                                                *
*                                                                         *
* Description: This is an class for a particular kind of condition.  It   *
*              extends the abstract class Condition.                      *
*                                                                         *
**************************************************************************/

#ifndef EQUIVALENCECONDITION_H
#define EQUIVALENCECONDITION_H

#include "Condition.h"

class EquivalenceCondition: public Condition {
public:

	EquivalenceCondition(int *variant, int metValue){
		this->variant = variant;
		this->metValue = metValue;
	}

	bool isMet(){
		return (*variant == metValue);
	}
};

#endif