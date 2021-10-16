#include "Task12.h"

Task12::Task12()
{
}


Task12::~Task12()
{
}

void Task12::Run()
{
	size_t lastTriangleNum;
	size_t loopNum = 0;
	size_t divisorMass = 0;

	do
	{
		lastTriangleNum = CalcTriangleNum(++loopNum);

		size_t tmpDvs = CalcDivisorMass(lastTriangleNum);

		if (tmpDvs != divisorMass)
		{
			std::cout << "DvsMass : " << tmpDvs << std::endl;
		}

		divisorMass = tmpDvs;
	} while (divisorMass <= 500u);

	std::cout << std::endl << "Answer : " << lastTriangleNum << std::endl;		// 76576500
}

size_t Task12::CalcDivisorMass(size_t num)
{
	size_t cnt = 0;

	for (size_t i = 0; i < num; ++i)
	{
		cnt += !(num % (i + 1));
	}

	return cnt;
}
