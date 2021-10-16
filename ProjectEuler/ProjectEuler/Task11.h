#pragma once
#include "TaskBase.h"

class Task11 : public TaskBase
{
public:
	Task11();
	~Task11();

	void Run() override;

private:
	void LoadGrid(const std::string & fileName, char ** & gridArray);

	void Print(char ** gridArray);

	void Calc(char ** gridArray);

	size_t mAnswer;

	char mItems[4];
};
