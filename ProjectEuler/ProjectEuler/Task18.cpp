#include "Task18.h"
#include <cstring>

Task18::Task18()
{
}

Task18::~Task18()
{
	for (auto& line : mNodes)
	{
		for (auto nodePtr : line)
		{
			delete nodePtr;
			nodePtr = nullptr;
		}
		line.clear();
	}
	mNodes.clear();
}

void Task18::Run()
{
	RunImpl("task18data.txt");
}

void Task18::RunImpl(const char * dataFileName, const char * loadFailMsg)
{
	bool success = LoadFile(dataFileName);
	if (!success)
	{
		if (loadFailMsg)
		{
			std::cout << loadFailMsg << std::endl;
		}
		return;
	}

	CalcMaxPoint();
}

bool Task18::LoadFile(const char * fileName)
{
	// ファイルロード
	std::ifstream file(fileName);
	if (file.fail())
	{
		std::cout << "fail to read file\n";
		return false;
	}

	std::vector<std::string> content;
	while ( std::getline(file, *content.insert(content.end(), std::string())) );	// 空文を回す

	if (content.back().empty())
	{
		content.pop_back();
	}

	file.close();

#define OUTPUT_CONTENT (1)
#if OUTPUT_CONTENT
	// ファイル内容表示
	for (auto& str : content)
	{
		std::cout << str << std::endl;
	}
#endif
#undef OUTPUT_CONTENT

	// ノード作成
	mNodes.clear();
	mNodes.resize(content.size());
	for (size_t i = 0; i < content.size(); ++i)
	{
		auto& line = mNodes[i];
		line.reserve(i + 1);

		std::stringstream stream(content[i]);
		std::vector<std::string> parsed;
		while ( std::getline(stream, *parsed.insert(parsed.end(), std::string()), ' ') );

		if (parsed.back().empty())
		{
			parsed.pop_back();
		}

		for (auto& p : parsed)
		{
			Node::ValueType value = std::stoi(p);
			auto nd = new Node(value);
			if (nd)
			{
				line.emplace_back(nd);
			}
		}
	}

	// ノードリンク設定
	for (size_t i = 0; i < mNodes.size() - 1; ++i)	// 最下部は行わない
	{
		auto & line = mNodes[i];
		auto & nextLine = mNodes[i + 1];
		for (size_t j = 0; j < line.size(); ++j)
		{
			auto nd = line[j];
			nd->mUnderLinkNodes[0] = nextLine[j];
			nd->mUnderLinkNodes[1] = nextLine[j + 1];
		}
	}

	return true;
}

void Task18::CalcMaxPoint()
{
	// そのノードから下で取得し得る最大の値
	std::unordered_map<const Node*, size_t> maxPoint;

	// 下の方からmaxPointを求める
	for (auto lineItr = mNodes.rbegin(); lineItr != mNodes.rend(); ++lineItr)
	{
		const bool isBottom = (lineItr == mNodes.rbegin());
		for (auto nd : *lineItr)
		{
			if (!isBottom)
			{
				if (!nd->mUnderLinkNodes[0] || !nd->mUnderLinkNodes[1]) continue;

				size_t max = 0;
				for (uint8 index = 0; index < 2; ++index)
				{
					size_t point = maxPoint[nd->mUnderLinkNodes[index]] + nd->mValue;
					if (point > max)
					{
						max = point;
					}
				}

				maxPoint[nd] = max;
			}
			else
			{
				// 最下部の場合はそのノードの値がそのままmaxPointとなる
				maxPoint[nd] = nd->mValue;
			}
		}
	}

	// 最上部のノードのmaxPointが答えとなる
	auto topNode = mNodes.front().front();
	STD_COUT("Answer : ", maxPoint[topNode]);
}
