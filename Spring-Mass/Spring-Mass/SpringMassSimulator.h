#pragma once

#ifndef SPRINGMASSSIMULATOR
#define SPRINGMASSSIMULATOR

#include "Mass.h"
#include "Spring.h"
#include <glm/glm.hpp>

class SpringMassSimulator
{
public:
	SpringMassSimulator();
	~SpringMassSimulator();
	SpringMassSimulator(
		int numOfMasses,
		float m,
		float K,
		float springLength,
		float sparingFrictionConst,
		glm::vec3 g,
		float airFrictionConst,
		float groundRepulsionConst, //平面斥力
		float groubdFrictionConst, //平面摩擦力
		float groundAbsorptionConst, //平面的引力
		float groundHeight
	);
	
	void release();
	void simulate(float dt);
	void setModelConst(glm::vec3 p);
	void setModelConnectionVel(glm::vec3 v);
	float getGroundHeight();
	int getNumOfMass();
	Mass* getMass(int index);
	void operate(float dt);
	void execute();
	void resetMassesForce();

	Spring** springs;
	glm::vec3 modelConnectionPos;
	glm::vec3 modelConnectionVel;

private:
	int numOfMasses;
	glm::vec3 g;
	float airFrictionConst;
	float groundRepulsionConst;
	float groubdFrictionConst;
	float groundAbsorptionConst;
	float groundHeight;
	Mass** masses;
};

#endif // !SPRINGMASSSIMULATOR

