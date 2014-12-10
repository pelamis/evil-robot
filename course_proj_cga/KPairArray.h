#pragma once
#ifndef KPAIRARRAY_H_
#define KPAIRARRAY_H_

#include "commons.h"
#include "KinematicPair.h"

class KPairArray
{
	//make the class fields private!
private:
	KinematicPair *array;
	int length;
public:
	KPairArray();
	~KPairArray();
	int getLength();
	KinematicPair & getPair(int pairNumber);
	GLdouble ** getTForPair(int pairNumber);
	void drawPair(int pairNumber);
};

#endif
