#pragma once
#include "TaskBase.h"
#include <cmath>

class Task16 : public TaskBase
{
public:
	void Run() override;

private:
	struct BigNum
	{
		static const uint16 mSectionMax;

		std::vector<uint16> mSections;
		bool mMinus;

		BigNum(int n = 0)
		{
			*this = n;
		}

		~BigNum()
		{
			mSections.clear();
			mSections.shrink_to_fit();
		}

		uint32 CalcDigitSum() const;

		void PrintValue() const;

		BigNum & operator=(int n);

		BigNum & operator*=(int n);
	};
};
