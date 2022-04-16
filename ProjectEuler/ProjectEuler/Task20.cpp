#include "Task20.h"

Task20::Task20()
{
}

Task20::~Task20()
{
}

void Task20::Run()
{
	const uint16 fuctorialTarget = 100;

	LongNum calcResult(1);
	for (uint16 i = 0; i < fuctorialTarget; ++i)
	{
		calcResult *= (i + 1);
	}

	size_t ans = calcResult.CalcDigitSum();

	STD_COUT("Answer : ", ans);
}

Task20::LongNum& Task20::LongNum::operator*=(sint32 x)
{
	for (auto & num : mNumber)
	{
		num *= x;
	}
	Update();

	return *this;
}

size_t Task20::LongNum::CalcDigitSum() const
{
	size_t ret = 0;
	for (auto num : mNumber)
	{
		while (num > 0)
		{
			ret += num % 10;
			num /= 10;
		}
	}

	return ret;
}

void Task20::LongNum::Update()
{
	static const UnitType unitLim = (UnitType)(pow(10, Task20::LongNum::mDigitOfUnit));

	// 繰り上がり
	UnitType carry = 0;
	for (auto & num : mNumber)
	{
		num += carry;

		carry = num / unitLim;
		num %= unitLim;
	}

	if (carry)
	{
		mNumber.emplace_back(carry);
	}
}
