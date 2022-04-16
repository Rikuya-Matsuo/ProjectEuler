#pragma once
#include "TaskBase.h"

class Task20 : public TaskBase
{
public:
	Task20();
	~Task20();

	void Run() override;

private:
	class LongNum;
};

class Task20::LongNum
{
public:
	using UnitType = sint32;
	LongNum(UnitType initNum) { *this =initNum; }

	LongNum& operator=(UnitType num)
	{
		mNumber.clear();
		mNumber.emplace_back(num);
		return *this;
	}
	LongNum& operator*=(sint32 x);

	size_t CalcDigitSum() const;

private:
	static const uint8 mDigitOfUnit = 6;

	std::list<UnitType> mNumber;

	void Update();
};
