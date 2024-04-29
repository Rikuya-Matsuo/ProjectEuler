#include "Task27.h"
#include "PrimeManager.h"

Task27::Task27()
{
	// まずn = 0を考えると、係数bが素数である必要がある
	PrimeManager::GetInstance()->Setup(1000);
}

Task27::~Task27()
{
}

void Task27::Run()
{
	auto pm = PrimeManager::GetInstance();
	if (!pm)
	{
		std::cout << "PrimeManager Error";
		return;
	}

	// まずn = 0を考えると、係数bが素数である必要がある
	std::list<size_t> primes;
	pm->GetPrimeList(1000, primes);

	auto maxCombo = 0;
	auto varAOnMax = 0;
	auto varBOnMax = 0;

	for (auto varA = -1000 + 1; varA < 1000; ++varA)
	{
		if (varA % 100 == 0)
		{
			std::cout << "Progress Report\n" << "\tvarA : " << varA << std::endl;
		}

		for (auto varB : primes)
		{
			if (varB % 100 == 0)
			{
				//std::cout << "Progress Report\n" << "\tvarB : " << varB << std::endl;
			}

			auto varN = 0;
			bool breakFlg = false;

			do
			{
				sint32 result = (varN * varN) + (varN * varA) + (sint32)varB;
				if (result > 0 && pm->CheckPrimeNumber(result))
				{
					++varN;
				}
				else
				{
					breakFlg = true;
				}
			} while (!breakFlg);

			if (maxCombo < varN)
			{
				maxCombo = varN;
				varAOnMax = varA;
				varBOnMax = (sint32)varB;

				std::cout << "Max Combo Update\n" << "\tMaxCombo : " << maxCombo << ", varA : " << varA << ", varB : " << varB << std::endl;
			}
		}
	}

	sint32 answer = varAOnMax * varBOnMax;
	COUT_ANSWER(answer);
}
