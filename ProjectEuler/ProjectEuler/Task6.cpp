#include "Task6.h"
#include <cmath>


Task6::Task6()
{
}


Task6::~Task6()
{
}

void Task6::Run()
{
	const size_t till = 100;

	// ��悵�����̂𑫂�
	int sqrSum = 0;
	for (size_t i = 0; i < till; ++i)
	{
		size_t num = i + 1;

		sqrSum += (int)pow(num, 2);
	}


	// ���������̂��悷��
	int sumSqr = 0;
	for (size_t i = 0; i < till; ++i)
	{
		size_t num = i + 1;
		sumSqr += (int)num;
	}
	sumSqr = (int)pow(sumSqr, 2);

	std::cout << abs(sqrSum - sumSqr) << std::endl;
}
