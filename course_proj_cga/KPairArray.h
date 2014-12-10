#pragma once
#ifndef KPAIRARRAY_H_
#define KPAIRARRAY_H_

#include "commons.h"
#include "KinematicPair.h"

class KPairArray
{
	//make the class fields private!
public:
	KinematicPair *array;
	int length;

	KPairArray();
	~KPairArray();
	int getLength();
	GLdouble ** getTForPair(int pairNumber);
};

#endif
