#pragma once
#include <iostream>
#include <cstdint>
#include <vector>
#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "MathUnit.h"

#define USING_INT_TYPE(bitnum)\
using uint##bitnum = uint##bitnum##_t;\
using sint##bitnum = int##bitnum##_t

USING_INT_TYPE(8);
USING_INT_TYPE(16);
USING_INT_TYPE(32);

class TaskBase
{
public:
	TaskBase();
	virtual ~TaskBase();

	virtual void Run() = 0;
};
