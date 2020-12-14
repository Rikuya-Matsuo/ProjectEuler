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

	// 素数かどうかをチェックする対象となる数値
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
	// xが素数である条件は、「2～(x - 1)の間に割り切れる数がないこと」
	for (size_t i = 2; i < num; ++i)
	{
		if (!(num % i))
		{
			return false;
		}
	}

	return true;
}
