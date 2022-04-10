#pragma once
#include "TaskBase.h"

enum class DayOfWeek : uint8;
struct Date;

class Task19 : public TaskBase
{
public:
	Task19();
	~Task19();

	void Run() override;

private:
	std::vector<Date*> mDates;

	static const uint16 mYearStart = 1901;
	static const uint16 mYearEnd = 2000;
};

struct Date
{
	uint16 mYear;
	uint8 mMonth;
	uint8 mDay;

	DayOfWeek mDayOfWeek;

	Date(uint16 year, uint8 month, uint8 day);
};

enum class DayOfWeek : uint8
{
	MONDAY = 0,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	SUNDAY,

	INVALID
};

DayOfWeek operator+(DayOfWeek dow, sint32 passDay);
DayOfWeek& operator+=(DayOfWeek& dow, sint32 passDay);
DayOfWeek operator-(DayOfWeek dow, sint32 beforeDay);
DayOfWeek& operator-=(DayOfWeek& dow, sint32 passDay);

namespace Calender
{
	bool IsLeapYear(uint16 year);

	uint8 GetDaysOfMonth(uint16 year, uint8 month);

	sint32 CalcPassDays(const Date * past, const Date * future);

	const char * GetStrDayOfWeek(DayOfWeek dow);
}
