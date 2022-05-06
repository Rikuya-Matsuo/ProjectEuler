#pragma once
#include "TaskBase.h"

class Task23 : public TaskBase
{
public:
	Task23();
	~Task23() {}

	void Run() override;

private:
	static const uint32 mMax;
};
