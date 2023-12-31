#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

main() {
	printf("%d %d/%d/%d\n", day_of_year(2023, 12, 6), 2023, 12, 6); 	
	printf("%d %d/%d/%d\n", day_of_year(2024, 12, 6), 2024, 12, 6); 	
	printf("%d %d/%d/%d\n", day_of_year(2023, 12, 36), 2023, 12, 36); 	
	printf("%d %d/%d/%d\n", day_of_year(2023, 13, 6), 2023, 13, 6);

	int month, day;
	month_day(2023, 340, &month, &day);
	printf("%d %d %d/%d\n", 2023, 340, month, day);
	month_day(2024, 341, &month, &day);
	printf("%d %d %d/%d\n", 2024, 341, month, day);
	month_day(2023, 366, &month, &day);
	printf("%d %d %d/%d\n", 2023, 366, month, day);
}
