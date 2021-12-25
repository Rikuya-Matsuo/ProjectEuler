#include "Task16.h"

void Task16::Run()
{
	BigNum num(1);

	const int base = 2;
	const uint32 power = 1000;

	for (uint32 i = 0; i < power; ++i)
	{
		num *= base;
	}

	num.PrintValue();

	uint32 answer = num.CalcDigitSum();
	std::cout << "Answer : " << answer << std::endl;

	return;
}

const uint16 Task16::BigNum::mSectionMax = 10000u;

uint32 Task16::BigNum::CalcDigitSum() const
{
	uint32 sum = 0;

	for (auto sect : mSections)
	{
		while (sect > 0)
		{
			sum += sect % 10;
			sect /= 10;
		}
	}

	return sum;
}

void Task16::BigNum::PrintValue() const
{
	std::string valueStr;
	for (auto sect : mSections)
	{
		valueStr.insert(0, std::to_string(sect));
	}

	std::cout << "Value : " << valueStr << std::endl;
}

Task16::BigNum & Task16::BigNum::operator=(int n)
{
	mMinus = n < 0;

	int absN = abs(n);
	mSections.clear();
	while (absN > 0)
	{
		int sect = absN % mSectionMax;
		mSections.emplace_back(sect);

		absN /= mSectionMax;
	}

	return *this;
}

Task16::BigNum & Task16::BigNum::operator*=(int n)
{
	mMinus = (mMinus != (n < 0));

	uint32 absN = abs(n);

	// 繰り上がり
	uint16 carry = 0;

	for (auto& sect : mSections)
	{
		sect *= absN;
		sect += carry;
		carry = 0;

		if (sect >= mSectionMax)
		{
			carry = sect / mSectionMax;
			sect %= mSectionMax;
		}
	}

	if (carry)
	{
		mSections.emplace_back(carry);
	}

	return *this;
}
