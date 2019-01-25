#include "pch.h"
#include "Spring.h"


Spring::Spring()
{
}

Spring::Spring(Mass * startMass, Mass * endMass, float K, float length, float frictionConst)
{
	this->startMass = startMass;
	this->endMass = endMass;

	this->K = K;
	this->length = length;
	this->frictionConst = frictionConst;
}


Spring::~Spring()
{
}

void Spring::execute()
{
	glm::vec3 springVec = startMass->getPos() - endMass->getPos();
	float len = glm::length(springVec);

	glm::vec3 force(0);
	if (0 != len)
	{
		force += (springVec / len) * (len - length) * (-K);
	}
	force += -(startMass->getVel() - endMass->getVel()) * frictionConst;

	startMass->applyForce(force);
	endMass->applyForce(force);
}
