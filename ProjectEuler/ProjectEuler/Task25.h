#pragma once
#include "TaskBase.h"

class Task25 : public TaskBase
{
public:
	Task25();
	~Task25();

	class LargeInt;

	void Run() override;

private:
	std::unordered_map<uint32, LargeInt> mFibonacciSeq;
};

class Task25::LargeInt
{
public:
	LargeInt(uint32 num = 0)
	{
		*this = num;
	}

	LargeInt operator+(const LargeInt& rhs);
	LargeInt operator+(uint32 rhs)
	{
		LargeInt rhsLI = rhs;
		return (*this + rhsLI);
	}
	LargeInt& operator=(uint32 rhs);

	uint32 getDigitNum() const { return mDigitNum; }

private:
	std::vector<uint32> mUnits;
	uint32 mDigitNum;

private:
	void Update();
};
