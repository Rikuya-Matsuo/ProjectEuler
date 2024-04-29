#pragma once
#include <iostream>
#include <list>

class PrimeManager final
{
public:
	static PrimeManager* GetInstance()
	{
		if (!mInstance)
		{
			mInstance = new PrimeManager();
		}

		if (mInstance) return mInstance;

		std::cout << "Fail to get PrimeManager\n";
		return nullptr;
	}

	static void DeleteInstance()
	{
		if (mInstance) delete mInstance;
	}

public:
	void Setup(size_t until);

	bool CheckPrimeNumber(size_t num);

	void GetPrimeList(size_t until, std::list<size_t>& out);

private:
	static PrimeManager* mInstance;

	PrimeManager()
		: mUntil(1)
	{}

private:
	size_t mUntil;
	std::list<size_t> mPrimes;
};
