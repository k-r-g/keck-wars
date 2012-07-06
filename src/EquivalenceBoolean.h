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

#ifndef EQUIVALENCEBOOLEAN_H
#define EQUIVALENCEBOOLEAN_H

#include "Condition.h"

class EquivalenceBoolean: public Condition {
public:

	EquivalenceBoolean(bool *variant ){
		this->variantBool = variant;
		this->metValue = !*variant;
	}

	bool isMet(){
		return (*variantBool == metValue);
	}
};

#endif