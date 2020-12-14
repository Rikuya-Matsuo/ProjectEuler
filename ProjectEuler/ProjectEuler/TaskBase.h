#pragma once
#include <iostream>

class TaskBase
{
public:
	TaskBase();
	virtual ~TaskBase();

	virtual void Run() = 0;
};
