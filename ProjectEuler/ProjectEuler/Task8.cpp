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

	// このconstは内容をいじらないという意味なので、ポインタの位置自体は動かせる
	const char * txtPtr = mText;

	while ((*txtPtr) != '\0')
	{
		buf[0] = (*txtPtr);
		uint8_t item = (uint8_t)atoi(buf);

		// 文字が0以外の数字である場合
		if (item)
		{
			// 記録
			items.emplace_back(item);

			// 上の記録によってitemsの要素数が項数よりも1つ多くなった場合
			if (items.size() >= termNum)
			{
				while (items.size() != termNum)
				{
					// 一番頭を削除
					items.erase(items.begin());
				}

				// 積を算出
				size_t x = 1;
				for (auto elem : items)
				{
					x *= elem;
				}

				// 導き出した積が、これまでで最大の積よりも大きければ記録
				if (productMax < x)
				{
					productMax = x;

					// その項も記録
					for (size_t i = 0; i < termNum; ++i)
					{
						productMaxItems[i] = items[i];
					}
				}
			}
		}
		// 文字が0ならば掛け算に使っても無駄なので、コンテナをクリアして頭から格納を始める
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
