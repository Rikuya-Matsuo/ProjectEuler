#pragma once
#include "TaskBase.h"

class Task12 : public TaskBase
{
public:
	Task12();
	~Task12();

	void Run() override;

private:
	// i�Ԗڂ̎O�p�������߂�
	// �O�p���̌�����p����
	size_t CalcTriangleNum(size_t i) { return (i * (i + 1)) / 2; }

	// �񐔂̐������߂�
	size_t CalcDivisorMass(size_t num);
};
