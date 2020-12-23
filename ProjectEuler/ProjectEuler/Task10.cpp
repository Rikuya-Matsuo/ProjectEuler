#include "Task10.h"

Task10::Task10()
{
	mThreads = new std::thread[CheckPrimeTask::mThreadMass];

	mTaskData = new CheckPrimeTask[CheckPrimeTask::mThreadMass];

	for (size_t i = 0; i < CheckPrimeTask::mThreadMass; ++i)
	{
		std::thread th(CheckPrimeTask::Func, std::ref(mTaskData[i]), 2 + i, CheckPrimeTask::mThreadMass, mBelow);

		mThreads[i].swap(th);
	}
}

Task10::~Task10()
{
	delete[] mThreads;
	delete[] mTaskData;
}

void Task10::Run()
{
	// 全スレッドの処理が終わるまで待つ
	size_t taskFinCnt = 0;
	while (taskFinCnt != CheckPrimeTask::mThreadMass)
	{
		taskFinCnt = 0;

		for (size_t i = 0; i < CheckPrimeTask::mThreadMass; ++i)
		{
			taskFinCnt += mTaskData[i].mFinishFlag;
		}
	}

	for (size_t i = 0; i < CheckPrimeTask::mThreadMass; ++i)
	{
		mThreads[i].join();
	}

	// タスクデータに記録された素数を合算していく
	size_t cnt = 0;
	for (size_t i = 0; i < CheckPrimeTask::mThreadMass; ++i)
	{
		for (auto elem : mTaskData[i].mPrimes)
		{
			cnt += elem;
		}
	}


	std::cout << cnt << std::endl;
}

bool Task10::IsPrimeNumber(size_t num)
{
	// xが素数である条件は、「2～(x - 1)の間に割り切れる数がないこと」
	for (size_t i = 2; i < num; ++i)
	{
		if (!(num % i))
		{
			return false;
		}
	}

	return true;
}

std::mutex Task10::CheckPrimeTask::mIOMutex;

const size_t Task10::CheckPrimeTask::mThreadMass = std::thread::hardware_concurrency();

Task10::CheckPrimeTask::CheckPrimeTask():
	mFinishFlag(false)
{

}

void Task10::CheckPrimeTask::Func(CheckPrimeTask& ins, size_t start, size_t interval, size_t below)
{
	size_t num = start;

	for (; num < below; num += interval)
	{
		{
			std::lock_guard<std::mutex> lock(mIOMutex);

			std::cout << "Checking\t" << num << std::endl;
		}

		if (Task10::IsPrimeNumber(num))
		{
			ins.mPrimes.emplace_back(num);
		}
	}

	ins.mFinishFlag = true;
}
