#include "ProperDivisorManager.h"

ProperDivisorManager* ProperDivisorManager::mInstance = nullptr;

void ProperDivisorManager::Setup(size_t until)
{
	// 約数を求める関係上、2からスタート
	for (size_t i = 2; i <= until; ++i)
	{
		// 既に真の約数データがある場合スキップ
		if (mProperDivisorMap.find(i) != mProperDivisorMap.end())
		{
			continue;
		}

		// 真の約数のデータを設定
		bool makeSetFlg = false;
		for (size_t divisorCandidate = i - 1; divisorCandidate >= 2; --divisorCandidate)
		{
			if (i % divisorCandidate == 0)
			{
				makeSetFlg = true;

				auto divisorList = mProperDivisorMap.find(divisorCandidate);
				if (divisorList != mProperDivisorMap.end())
				{
					// 既に約数候補の約数を算出している場合、それに約数候補自体を追加したものがiの約数である
					mProperDivisorMap[i].insert(divisorList->second.begin(), divisorList->second.end());
				}
				mProperDivisorMap[i].insert(divisorCandidate);

				// 先にヒットしたものの中に含まれない約数を追加する。
				// 例えばi = 6のとき先にヒットするのは3だが、3の約数には2が含まれない。そのため2を追加する必要がある。
				// 追加が必要な数の累乗の値も必要ならここで追加しなければならない。
				auto mapCpy = mProperDivisorMap[i];
				size_t additionalDivisor = (i / divisorCandidate);
				while (i % additionalDivisor == 0 && i != additionalDivisor)
				{
					for (auto originalDivisor : mapCpy)
					{
						auto add = originalDivisor * additionalDivisor;
						if (add < i && i % add == 0)
						{
							mProperDivisorMap[i].insert(add);
						}
					}
					additionalDivisor *= (i / divisorCandidate);
				}
				break;
			}
		}

		// 常に1は含まれる
		if (!makeSetFlg)
		{
			mProperDivisorMap[i].insert(1);
		}
	}
}

const std::unordered_set<size_t>* ProperDivisorManager::GetProperDivisors(size_t num)
{
	if (num < 2) return nullptr;

	auto itr = mProperDivisorMap.find(num);
	if (itr == mProperDivisorMap.end())
	{
		// データがないならそこまでの値をセットアップ
		Setup(num);

		// イテレータ再設定
		itr = mProperDivisorMap.find(num);
		if (itr == mProperDivisorMap.end())
		{
			// 万が一セットアップに失敗してたら諦める
			return nullptr;
		}
	}

	return &(itr->second);
}
