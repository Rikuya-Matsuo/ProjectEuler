#include "Task22.h"
#include <algorithm>

Task22::Task22() :
	mLetterOrder("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
{
	for (uint32 i = 0; mLetterOrder[i] != '\0'; ++i)
	{
		mLetterScore[mLetterOrder[i]] = i + 1;
	}

	// 「名前の数は5000を超える」と問題文にあるので、5000台の最大値分メモリを確保しておく
	mNameList.reserve(5999);
}

Task22::~Task22()
{
}

void Task22::Run()
{
	LoadNameList();

	size_t ans = CalcSumScore();

	COUT_ANSWER(ans);
}

void Task22::LoadNameList()
{
	mNameList.clear();

	// ロード
	std::ifstream ifs("task22data.txt");
	if (ifs.fail())
	{
		return;
	}

	std::string buf;

	// eof()の仕様の関係で、文字はループ処理の最後で取得するようにする
	char c = ifs.get();
	while (!ifs.eof())
	{
		switch (c)
		{
		case '\"':
			// この文字は無視する
			break;

		case ',':
			// 名前を登録し、次の名前を読み始める
			mNameList.emplace_back(buf);
			buf.clear();
			break;

		default:
			buf += c;
			break;
		}

		c = ifs.get();
	}

	ifs.close();

	// 最後に読みこんだ名前を登録する
	if (!buf.empty())
	{
		mNameList.emplace_back(buf);
	}

	// アルファベット順にソート
	auto sortRule = [this](const std::string& lhs, const std::string& rhs)
	{
		uint32 i;
		for (i = 0; (i < lhs.size() && i < rhs.size()); ++i)
		{
			if (lhs[i] == rhs[i]) continue;

			return mLetterScore[lhs[i]] < mLetterScore[rhs[i]];
		}

		return (i == lhs.size());
	};
	std::sort(mNameList.begin(), mNameList.end(), sortRule);
}

size_t Task22::CalcSumScore() const
{
	size_t sum = 0;
	for (uint32 i = 0; i < mNameList.size(); ++i)
	{
		auto & name = mNameList[i];
		size_t score = 0;
		for (auto letter : name)
		{
			score += mLetterScore.at(letter);
		}
		score *= (i + 1);

		sum += score;
	}

	return sum;
}
