#pragma once
#include "TaskBase.h"

class Task21 : public TaskBase
{
public:
	Task21();
	~Task21();

	void Run() override;

private:
	static const size_t mLimit;

private:
	size_t CalcAnswer();

	size_t CalcSumOfProperDivisor(size_t num);
	size_t CalcSumOfProperDivisor(const std::unordered_set<size_t>& properDivisors);
};
