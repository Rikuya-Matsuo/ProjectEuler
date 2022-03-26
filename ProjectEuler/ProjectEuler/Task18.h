#pragma once
#include "TaskBase.h"

// 問題67で類似の問いが出るため、継承することを想定して設計する
class Task18 : public TaskBase
{
public:
	Task18();
	~Task18();

	virtual void Run() override;

protected:
	struct Node;

protected:
	virtual void RunImpl(const char * dataFileName, const char * loadFailMsg = "Task18 terminated");

	bool LoadFile(const char * fileName);

	void CalcMaxPoint();

protected:
	using Node2DArray = std::vector<std::vector<Node*>>;
	Node2DArray mNodes;
};

struct Task18::Node
{
	using ValueType = uint16;
	ValueType mValue;
	const Node * mUnderLinkNodes[2];

	Node(ValueType value = 0) : mValue(value)
	{
		for (uint8 i = 0; i < 2; ++i)
		{
			mUnderLinkNodes[i] = nullptr;
		}
	}
};
