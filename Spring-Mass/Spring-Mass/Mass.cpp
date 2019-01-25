#include "pch.h"
#include "Mass.h"

Mass::Mass(float m)
{
	this->mass = m;
}

Mass::~Mass()
{
}

void Mass::applyForce(glm::vec3 f)
{
	this->force += f;
}

void Mass::init()
{
	force.x = 0;
	force.y = 0;
	force.z = 0;
}

void Mass::execute(float dt)
{
	vel += (force / mass) * dt; // a = vt^2;
	pos += vel * dt; //x=vt
}

void Mass::setPos(glm::vec3 pos)
{
	this->pos = pos;
}

void Mass::setVel(glm::vec3 vel)
{
	this->vel = vel;
}

glm::vec3 Mass::getPos()
{
	return this->pos;
}

glm::vec3 Mass::getVel()
{
	return this->vel;
}

float Mass::getMass()
{
	return this->mass;
}
