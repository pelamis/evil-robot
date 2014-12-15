#pragma once
#ifndef LINKARRAY_H_
#define LINKARRAY_H_
#include "commons.h"
#include "Link.h"
#include "KPairArray.h"

class LinkArray
{
private:
	Link *array;
	int length;
public:
	LinkArray();
	~LinkArray();
	int getLength();
	void setT0andT1(int linkNumber);
	void buildMeshForAll();
	void drawAll();
};
#endif
