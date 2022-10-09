#include "Task25.h"

namespace
{
	using LargeInt = Task25::LargeInt;
}

Task25::Task25()
{
}

Task25::~Task25()
{
}

void Task25::Run()
{
	uint32 index = 0;
	do
	{
		++index;
		if (index <= 2)
		{
			mFibonacciSeq[index] = 1;
			continue;
		}

		mFibonacciSeq[index] = mFibonacciSeq[index - 1] + mFibonacciSeq[index - 2];
	} while (mFibonacciSeq[index].getDigitNum() < 1000);

	COUT_ANSWER(index);
}



LargeInt LargeInt::operator+(const LargeInt & rhs)
{
	LargeInt sum;
	sum.mUnits.clear();
	const auto lhsUnitSize = this->mUnits.size();
	const auto rhsUnitSize = rhs.mUnits.size();
	const auto loopNum = (lhsUnitSize > rhsUnitSize ? lhsUnitSize : rhsUnitSize);
	for (size_t i = 0; i < loopNum; ++i)
	{
		const uint32 lhsUnit = (i < lhsUnitSize) ? this->mUnits[i] : 0;
		const uint32 rhsUnit = (i < rhsUnitSize) ? rhs.mUnits[i] : 0;

		sum.mUnits.emplace_back(lhsUnit + rhsUnit);
	}
	sum.Update();
	return sum;
}

LargeInt& LargeInt::operator=(uint32 rhs)
{
	mUnits.clear();
	mUnits.emplace_back(rhs);
	Update();
	return *this;
}

void LargeInt::Update()
{
	uint8 carry = 0;
	for (auto& unit : mUnits)
	{
		unit += carry;
		carry = unit / BILLION;
		unit %= BILLION;
	}
	if (carry) { mUnits.emplace_back(carry); }

	uint8 backUnitDigitNum = 0;
	uint32 backUnitBuf = mUnits.back();
	while (backUnitBuf)
	{
		++backUnitDigitNum;
		backUnitBuf /= 10;
	}

	// ユニット１つが10億未満なので９桁
	mDigitNum = ((uint32)mUnits.size() - 1) * 9 + backUnitDigitNum;
}
