#include "Task26.h"

void Task26::Run()
{
	// 割り算の詳細を算出
	for (uint32 num = 2u; num < 1000u; ++num)
	{
		UnitFraction uf;
		uf.mNumber = num;
		auto& fpContainer = uf.mFractionPart;

		uint32 divTarget = 10u;
		while (true)
		{
			DivDigitInfo ddi;
			ddi.mQuotient = divTarget / num;
			ddi.mRemainder = divTarget % num;

			fpContainer.emplace_back(ddi);

			if (ddi.mRemainder == 0)
			{
				uf.mCycleStartIndex = uf.mCycleEndIndex = -1;
				break;
			}
			
			bool breakFlg = false;
			for (uint32 fpIndex = 0; fpIndex < fpContainer.size() - 1; ++fpIndex)
			{
				if (ddi.mRemainder == fpContainer[fpIndex].mRemainder)
				{
					uf.mCycleStartIndex = fpIndex;
					fpContainer.pop_back();
					uf.mCycleEndIndex = (sint32)fpContainer.size() - 1;
					breakFlg = true;
					break;
				}
			}
			if (breakFlg) { break; }

			divTarget = ddi.mRemainder * 10u;
		}

		fpContainer.shrink_to_fit();
		mUnitFractions[num] = uf;
	}

	// 詳細から答えを出す
	uint32 ans = 0;
	uint32 maxCycleLength = 0;
	for (const auto& uf : mUnitFractions)
	{
		auto& ufValue = uf.second;
		if (ufValue.mCycleStartIndex >= 0 && ufValue.mCycleEndIndex >= 0)
		{
			uint32 cycleLen = ufValue.mCycleEndIndex - ufValue.mCycleStartIndex + 1;
			if (cycleLen > maxCycleLength)
			{
				ans = uf.first;
				maxCycleLength = cycleLen;
			}
		}
	}

	// ログ出力
	auto& ansUf = mUnitFractions[ans];
	std::string divResult = "0.";
	for (auto& d : ansUf.mFractionPart)
	{
		divResult += std::to_string(d.mQuotient);
	}
	STD_COUT("Res : ", divResult);
	std::string cycle;
	for (sint32 i = ansUf.mCycleStartIndex; i <= ansUf.mCycleEndIndex; ++i)
	{
		cycle += std::to_string(ansUf.mFractionPart[i].mQuotient);
	}
	STD_COUT("Cyc : ", cycle);
	STD_COUT("Len : ", maxCycleLength);
	COUT_ANSWER(ans);
}
