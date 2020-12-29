#include "Task11.h"
#include <fstream>
#include <thread>
#include <mutex>

Task11::Task11()
{
}

Task11::~Task11()
{
}

void Task11::Run()
{
	char ** grid = nullptr;

	LoadGrid("task11data.txt", grid);

	Print(grid);

	Calc(grid);

	for (size_t i = 0; i < 4; ++i)
	{
		short num = static_cast<short>(mItems[i]);

		std::cout << ((i) ? " * " : "") << num;
	}
	std::cout << '\n';

	std::cout << "\t\t = " << mAnswer;

	for (size_t i = 0; i < 20; ++i)
	{
		delete[] grid[i];
	}
	delete[] grid;
}

void Task11::LoadGrid(const std::string & fileName, char ** & gridArray)
{
	std::ifstream file(fileName);

	if (file.fail())
	{
		std::cout << "fail to read file.\n";
		return;
	}

	gridArray = new char*[20];
	for (size_t i = 0; i < 20; ++i)
	{
		gridArray[i] = new char[20];
	}
	size_t gridX = 0;
	size_t gridY = 0;

	char buf[3];
	uint8_t bufIndex = 0;

	while (!(file.rdstate() & file.eofbit))
	{
		char c = file.get();

		if (file.eof())
		{
			std::cout << "";
		}

		if (c == ' ' || c == '\n' || file.eof())
		{
			buf[bufIndex] = '\0';

			gridArray[gridY][gridX] = atoi(buf);

			if (++gridX >= 20)
			{
				gridX = 0;
				++gridY;
			}

			bufIndex = 0;

			continue;
		}
		
		buf[bufIndex++] = c;
	}

	return;
}

void Task11::Print(char ** gridArray)
{
	for (size_t y = 0; y < 20; ++y)
	{
		for (size_t x = 0; x < 20; ++x)
		{
			const char * tmp = "%02d";
			char buf[4];
			sprintf_s(buf, tmp, static_cast<short>(gridArray[y][x]));

			std::cout << buf << ' ';
		}

		std::cout << '\n';
	}
}

void Task11::Calc(char ** gridArray)
{
	struct IndexStruct
	{
		int mX = 0;
		int mY = 0;

		bool IsInvalid() const
		{
			bool invalidFlag =
				mX >= 20 || mX < 0 ||
				mY >= 20 || mY < 0;

			return invalidFlag;
		}
	};

	IndexStruct indexes[4];
	std::mutex indexesMutex;

	auto setIndexes = [&indexes](int x, int y, int xoffset, int yoffset) -> bool
	{
		auto setIndex = [&indexes](int xoffset, int yoffset, size_t i)
		{
			if (!i)
			{
				indexes[i].mX = indexes[i].mY = -1;
				return;
			}

			indexes[i].mX = indexes[i - 1].mX + xoffset;
			indexes[i].mY = indexes[i - 1].mY + yoffset;
			return;
		};

		indexes[0].mX = x;
		indexes[0].mY = y;

		if (indexes[0].IsInvalid())
		{
			return false;
		}

		for (size_t i = 1; i < 4; ++i)
		{
			setIndex(xoffset, yoffset, i);

			if (indexes[i].IsInvalid())
			{
				return false;
			}
		}

		return true;
	};

	auto value = [gridArray](const IndexStruct & index)
	{
		return gridArray[index.mY][index.mX];
	};

	struct ResultData
	{
		size_t mAns;
		char mItems[4];
	};

	auto checkLoop = [&](ResultData & result, int xoffset, int yoffset)
	{
		result.mAns = 0;

		for (size_t y = 0; y < 20; ++y)
		{
			for (size_t x = 0; x < 20; ++x)
			{
				std::lock_guard<std::mutex> lock(indexesMutex);

				bool success = setIndexes((int)x, (int)y, xoffset, yoffset);

				if (!success)
				{
					continue;
				}

				size_t product = 1;
				for (size_t i = 0; i < 4; ++i)
				{
					product *= value(indexes[i]);
				}

				if (result.mAns < product)
				{
					result.mAns = product;

					for (size_t i = 0; i < 4; ++i)
					{
						result.mItems[i] = value(indexes[i]);
					}
				}
			}
		}
	};

//#define TEST
#ifdef TEST
	ResultData hRes;
	checkLoop(hRes, 1, 0);
#else
	ResultData hRes;
	std::thread hTh(checkLoop, std::ref(hRes), 1, 0);

	ResultData vRes;
	std::thread vTh(checkLoop, std::ref(vRes), 0, 1);

	ResultData LUtoRDRes;
	std::thread lurdTh(checkLoop, std::ref(LUtoRDRes), 1, 1);

	ResultData RUtoLDRes;
	std::thread ruldTh(checkLoop, std::ref(RUtoLDRes), -1, 1);

	hTh.join();
	vTh.join();
	lurdTh.join();
	ruldTh.join();

	ResultData & maxRes = hRes;
	
	if (maxRes.mAns < vRes.mAns)
	{
		maxRes = vRes;
	}

	if (maxRes.mAns < LUtoRDRes.mAns)
	{
		maxRes = LUtoRDRes;
	}

	if (maxRes.mAns < RUtoLDRes.mAns)
	{
		maxRes = RUtoLDRes;
	}

	mAnswer = maxRes.mAns;
	for (size_t i = 0; i < 4; ++i)
	{
		mItems[i] = maxRes.mItems[i];
	}
#endif
}
