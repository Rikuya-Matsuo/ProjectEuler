#include "Task10.h"

Task10::Task10()
{
}

Task10::~Task10()
{
}

void Task10::Run()
{
	const size_t below = 2000000;

	size_t cnt = 0;

	// �f���݂̂��`�F�b�N�������̂ŁAi�̏����l��2
	for (size_t i = 2; i < below; ++i)
	{
		std::cout << "Checking\t\t" << i << std::endl;

		cnt += (IsPrimeNumber(i)) ? i : 0;
	}

	std::cout << cnt << std::endl;
}

bool Task10::IsPrimeNumber(size_t num)
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
