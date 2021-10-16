#pragma once
#include "TaskBase.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>

class Task13 : public TaskBase
{
public:
	Task13();
	~Task13();

	void Run() override;

public:
	// 10桁の数字は32ビットの変数には収めることが必ずしも可能ではないため、
	// ある程度の桁数に分けて数値を保存する構造体を作る
	template <uint32_t digitNum>
	struct LongDigitNumber;

private:
	static const uint32_t sDigitUnit = 9u;
	using LongDigitNumber_t = LongDigitNumber<sDigitUnit>;

	static const char * sNumberStr;

	std::vector<LongDigitNumber_t *> mNumbers;

private:
	// mNumberStrから各行の数字を読み込む
	void SeqLoad();

	template<uint32_t digitUnit>
	void SeqCalc(LongDigitNumber<digitUnit> & out);
};

// 10の累乗のファンクタであり、指数ごとの結果のコレクションでもある
class SectionLimitDict
{
public:
	size_t operator[](uint32_t digitNum)
	{
		size_t ret = 0;

		auto itr = mPowDict.find(digitNum);
		if (itr != mPowDict.end())
		{
			ret = itr->second;
		}
		else
		{
			ret = static_cast<size_t>(pow(10, digitNum));
			mPowDict[digitNum] = ret;
		}

		return ret;
	}

private:
	static std::unordered_map<uint32_t, size_t> mPowDict;
};

// 負の値での計算は未対応
template <uint32_t digitNum>
struct Task13::LongDigitNumber
{
	const size_t mSectionLimit;

	std::vector<size_t> mSections;

	bool mMinus;

	LongDigitNumber()
		: mMinus(false)
		, mSectionLimit(SectionLimitDict()[digitNum])
	{}

	LongDigitNumber(const std::string & numStr)
		: LongDigitNumber()
	{
		*this = numStr;
	}

	LongDigitNumber(const char * numStr)
		: LongDigitNumber()
	{
		std::string str = numStr;
		*this = str;
	}

	~LongDigitNumber()
	{
		mSections.clear();
	}

	void ToString(std::string & out);

	LongDigitNumber & operator=(const std::string & numStr);
	LongDigitNumber & operator=(const LongDigitNumber & rhs);
};

#define TSK13_LDN_FUNC_DEF(retType, funcName) \
template<uint32_t digitNum>\
retType Task13::LongDigitNumber<digitNum>::##funcName

TSK13_LDN_FUNC_DEF(void, ToString)(std::string & out)
{
	if (mMinus)
	{
		out += '-';
	}

	for (auto itr = mSections.rbegin(); itr != mSections.rend(); ++itr)
	{
		std::string str = std::to_string(*itr);

		const size_t size = str.size();
		if (size < digitNum && itr != mSections.rbegin())
		{
			size_t digitDiff = digitNum - size;
			std::string zeroPad;
			for (size_t i = 0; i < digitDiff; ++i)
			{
				zeroPad += '0';
			}

			str = zeroPad + str;
		}

		out += str;
	}
}

TSK13_LDN_FUNC_DEF(Task13::LongDigitNumber<digitNum> &, operator=)(const std::string & numStr)
{
	mMinus = (numStr[0] == '-');
	mSections.clear();
	size_t reserveNum = (numStr.size() / digitNum) + (size_t)(numStr.size() % digitNum > 0);
	mSections.reserve(reserveNum);

	char buf[digitNum + 1];
	memset(buf, ' ', sizeof(buf) - 1);
	buf[digitNum] = '\0';
	int cnt = 0;

	auto itr = numStr.rbegin();
	while (itr != numStr.rend())
	{
		if (*itr != '-')
		{
			buf[digitNum - (cnt + 1)] = *itr;

			if (++cnt == digitNum)
			{
				cnt = 0;

				mSections.emplace_back(atoi(buf));

				memset(buf, ' ', sizeof(buf) - 1);
			}
		}

		++itr;
	}

	if (cnt)
	{
		mSections.emplace_back(atoi(buf));
	}

	return *this;
}

TSK13_LDN_FUNC_DEF(Task13::LongDigitNumber<digitNum> &, operator=)(const Task13::LongDigitNumber<digitNum> & rhs)
{
	mMinus = rhs.mMinus;
	
	mSections.clear();
	mSections.reserve(rhs.mSections.size());
	for (auto itr : rhs.mSections)
	{
		mSections.emplace_back(itr);
	}

	return *this;
}

template <uint32_t digitNum>
Task13::LongDigitNumber<digitNum> operator+(const Task13::LongDigitNumber<digitNum> & lhs, const Task13::LongDigitNumber<digitNum> & rhs)
{
	Task13::LongDigitNumber<digitNum> ret;

	size_t lhsSize = lhs.mSections.size();
	size_t rhsSize = rhs.mSections.size();

	size_t cnt = 0;
	size_t carry = 0;
	do
	{
		size_t section = carry;
		
		if (cnt < lhsSize)
		{
			section += lhs.mSections[cnt];
		}
		if (cnt < rhsSize)
		{
			section += rhs.mSections[cnt];
		}

		carry = section / ret.mSectionLimit;
		section %= ret.mSectionLimit;

		if (section)
		{
			ret.mSections.emplace_back(section);
		}

		++cnt;

	} while (cnt < lhsSize || cnt < rhsSize);

	if (carry)
	{
		ret.mSections.emplace_back(carry);
	}

	return ret;
}
