#pragma once
#include "TaskBase.h"
#include <vector>

class Task15 : public TaskBase
{
public:
	Task15();
	~Task15();

	void Run() override;

private:
	void CalcRoute(size_t gridH, size_t gridV);

	using Array = std::vector<size_t>;
	static void SetupArray(Array& arr, size_t num);

	// 約分。不完全だが十分な軽量化が可能。
	static void ReduceFraction(Array& arr1, Array& arr2);

	static size_t MultArray(const Array& arr);
};
