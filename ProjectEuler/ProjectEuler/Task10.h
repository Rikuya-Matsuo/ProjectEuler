#pragma once
#include "TaskBase.h"
class Task10 :
	public TaskBase
{
public:
	Task10();
	~Task10();

	void Run() override;

private:
	bool IsPrimeNumber(size_t num);
};

