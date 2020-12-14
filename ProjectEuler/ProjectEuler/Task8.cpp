#include "Task8.h"
#include <vector>
#include <cstring>

Task8::Task8()
{
}


Task8::~Task8()
{
}

void Task8::Run()
{
	const size_t termNum = 13;

	std::vector<uint8_t> items;
	items.reserve(termNum + 1);

	size_t productMax = 0;

	std::vector<uint8_t> productMaxItems;
	productMaxItems.resize(termNum);
	for (auto itr = productMaxItems.begin(); itr != productMaxItems.end(); ++itr)
	{
		*itr = 0;
	}

	char buf[2] = { '\0', '\0' };

	// ����const�͓��e��������Ȃ��Ƃ����Ӗ��Ȃ̂ŁA�|�C���^�̈ʒu���͓̂�������
	const char * txtPtr = mText;

	while ((*txtPtr) != '\0')
	{
		buf[0] = (*txtPtr);
		uint8_t item = (uint8_t)atoi(buf);

		// ������0�ȊO�̐����ł���ꍇ
		if (item)
		{
			// �L�^
			items.emplace_back(item);

			// ��̋L�^�ɂ����items�̗v�f������������1�����Ȃ����ꍇ
			if (items.size() >= termNum)
			{
				while (items.size() != termNum)
				{
					// ��ԓ����폜
					items.erase(items.begin());
				}

				// �ς��Z�o
				size_t x = 1;
				for (auto elem : items)
				{
					x *= elem;
				}

				// �����o�����ς��A����܂łōő�̐ς����傫����΋L�^
				if (productMax < x)
				{
					productMax = x;

					// ���̍����L�^
					for (size_t i = 0; i < termNum; ++i)
					{
						productMaxItems[i] = items[i];
					}
				}
			}
		}
		// ������0�Ȃ�Ί|���Z�Ɏg���Ă����ʂȂ̂ŁA�R���e�i���N���A���ē�����i�[���n�߂�
		else
		{
			items.clear();
		}

		++txtPtr;
	}

	for (size_t i = 0; i < productMaxItems.size(); ++i)
	{
		std::cout << ((i) ? " * " : "") << (short)productMaxItems[i];
	}
	std::cout << "\n\t= " << productMax << std::endl;
}
