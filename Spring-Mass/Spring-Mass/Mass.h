#pragma once

#ifndef MASS_H
#define MASS_H
#include <glm/glm.hpp>
#include <iostream>

class Mass
{
public:
	Mass(float m);
	~Mass();

	void applyForce(glm::vec3 f);//将力附加到该质点上的力
	void init();
	void execute(float dt); //处理实例内属性的变化，dt，变化的时间
	void setPos(glm::vec3 pos);
	void setVel(glm::vec3 vel);//速度

	glm::vec3 getPos();
	glm::vec3 getVel();
	float getMass();

private:
	float mass;
	glm::vec3 pos;
	glm::vec3 vel;
	glm::vec3 force;
};

#endif // !MASS_H
