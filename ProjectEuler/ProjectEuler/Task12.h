#pragma once
#include "TaskBase.h"

class Task12 : public TaskBase
{
public:
	Task12();
	~Task12();

	void Run() override;

private:
	// i番目の三角数を求める
	// 三角数の公式を用いる
	size_t CalcTriangleNum(size_t i) { return (i * (i + 1)) / 2; }

	// 約数の数を求める
	size_t CalcDivisorMass(size_t num);
};
