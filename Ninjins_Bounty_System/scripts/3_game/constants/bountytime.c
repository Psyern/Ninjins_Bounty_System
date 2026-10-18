//! Wall-clock helpers (UTC) for data that must survive restarts - g_Game.GetTime() restarts at 0.
class obfc_BountyTime
{
	//! Days since 1970-01-01 (proleptic Gregorian, Howard Hinnant's days_from_civil).
	static int obfm_DaysFromCivil(int year, int month, int day)
	{
		int era;
		int yearOfEra;
		int shiftedMonth;
		int dayOfYear;
		int dayOfEra;
		if (month <= 2)
			year = year - 1;
		era = year / 400;
		yearOfEra = year - era * 400;
		if (month > 2)
			shiftedMonth = month - 3;
		else
			shiftedMonth = month + 9;
		dayOfYear = (153 * shiftedMonth + 2) / 5 + day - 1;
		dayOfEra = yearOfEra * 365 + yearOfEra / 4 - yearOfEra / 100 + dayOfYear;
		return era * 146097 + dayOfEra - 719468;
	}
	static int obfm_GetUnixDay()
	{
		int year;
		int month;
		int day;
		GetYearMonthDayUTC(year, month, day);
		return obfm_DaysFromCivil(year, month, day);
	}
	static int obfm_GetUnixTime()
	{
		int hour;
		int minute;
		int second;
		GetHourMinuteSecondUTC(hour, minute, second);
		return obfm_GetUnixDay() * 86400 + hour * 3600 + minute * 60 + second;
	}
	//! Week number since the epoch; weeks start on Monday 00:00 UTC (1970-01-01 was a Thursday).
	static int obfm_GetWeekIndex()
	{
		return (obfm_GetUnixDay() + 3) / 7;
	}
}
