#pragma once
#include "TaskBase.h"

class Task9 : public TaskBase
{
public:
	Task9();
	~Task9();

	void Run() override;

private:
	bool Check(uint16_t a, uint16_t b, uint16_t c);
};

