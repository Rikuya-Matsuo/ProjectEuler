#pragma once
#include "TaskBase.h"

class Task21 : public TaskBase
{
public:
	Task21();
	~Task21();

	void Run() override;

private:
	using NumType = uint32;
	using ProperDivisorMap = std::unordered_map<NumType, std::unordered_set<NumType>>;
	ProperDivisorMap mProperDivisorMap;

	void SetupProperDivisor(NumType limit);

	size_t CalcAnswer();

	size_t CalcSumOfProperDivisor(NumType num);
	size_t CalcSumOfProperDivisor(const std::unordered_set<NumType>& properDivisors);
};
