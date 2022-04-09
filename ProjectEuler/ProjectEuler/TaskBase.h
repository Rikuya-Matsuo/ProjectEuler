#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include "MathUnit.h"
#include "IntType.h"

class TaskBase
{
public:
	TaskBase();
	virtual ~TaskBase();

	virtual void Run() = 0;
};

#define STD_COUT(str, var) std::cout << str << var << std::endl;
