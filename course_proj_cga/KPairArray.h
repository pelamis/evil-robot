#pragma once
#ifndef KPAIRARRAY_H_
#define KPAIRARRAY_H_

#include "commons.h"
#include "KinematicPair.h"

class KPairArray
{
private:
	KinematicPair *array;
public:
	KPairArray();
	~KPairArray();
};

#endif
