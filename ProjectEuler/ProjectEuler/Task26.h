#pragma once
#include "TaskBase.h"

class Task26 : public TaskBase
{
public:
	void Run() override;

private:
	struct DivDigitInfo
	{
		uint8 mQuotient;	// 商
		uint32 mRemainder;	// 余り
	};

	struct UnitFraction
	{
		uint32 mNumber;	// 割る数
		sint32 mCycleStartIndex;
		sint32 mCycleEndIndex;
		std::vector<DivDigitInfo> mFractionPart;
	};

	std::unordered_map<uint32, UnitFraction> mUnitFractions;
};

