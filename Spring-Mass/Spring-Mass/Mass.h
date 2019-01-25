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

	void applyForce(glm::vec3 f);//�������ӵ����ʵ��ϵ���
	void init();
	void execute(float dt); //����ʵ�������Եı仯��dt���仯��ʱ��
	void setPos(glm::vec3 pos);
	void setVel(glm::vec3 vel);//�ٶ�

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
