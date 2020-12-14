#pragma once
#include "TaskBase.h"

class Task7 : public TaskBase
{
public:
	Task7();
	~Task7();

	void Run() override;

private:
	bool IsPrimeNumber(size_t num);
};
