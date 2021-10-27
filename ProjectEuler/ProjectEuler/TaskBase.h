#pragma once
#include <iostream>
#include "MathUnit.h"

class TaskBase
{
public:
	TaskBase();
	virtual ~TaskBase();

	virtual void Run() = 0;
};
