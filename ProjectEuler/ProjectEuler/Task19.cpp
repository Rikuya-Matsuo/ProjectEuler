#include "Task19.h"

Task19::Task19()
{
	// コンテナのサイズ確保
	size_t numOfDay = (mYearEnd - mYearStart + 1) * 12;
	mDates.reserve(numOfDay);
}

Task19::~Task19()
{
	for (auto & d : mDates)
	{
		if (d)
		{
			delete d;
			d = nullptr;
		}
	}
	mDates.clear();
	mDates.shrink_to_fit();
}

void Task19::Run()
{
	STD_COUT("Capacity : ", mDates.capacity());
	
	// 問題文から与えられた、基準となる日付
	Date base(1900, 1, 1);
	base.mDayOfWeek = DayOfWeek::MONDAY;

	// データ設定
	for (auto year = mYearStart; year <= mYearEnd; ++year)
	{
		for (uint8 month = 1; month <= 12; ++month)
		{
			Date * date = new Date(year, month, 1);
			date->mDayOfWeek = base.mDayOfWeek + Calender::CalcPassDays(&base, date);

			std::cout << "SetDate : " <<
				date->mYear << "/" << (uint16)date->mMonth << "/" << (uint16)date->mDay << " " << Calender::GetStrDayOfWeek(date->mDayOfWeek) << std::endl;

			mDates.emplace_back(date);
		}
	}

	STD_COUT("Size : ", mDates.size());

	// 走査で月初めの日曜日の数を算出
	size_t sundayCnt = 0;
	for (const auto date : mDates)
	{
		if (date->mDayOfWeek == DayOfWeek::SUNDAY)
		{
			++sundayCnt;
		}
	}

	STD_COUT("Answer : ", sundayCnt);
}

Date::Date(uint16 year, uint8 month, uint8 day) :
	mYear(year),
	mMonth(month),
	mDay(day),
	mDayOfWeek(DayOfWeek::INVALID)
{}

DayOfWeek operator+(DayOfWeek dow, sint32 passDay)
{
	if (dow == DayOfWeek::INVALID) return DayOfWeek::INVALID;

	sint32 newDow = ((sint32)dow + passDay) % (sint32)DayOfWeek::INVALID;
	return (DayOfWeek)newDow;
}

DayOfWeek& operator+=(DayOfWeek& dow, sint32 passDay)
{
	dow = dow + passDay;
	return dow;
}

DayOfWeek operator-(DayOfWeek dow, sint32 beforeDay)
{
	return (dow + ((sint32)DayOfWeek::INVALID - beforeDay));
}

DayOfWeek& operator-=(DayOfWeek & dow, sint32 passDay)
{
	dow = dow - passDay;
	return dow;
}

namespace Calender
{
	bool IsLeapYear(uint16 year)
	{
		if (year % 4 != 0)
		{
			return false;
		}

		if (year % 100 == 0 && year % 400 != 0)
		{
			return false;
		}

		return true;
	}

	uint8 GetDaysOfMonth(uint16 year, uint8 month)
	{
		uint8 ret;
		switch (month)
		{
		case 4:
		case 6:
		case 9:
		case 11:
			ret = 30;
			break;

		case 2:
			ret = IsLeapYear(year) ? 29 : 28;
			break;

		default:
			ret = 31;
			break;
		}

		return ret;
	}

	sint32 CalcPassDays(const Date * past, const Date * future)
	{
		sint32 passDay = 0;

		// まずはそれぞれの年の1/1同士で計算すると考える
		for (auto y = past->mYear; y < future->mYear; ++y)
		{
			passDay += IsLeapYear(y) ? 366 : 365;
		}

		auto calcPassDayFromJan1 = [](const Date * date) -> sint32
		{
			sint32 passDayFromJan1 = 0;
			uint8 monthFromJan1 = date->mMonth - 1;
			uint8 dayFromJan1 = date->mDay - 1;
			for (uint8 mthCnt = 0; mthCnt < monthFromJan1; ++mthCnt)
			{
				passDayFromJan1 += GetDaysOfMonth(date->mYear, mthCnt + 1);
			}
			passDayFromJan1 += dayFromJan1;

			return passDayFromJan1;
		};

		// 過去の日付の、その年の1/1からの経過日数を計算し、
		// その分経過日数から減算
		passDay -= calcPassDayFromJan1(past);

		// 未来の日付の、その年の1/1からの経過日数を計算し、
		// その分経過日数に加算
		passDay += calcPassDayFromJan1(future);

		return passDay;
	}

	const char * GetStrDayOfWeek(DayOfWeek dow)
	{
		const char * tbl[] =
		{
			"MON",
			"TUE",
			"WED",
			"THU",
			"FRI",
			"SAT",
			"SUN"
		};

		return tbl[(uint8)dow];
	}
}
