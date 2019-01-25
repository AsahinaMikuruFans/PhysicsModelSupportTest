#pragma once

#ifndef SPRING_H
#define SPRING_H

#include "Mass.h"
#include <iostream>

class Spring
{
public:
	Spring();
	Spring(Mass* startMass, Mass* endMass, float K, float length, float frictionConst);
	~Spring();

	void execute();
private:
	Mass* startMass;
	Mass* endMass;

	float K;
	float length;
	float frictionConst;
};


#endif // !SPRING_H
