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

	// �����鐔
	size_t dividedNum = 0;

	// �]�肪���������t���O
	bool remainderFlag;

	do
	{
		++dividedNum;

		// ���鐔�B1�łȂ��Ɋ���؂�邽��2����X�^�[�g
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
