#pragma once
#include <cstdint>
#include "TaskBase.h"

class TaskFactory final
{
public:
	~TaskFactory();

	static TaskFactory & Instance()
	{
		static TaskFactory instance;
		return instance;
	}

	TaskBase * Create(uint16_t id);

private:
	TaskFactory();
};

#define TASK_FACTORY TaskFactory::Instance()
