#include "Task7.h"



Task7::Task7()
{
}


Task7::~Task7()
{
}

void Task7::Run()
{
	const uint16_t targetPrimeNumIndex = 10001;

	uint16_t primeNumCounter = 0;

	// �f�����ǂ������`�F�b�N����ΏۂƂȂ鐔�l
	size_t num = 2;

	while (primeNumCounter != targetPrimeNumIndex)
	{
		primeNumCounter += IsPrimeNumber(num++);
	}
	--num;

	std::cout << targetPrimeNumIndex << "th prime number is " << num << std::endl;
}

bool Task7::IsPrimeNumber(size_t num)
{
	// x���f���ł�������́A�u2�`(x - 1)�̊ԂɊ���؂�鐔���Ȃ����Ɓv
	for (size_t i = 2; i < num; ++i)
	{
		if (!(num % i))
		{
			return false;
		}
	}

	return true;
}
