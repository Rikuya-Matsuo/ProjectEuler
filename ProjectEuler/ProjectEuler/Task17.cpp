#include "Task17.h"

Task17::Task17() :
	mHundredStr("hundred"),
	mThousandStr("thousand"),
	mMaxNum(1000)
{
	mNumLiteralMap = {
	{1,	"one"},
	{2,	"two"},
	{3,	"three"},
	{4,	"four"},
	{5,	"five"},
	{6,	"six"},
	{7,	"seven"},
	{8,	"eight"},
	{9,	"nine"},
	{10, "ten"},
	{11, "eleven"},
	{12, "twelve"},
	{13, "thirteen"},
	{14, "fourteen"},
	{15, "fifteen"},
	{16, "sixteen"},
	{17, "seventeen"},
	{18, "eighteen"},
	{19, "nineteen"},
	{20, "twenty"},
	{30, "thirty"},
	{40, "forty"},
	{50, "fifty"},
	{60, "sixty"},
	{70, "seventy"},
	{80, "eighty"},
	{90, "ninety"}
	};
}

Task17::~Task17()
{
	mNumLiteralMap.clear();
}

void Task17::Run()
{
	std::string str;
	size_t answer = 0;
	for (uint16 i = 1; i < 1000 + 1; ++i)
	{
		MakeLiteral(i, str);
		size_t letterCnt = CountLetter(str.c_str());

		std::cout << i << "\t" << str << " : " << letterCnt << std::endl;

		answer += letterCnt;
	}

	std::cout << "\nAnswer : " << answer << std::endl;
}

void Task17::MakeLiteral(numType num, std::string & out)
{
	out.clear();
	// 現状1000以下まで対応
	if (num > mMaxNum)
	{
		return;
	}

	auto addStr = [&out](const std::string& str)
	{
		if (!out.empty())
		{
			out += ' ';
		}
		out += str;
	};

	const auto mapEnd = mNumLiteralMap.end();

	bool over100 = false;
	if (num >= 1000)
	{
		numType thousandDigit = num / 1000;
		auto itr = mNumLiteralMap.find(thousandDigit);
		if (itr != mapEnd)
		{
			addStr(itr->second + ' ' + mThousandStr);
			num %= 1000;
			over100 = true;
		}
	}

	if (num >= 100 && num < 1000)
	{
		numType hundredDigit = num / 100;
		auto itr = mNumLiteralMap.find(hundredDigit);
		if (itr != mapEnd)
		{
			addStr(itr->second + ' ' + mHundredStr);
			num %= 100;
			over100 = true;
		}
	}

	auto itr = mNumLiteralMap.find(num);
	std::string str;
	// マップにデータのある数値だった場合
	if (itr != mapEnd)
	{
		if (over100) { str += "and "; }
		str += itr->second;
		addStr(str);
	}
	// マップにデータのない数値だった場合
	// データのある値から合成する
	else
	{
		numType oneDigit = num % 10;

		auto tenItr = mNumLiteralMap.find(num - oneDigit);
		auto oneItr = mNumLiteralMap.find(oneDigit);
		if (tenItr != mapEnd && oneItr != mapEnd)
		{
			if (over100) { str += "and "; }
			str += tenItr->second + '-' + oneItr->second;

			addStr(str);
		}
	}
}

size_t Task17::CountLetter(const char * str)
{
	size_t cnt = 0;
	const char * ptr = str;
	while (*ptr != '\0')
	{
		cnt += (*ptr != ' ' && *ptr != '-') ? 1 : 0;
		++ptr;
	}
	return cnt;
}
