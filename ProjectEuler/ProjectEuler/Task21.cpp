#include "Task21.h"
#include "ProperDivisorManager.h"

const size_t Task21::mLimit = 10000;

Task21::Task21()
{
	ProperDivisorManager::GetInstance()->Setup(mLimit - 1);
}

Task21::~Task21()
{
}

void Task21::Run()
{
	size_t ans = CalcAnswer();

	COUT_ANSWER(ans);
}

size_t Task21::CalcAnswer()
{
	// 友愛数である組み合わせを全て求める
	using AmicableNumPair = std::pair<size_t, size_t>;
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
	for (size_t i = 2; i < mLimit; ++i)
	{
		const auto num = i;
		const auto sumPrDiv = CalcSumOfProperDivisor(num);

		if (num != sumPrDiv && CalcSumOfProperDivisor(sumPrDiv) == num)
		{
			// numとsumPrDivは友愛数である
			// 同じ組み合わせが2回登録されてしまうため、numの方が小さい時だけ処理
			if (num < sumPrDiv)
			{
				// ログ出力
				sprintf_s(buf, "(%zu, %zu)", num, sumPrDiv);
				STD_COUT("Amicable Num : ", buf);

				// コンテナ追加
				amicableNums.insert(std::make_pair(num, sumPrDiv));
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

size_t Task21::CalcSumOfProperDivisor(size_t num)
{
	auto pd = ProperDivisorManager::GetInstance()->GetProperDivisors(num);
	return (pd) ? CalcSumOfProperDivisor(*pd) : 0;
}

size_t Task21::CalcSumOfProperDivisor(const std::unordered_set<size_t>& properDivisors)
{
	size_t sum = 0;
	for (auto divisor : properDivisors)
	{
		sum += divisor;
	}
	return sum;
}
