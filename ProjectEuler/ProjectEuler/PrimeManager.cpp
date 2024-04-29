#include "PrimeManager.h"
PrimeManager* PrimeManager::mInstance = nullptr;

void PrimeManager::Setup(size_t until)
{
	if (until < 2) return;
	if (until < mUntil) return;

	for (size_t i = mUntil + 1; i <= until; ++i)
	{
		// xが素数である条件は、「2～(x - 1)の間に割り切れる数がないこと」
		bool isPrime = true;
		for (size_t j = 2; j < i; ++j)
		{
			if (!(i % j))
			{
				isPrime = false;
				break;
			}
		}

		if (isPrime)
		{
			mPrimes.emplace_back(i);
		}
	}
	mUntil = until;
}

bool PrimeManager::CheckPrimeNumber(size_t num)
{
	// 追加セットアップ
	Setup(num);
	
	// リスト内にあるか
	for (auto prime : mPrimes)
	{
		if (num == prime) return true;

		if (prime > num) break;
	}

	return false;
}

void PrimeManager::GetPrimeList(size_t until, std::list<size_t>& out)
{
	// 追加セットアップ
	Setup(until);

	out.clear();
	for (auto prime : mPrimes)
	{
		if (prime > until) break;
		out.emplace_back(prime);
	}
}
