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

#ifndef ACCUMULATIONCONDITION_H
#define ACCUMULATIONCONDITION_H

#include "Condition.h"

class AccumulationCondition: public Condition {
public:

	AccumulationCondition(int *variant, int metValue){
		this->variant = variant;
		this->metValue = metValue;
	}

	bool isMet(){
		return (*variant >= (metValue));
	}
};

#endif