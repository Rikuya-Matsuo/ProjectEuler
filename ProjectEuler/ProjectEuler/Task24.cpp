#include "Task24.h"
#include <thread>
#include <mutex>

namespace
{
	std::mutex cntMutex;
	std::mutex classMutex;
	std::mutex logMutex;
	size_t threadRunCount = 0;
}

Task24::Task24()
{
}

Task24::~Task24()
{
	mPermutations.clear();
	mPermutations.shrink_to_fit();
}

void Task24::Run()
{
	std::string sampleString = "0123456789";
	std::string sampleString2 = "0123";

	makePermutationList(sampleString);

	const size_t ansIndex = MILLION - 1;

	if (mPermutations.size() < ansIndex + 1)
	{
		STD_COUT("Error( PermutationList size shortage ) : ", mPermutations.size());
		return;
	}

	COUT_ANSWER(mPermutations[ansIndex].mStr);
}

void Task24::makePermutationList(const std::string & sampleString)
{
	// 初期化＆メモリ確保
	mPermutations.clear();
	mPermutations.shrink_to_fit();

	size_t combinationNum = calcLetterCombination(sampleString);
	mPermutations.reserve(combinationNum);

	// リスト作成処理
	// マルチスレッドで高速化を図る
	for (size_t loopCnt = 0; loopCnt < sampleString.size(); ++loopCnt)
	{
		std::lock_guard<std::mutex> lg(cntMutex);
		++threadRunCount;

		auto func = std::bind(&Task24::makePermutationListImpl_threadBegin, this, std::ref(sampleString), std::ref(mPermutations), loopCnt);
		std::thread th(func);
		th.detach();
	}

	// 全スレッドが処理を終えるまで待機
	while (true)
	{
		std::lock_guard<std::mutex> lg(cntMutex);
		if (!threadRunCount) break;
	}

	std::sort(mPermutations.begin(), mPermutations.end());
}

void Task24::makePermutationListImpl_threadBegin(const std::string & sampleString, std::vector<PermutationObject> & out, size_t index)
{
	std::list<size_t> indexList;
	indexList.emplace_back(index);

	std::vector<PermutationObject> permutations;
	makePermutationListImpl(sampleString, permutations, indexList);
	
	{
		std::lock_guard<std::mutex> lg(classMutex);
		out.insert(out.end(), permutations.begin(), permutations.end());
	}

	{
		std::lock_guard<std::mutex> lg(cntMutex);
		--threadRunCount;
	}
}

void Task24::makePermutationListImpl(const std::string & sampleString, std::vector<PermutationObject> & out, std::list<size_t> & indexList)
{
	// 呼び出し時点で必要なインデックス配列が揃っていれば順列生成処理
	if (indexList.size() == sampleString.size())
	{
		std::string buf;
		buf.reserve(sampleString.size());
		for (auto index : indexList)
		{
			buf += sampleString[index];
		}

		PermutationObject obj = buf;
		out.emplace_back(obj);

		// 進行状況確認のためログ出力
		std::lock_guard<std::mutex> lg(logMutex);
		STD_COUT("Add Permutation : ", buf);

		return;
	}

	for (size_t i = 0; i < sampleString.size(); ++i)
	{
		// 既に同じインデックスがあれば無効
		if (std::find(indexList.begin(), indexList.end(), i) != indexList.end()) continue;

		indexList.emplace_back(i);
		makePermutationListImpl(sampleString, out, indexList);
		indexList.pop_back();
	}
}

size_t Task24::calcLetterCombination(const std::string & sampleString) const
{
	std::unordered_map<char, uint32> map;
	for (auto & c : sampleString)
	{
		if (map.find(c) == map.end())
		{
			map[c] = 0;
		}
		++map[c];
	}

	size_t ans = 1;
	for (uint32 i = 0; i < sampleString.size(); ++i)
	{
		ans *= (i + 1);
	}

	for (auto & pair : map)
	{
		if (pair.second < 2) continue;

		for (uint32 i = 0; i < pair.second; ++i)
		{
			ans /= (i + 1);
		}
	}

	return ans;
}

Task24::PermutationObject & Task24::PermutationObject::operator=(const std::string & rhs)
{
	auto isNumLetter = [](char c)
	{
		static const std::string nums = "0123456789";
		for (auto cNum : nums)
		{
			if (c == cNum) return true;
		}
		return false;
	};
	auto itr = std::find_if_not(rhs.begin(), rhs.end(), isNumLetter);
	if (itr != rhs.end())
	{
		STD_COUT("Error( Non-Number-Letter included ) : ", rhs);
		return *this;
	}

	mStr = rhs;
	mStr.shrink_to_fit();

	uint32 score = 0;
	for (uint32 i = 0; i < rhs.size() - 1; ++i)	// 変数に入りきらないのでラスト1桁分は省略
	{
		score *= (uint32)rhs.size();

		char rhsC = rhs[i];
		char rhsCStr[] = { rhsC, '\0' };
		score += std::atoi(rhsCStr);
	}
	mScore = score;

	return *this;
}
