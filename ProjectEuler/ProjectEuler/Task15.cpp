#include "Task15.h"

Task15::Task15()
{
}

Task15::~Task15()
{
}

void Task15::Run()
{
	const size_t horizon = 20;
	const size_t vertical = 20;

	CalcRoute(horizon, vertical);
}

void Task15::CalcRoute(size_t gridH, size_t gridV)
{
	size_t sum = gridH + gridV;

	Array hArray, vArray, sumArray;
	SetupArray(hArray, gridH);
	SetupArray(vArray, gridV);
	SetupArray(sumArray, sum);

	ReduceFraction(sumArray, hArray);
	ReduceFraction(sumArray, vArray);

	size_t sumMult = MultArray(sumArray);
	size_t hMult = MultArray(hArray);
	size_t vMult = MultArray(vArray);

	size_t answer = sumMult / (hMult * vMult);

	std::cout << "Answer : " << answer << std::endl;
}

void Task15::SetupArray(Array& arr, size_t num)
{
	arr.reserve(num);
	// 効率化のため、配列に１は入れない
	for (size_t i = 1; i < num; ++i)
	{
		arr.emplace_back(i + 1);
	}
}

void Task15::ReduceFraction(Array& arr1, Array& arr2)
{
	for (auto& num1 : arr1)
	{
		if (num1 == 1) continue;

		for (auto& num2 : arr2)
		{
			if (num2 == 1) continue;

			// 同数ならどちらも１に
			if (num1 == num2)
			{
				num1 = num2 = 1;
				continue;
			}

			// 割り切れるかを調べる
			auto larger = num1;
			auto smaller = num2;
			if (num1 < num2)
			{
				larger = num2;
				smaller = num1;
			}

			float fDivide = (float)larger / (float)smaller;
			bool isInteger = ((fDivide - (int)fDivide) == 0.0f);
			// 割り切れるなら割る
			if (isInteger)
			{
				auto newLargeNum = larger / smaller;
				if (num1 == larger)
				{
					num1 = newLargeNum;
					num2 = 1;
				}
				else
				{
					num1 = 1;
					num2 = newLargeNum;
				}
			}
		}
	}

	// １と０の値を削除
	auto erase1 = [](Array& arr)
	{
		auto eraseCond = [](size_t num) -> bool
		{
			return (num == 1 || !num);
		};

		bool erased = false;
		for (auto itr = arr.begin(); itr != arr.end(); ++itr)
		{
			if (erased)
			{
				--itr;
				erased = false;
			}

			if (eraseCond(*itr))
			{
				itr = arr.erase(itr);
				erased = true;
			}
		}

		// ループの最後にも削除を行った場合、配列最後尾の値もチェック
		if (erased)
		{
			auto itr = arr.end() - 1;
			if (eraseCond(*itr))
			{
				arr.erase(itr);
			}
		}
		arr.shrink_to_fit();
	};
	erase1(arr1);
	erase1(arr2);
}

size_t Task15::MultArray(const Array & arr)
{
	size_t mult = 1;
	for (auto num : arr)
	{
		mult *= num;
	}
	return mult;
}
