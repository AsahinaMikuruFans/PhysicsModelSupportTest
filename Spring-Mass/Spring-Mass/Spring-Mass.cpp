// Spring-Mass.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <math.h>
#include "SpringMassSimulator.h"

namespace springG
{
	constexpr auto normalSpring = 7.9f; //普通弹簧
	constexpr auto stainlessSteelSpring = 7.2f; //不锈钢丝
	constexpr auto siliconBronzeSpring = 4.1f; //硅青铜线
}

/*
 获得弹簧的劲度系数
 G 常量，线材的刚性模数
 d 线径
 D 外径
 N 有效圈数
 */
float getSpringK(float G, float d, float D, int N)
{
	return (G * pow(d, 4)) / (8 * N * pow(D - d, 3));
}

/*
 获取位移量
*/
float getX(float lastx, float F, float k)
{
	return F / k - lastx;
}

int main()
{
	SpringMassSimulator sms(
		10,
		2.0f, 
		0.9f, 2.0f, 0.2f,
		glm::vec3(9.8f), 
		0.2f, 0.2f, 0.2f, 0.2f, 1.0f
	);
	sms.operate(0.1);
	sms.release();
}