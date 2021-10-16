#include "Task5.h"

Task5::Task5()
{
}


Task5::~Task5()
{
}

void Task5::Run()
{
	const char divideByMax = 20;

	// 割られる数
	size_t dividedNum = 0;

	// 余りが発生したフラグ
	bool remainderFlag;

	do
	{
		++dividedNum;

		// 割る数。1でなら常に割り切れるため2からスタート
		char divideBy = 2;

		for (; divideBy <= divideByMax; ++divideBy)
		{
			remainderFlag = dividedNum % divideBy;
			if (remainderFlag)
			{
				break;
			}
		}

	} while (remainderFlag);

	std::cout << dividedNum << std::endl;
}
