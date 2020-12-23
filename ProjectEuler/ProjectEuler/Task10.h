#pragma once
#include "TaskBase.h"
#include <thread>
#include <mutex>
#include <list>

class Task10 : public TaskBase
{
public:
	Task10();
	~Task10();

	void Run() override;

	static bool IsPrimeNumber(size_t num);

private:

	struct CheckPrimeTask
	{
		CheckPrimeTask();

		std::list<size_t> mPrimes;

		bool mFinishFlag;

		static std::mutex mIOMutex;

		static const size_t mThreadMass;

		static void Func(CheckPrimeTask& ins, size_t start, size_t interval, size_t below);
	};

	CheckPrimeTask* mTaskData;

	std::thread * mThreads;

	const size_t mBelow = 2000000;
};
