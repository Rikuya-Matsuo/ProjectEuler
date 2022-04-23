#include "Task21.h"

Task21::Task21()
{
	const NumType num = 10000;
	SetupProperDivisor(num);
}

Task21::~Task21()
{
}

void Task21::Run()
{
	size_t ans = CalcAnswer();

	COUT_ANSWER(ans);
}

void Task21::SetupProperDivisor(NumType limit)
{
	// 約数を求める関係上、2からスタート
	for (NumType i = 2; i < limit; ++i)
	{
		bool makeSetFlg = false;
		for (NumType divisorCandidate = i - 1; divisorCandidate >= 2; --divisorCandidate)
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
				NumType additionalDivisor = (i / divisorCandidate);
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

		if (!makeSetFlg)
		{
			mProperDivisorMap[i].insert(1);
		}
	}
}

size_t Task21::CalcAnswer()
{
	// 友愛数である組み合わせを全て求める
	using AmicableNumPair = std::pair<NumType, NumType>;
	struct HashFunc
	{
		size_t operator()(const AmicableNumPair& pair) const
		{
			// 友愛数は単純な1対1の関係（他の相手は存在しえない）のため、小さい方の値をハッシュ値として使う
			return (pair.first < pair.second) ? pair.first : pair.second;
		}
	};

	// ログ出力用
	char buf[64];

	std::unordered_set<AmicableNumPair, HashFunc> amicableNums;
	for (const auto& data : mProperDivisorMap)
	{
		const auto num = data.first;
		const auto sumPrDiv = CalcSumOfProperDivisor(data.second);
		const auto sumPrDivNT = (NumType)sumPrDiv;

		if (num != sumPrDivNT && CalcSumOfProperDivisor(sumPrDivNT) == (size_t)num)
		{
			// numとsumPrDivは友愛数である
			// 同じ組み合わせが2回登録されてしまうため、numが小さい時だけ処理
			if (num < sumPrDivNT)
			{
				// ログ出力
				sprintf_s(buf, "(%d, %d)", num, sumPrDivNT);
				STD_COUT("Amicable Num : ", buf);

				// コンテナ追加
				amicableNums.insert(std::make_pair(num, sumPrDivNT));
			}
		}
	}

	// 求めた友愛数の合計を算出する
	size_t sumAmicableNums = 0;
	for (const auto& pair : amicableNums)
	{
		sumAmicableNums += pair.first + pair.second;
	}

	return sumAmicableNums;
}

size_t Task21::CalcSumOfProperDivisor(NumType num)
{
	auto itr = mProperDivisorMap.find(num);
	return (itr != mProperDivisorMap.end()) ? CalcSumOfProperDivisor(itr->second) : 0;
}

size_t Task21::CalcSumOfProperDivisor(const std::unordered_set<NumType>& properDivisors)
{
	size_t sum = 0;
	for (auto divisor : properDivisors)
	{
		sum += divisor;
	}
	return sum;
}
