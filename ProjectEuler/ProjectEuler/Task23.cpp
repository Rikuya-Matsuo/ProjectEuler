#include "Task23.h"
#include "ProperDivisorManager.h"
#include <thread>
#include <mutex>

const uint32 Task23::mMax = 28123;

namespace
{
	std::mutex listMtx;
	std::mutex cntMtx;
	uint16 threadRunCnt = 0;

	// このスレッドを動かしている間はabundantNumListの参照元に変更を加えないこと
	void ThreadFunc(const std::list<uint32>& abundantNumList, std::list<uint32>::const_iterator itr, std::unordered_set<uint32>& sumListRef)
	{
		// 合計値を一気に算出する
		std::unordered_set<uint32> sums;
		for (auto itr2 = itr; itr2 != abundantNumList.cend(); ++itr2)
		{
			sums.insert(*itr + *itr2);
		}

		{
			// 算出した合計値を参照コンテナに入れる
			std::lock_guard<std::mutex> lg(listMtx);
			std::cout << "Finish Calc Sums : (" << *itr << " + x)\n";
			sumListRef.insert(sums.begin(), sums.end());
		}

		{
			// スレッドの処理が終わったことを通知する
			std::lock_guard<std::mutex> lg(cntMtx);
			--threadRunCnt;
		}
	}
}

Task23::Task23()
{
	ProperDivisorManager::GetInstance()->Setup(mMax);
}

void Task23::Run()
{
	// 問題文提示の上限までの過剰数を列挙する
	std::cout << "*** Process : List up Abundant Numbers\n";
	std::list<uint32> abundantNumList;
	for (uint32 i = 2; i <= mMax; ++i)
	{
		auto pdList = ProperDivisorManager::GetInstance()->GetProperDivisors(i);
		if (!pdList) continue;

		size_t sumOfPd = 0;
		for (auto pd : *pdList)
		{
			sumOfPd += pd;
		}

		if (sumOfPd > i)
		{
			abundantNumList.emplace_back(i);
		}
	}

	// 2つの過剰数を足してできる数を全て求める
	// ここのループが、2時間経っても終わらないほど量が多いため、マルチスレッドを使って高速化する
	std::cout << "*** Process : List up Sums of 2 Abundant Numbers\n";
	std::unordered_set<uint32> abundantNumSumList;
	const auto threadMaxNum = std::thread::hardware_concurrency() - 1;
	bool continueFlg = false;
	for (auto itr = abundantNumList.cbegin(); itr != abundantNumList.cend(); continueFlg ? itr : ++itr)
	{
		continueFlg = false;
		std::lock_guard<std::mutex> lg(cntMtx);
		if (threadRunCnt < threadMaxNum)
		{
			++threadRunCnt;
			std::thread th(ThreadFunc, std::ref(abundantNumList), itr, std::ref(abundantNumSumList));
			th.detach();
		}
		else
		{
			continueFlg = true;
			continue;
		}
	}

	// 全てのスレッドが処理を終えるまで待機
	while (true)
	{
		std::lock_guard<std::mutex> lg(cntMtx);
		if (!threadRunCnt) break;
	}

	// 問題文提示の上限までの数値を走査し、2つの過剰数を足してできる数でない場合、変数に加算
	std::cout << "*** Process : Calculate Answer\n";
	size_t ans = 0;
	for (uint32 i = 1; i <= mMax; ++i)
	{
		if (abundantNumSumList.find(i) == abundantNumSumList.end())
		{
			ans += i;
		}
	}

	COUT_ANSWER(ans);
}
