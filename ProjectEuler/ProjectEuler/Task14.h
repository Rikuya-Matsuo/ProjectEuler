#pragma once
#include "TaskBase.h"
#include <unordered_map>
#include <memory>

class Task14 : public TaskBase
{
public:
	Task14();
	~Task14();

	void Run() override;

	struct Node;

private:
	std::unordered_map<uint32_t, Node> mNodes;

	void SeqNodeSetting();

	void SeqCalcLongestNodeChain();

	void CreateNodeChain(uint32_t num);

	uint32_t CalcNextNum(uint32_t num) const { return (num % 2) ? (num * 3 + 1) : (num / 2); }
};

struct Task14::Node
{
	uint32_t mNum;
	Node * mNext;

	// 最長チェーンの開始番号の可能性があるか
	bool mHeadCandidate;

	Node(uint32_t num)
		: mNum(num)
		, mNext(nullptr)
		, mHeadCandidate(true)
	{}

	Node() : Node(0) {}

	~Node()
	{
		mNext = nullptr;
	}

	uint32_t CalcChainLength() const
	{
		return Echo();
	}

	// 内部処理用。mNextがnullptrでなければn + 1を返す。nullptrであればnを返す。
	uint32_t Echo(uint32_t n = 1) const
	{
		if (mNext)
		{
			++n;
			return mNext->Echo(n);
		}
		else
		{
			return n;
		}
	}
};
