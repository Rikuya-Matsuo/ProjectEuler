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

	// “ñæ‚µ‚½‚à‚Ì‚ğ‘«‚·
	int sqrSum = 0;
	for (size_t i = 0; i < till; ++i)
	{
		size_t num = i + 1;

		sqrSum += (int)pow(num, 2);
	}


	// ‘«‚µ‚½‚à‚Ì‚ğ“ñæ‚·‚é
	int sumSqr = 0;
	for (size_t i = 0; i < till; ++i)
	{
		size_t num = i + 1;
		sumSqr += (int)num;
	}
	sumSqr = (int)pow(sumSqr, 2);

	std::cout << abs(sqrSum - sumSqr) << std::endl;
}
