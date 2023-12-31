#define ERROR 0

static char daytab0[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static char daytab1[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static char *daytab[] = {daytab0, daytab1};


int day_of_year(int year, int month, int day) {
	int i, leap;
	if (month < 1 || month > 12) {
		return ERROR;
	}

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	if (day < 1 || day > *(*(daytab + leap) + month)) {
		return ERROR;
	}

	for (i = 1; i < month; i++) {
		day += *(*(daytab + leap) + i);
	}
	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
	int i, leap;
	
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	if (yearday < 1 || yearday > 365 + leap) {
		*pmonth = *pday = ERROR;
		return;
	}

	for (i = 1; yearday > *(*(daytab + leap) + i); i++) {
		yearday -= *(*(daytab + leap) + i);
	}
	*pmonth = i;
	*pday = yearday;
}
