#include "pch.h"
#include "SpringMassSimulator.h"


SpringMassSimulator::SpringMassSimulator()
{
}


SpringMassSimulator::~SpringMassSimulator()
{
}

SpringMassSimulator::SpringMassSimulator(int numOfMasses, float m, float K, float springLength, float sparingFrictionConst, glm::vec3 g, float airFrictionConst, float groundRepulsionConst, float groubdFrictionConst, float groundAbsorptionConst, float groundHeight)
{
	this->numOfMasses = numOfMasses;
	this->g = g;
	this->airFrictionConst = airFrictionConst;
	this->groubdFrictionConst = groubdFrictionConst;
	this->groundRepulsionConst = groundRepulsionConst;
	this->groundAbsorptionConst = groundAbsorptionConst;
	this->groundHeight = groundHeight;

	this->masses = new Mass*[numOfMasses];

	for (size_t i = 0; i < numOfMasses; i++)
	{
		masses[i] = new Mass(m);
		masses[i]->init();
	}

	//������������ģ�ͣ�����ģ�Ͳ�ͬ���Ը���
	for (size_t i = 0; i < numOfMasses; i++)
	{
		masses[i]->setPos(glm::vec3(i * springLength, 0, 0));
	}

	springs = new Spring*[numOfMasses - 1];
	for (size_t i = 0; i < numOfMasses - 1; ++i)
	{
		//�����ﹹ�����ɣ������Դ���������ͬ��ģ�ͣ������������ͬ�ĸ���
		springs[i] = new Spring(masses[i], masses[i + 1], K, springLength, sparingFrictionConst);
	}
}

void SpringMassSimulator::release()
{
	for (size_t i = 0; i < numOfMasses; ++i)
	{
		delete(masses[i]);
		masses[i] = nullptr;
	}
	delete(masses);
	masses = nullptr;

	for (size_t i = 0; i < numOfMasses - 1; i++)
	{
		delete(springs[i]);
		springs[i] = nullptr;
	}
	springs = nullptr;
}

void SpringMassSimulator::simulate(float dt)
{
	//������ģ�⺯�������Ը����Զ����ģ�����Զ���ģ��ķ���
	for (size_t i = 0; i < numOfMasses; i++)
	{
		masses[i]->execute(dt);
	}

	modelConnectionPos = modelConnectionVel * dt;

	if (modelConnectionPos.y < groundHeight)
	{
		modelConnectionPos.y = groundHeight;
		modelConnectionVel.y = 0;
	}

	masses[0]->setPos(modelConnectionPos);
	masses[0]->setVel(modelConnectionVel);
}

void SpringMassSimulator::setModelConst(glm::vec3 p)
{
	this->modelConnectionPos = p;
}

void SpringMassSimulator::setModelConnectionVel(glm::vec3 v)
{
	this->modelConnectionVel = v;
}

float SpringMassSimulator::getGroundHeight()
{
	return this->groundHeight;
}

int SpringMassSimulator::getNumOfMass()
{
	return this->numOfMasses;
}

Mass * SpringMassSimulator::getMass(int index)
{
	if(index < 0 || index >= numOfMasses)
		return nullptr;
	return masses[index];
}

void SpringMassSimulator::operate(float dt)
{
	std::cout << "ʱ��" << dt << ":" << std::endl;
	this->resetMassesForce();
	this->execute();
	this->simulate(dt);
}

void SpringMassSimulator::execute()
{
	//�����Ƕ�ģ��ϵ�Ĵ���
	for (size_t i = 0; i < numOfMasses - 1; ++i)
	{
		springs[i]->execute();
	}

	for (size_t i = 0; i < numOfMasses; ++i)
	{
		masses[i]->applyForce(g * masses[i]->getMass());
		masses[i]->applyForce(-masses[i]->getVel() * airFrictionConst);

		if (masses[i]->getPos().y < groundHeight)
		{
			glm::vec3 v;
			v = masses[i]->getVel();
			v.y = 0;

			//����y������ٶȣ�ʹ��Ħ����������������Ч����������ϵͳ�е�ƽ��ƽ��
			masses[i]->applyForce(-v * groubdFrictionConst);
			v = masses[i]->getVel();
			v.x = 0;
			v.z = 0;

			//���ϣ��õ�һ����ֱ�ڵ�����ٶȣ�������ٶ������������ģ�͵�����
			if (v.y < 0)
				masses[i]->applyForce(-v * groundAbsorptionConst);

			//ͬʱ������Ҳ���������������ײ�������ʵ�
			glm::vec3 force = glm::vec3(0, groundRepulsionConst, 0) //���淨����
				* (groundHeight - masses[i]->getPos().y);
			masses[i]->applyForce(force);

		}
		
	}
}

void SpringMassSimulator::resetMassesForce()
{
	for (size_t i = 0; i < numOfMasses; i++)
	{
		masses[i]->init();
	}
}
