#include "Task14.h"

bool operator==(const Task14::Node & node, uint32_t num)
{
	return node.mNum == num;
}

bool operator!=(const Task14::Node & node, uint32_t num)
{
	return node.mNum != num;
}

bool operator==(const Task14::Node & lhs, const Task14::Node & rhs)
{
	return lhs.mNum == rhs.mNum;
}

bool operator!=(const Task14::Node & lhs, const Task14::Node & rhs)
{
	return lhs.mNum != rhs.mNum;
}

Task14::Task14()
{
}

Task14::~Task14()
{
	mNodes.clear();
}

void Task14::Run()
{
	std::cout << "=====SeqNodeSetting=====\n";
	SeqNodeSetting();

	std::cout << "=====SeqCalcLongestNodeChain=====\n";
	SeqCalcLongestNodeChain();
}

void Task14::SeqNodeSetting()
{
	// 1~999,999でループ
	for (uint32_t i = 1; i < MILLION; ++i)
	{
		CreateNodeChain(i);

		if (!(i % 1000))
		{
			std::cout << i << std::endl;
		}
	}
}

void Task14::SeqCalcLongestNodeChain()
{
	uint32_t maxLen = 0;
	uint32_t maxStartNum = 0;

	for (uint32_t i = 1; i < MILLION; ++i)
	{
		const Node & nodeRef = mNodes[i];
		
		if ( !nodeRef.mHeadCandidate )
		{
			continue;
		}

		uint32_t len = nodeRef.CalcChainLength();
		if (len > maxLen)
		{
			maxLen = len;
			maxStartNum = i;

			std::cout << "record update. current : " << i << std::endl;
		}
	}

	std::cout << "startNum : " << maxStartNum << std::endl;
	std::cout << "length : " << maxLen << std::endl;

	std::cout << "==content==\n";

	Node * ptr = nullptr;
	for (ptr = &mNodes[maxStartNum]; ptr != nullptr; ptr = ptr->mNext)
	{
		std::cout << ptr->mNum;

		std::cout << ((ptr->mNum != 1) ? ',' : ';');
	}

	std::cout << std::endl;
}

void Task14::CreateNodeChain(uint32_t num)
{
	// numのノードが存在する状態に
	{
		auto itr = mNodes.find(num);

		if (itr == mNodes.end())
		{
			// ノードを新規作成
			auto node = Node(num);
			mNodes[num] = node;
		}
		else
		{
			// 既に存在するならこれ以上設定の必要は無し
			return;
		}
	}

	// numが1の場合次のノードはない
	if (num == 1)
	{
		return;
	}

	// 次のノードが存在する状態に
	uint32_t nextNum = CalcNextNum(num);
	CreateNodeChain(nextNum);

	// numノードをnextNumノードにつなぐ
	auto nextNode = &mNodes[nextNum];
	nextNode->mHeadCandidate = false;
	mNodes[num].mNext = nextNode;
}
