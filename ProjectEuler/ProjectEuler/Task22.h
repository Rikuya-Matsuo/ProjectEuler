#pragma once
#include "TaskBase.h"

class Task22 : public TaskBase
{
public:
	Task22();
	~Task22();

	void Run() override;

private:
	std::vector<std::string> mNameList;

	const char* mLetterOrder;
	std::unordered_map<char, uint32> mLetterScore;

private:
	void LoadNameList();

	size_t CalcSumScore() const;
};
