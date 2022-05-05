#pragma once
#include <iostream>
#include <unordered_map>
#include <unordered_set>

class ProperDivisorManager final
{
public:
	static ProperDivisorManager* GetInstance()
	{
		if (!mInstance)
		{
			mInstance = new ProperDivisorManager();
		}

		if (mInstance) return mInstance;

		std::cout << "Fail to get ProperDivisorManager\n";
		return nullptr;
	}

	static void DeleteInstance()
	{
		if (mInstance) delete mInstance;
	}

public:
	void Setup(size_t until);

	const std::unordered_set<size_t>* GetProperDivisors(size_t num);

private:
	static ProperDivisorManager* mInstance;

	ProperDivisorManager()
	{}

private:
	using ProperDivisorMap = std::unordered_map<size_t, std::unordered_set<size_t>>;
	ProperDivisorMap mProperDivisorMap;
};
