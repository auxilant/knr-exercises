#include <stdio.h>

main() {
	float cels, fahr;
	int lower, upper, step;

	lower = -20;
	upper = 150;
	step = 10;
	cels = lower;

	printf("Celsius Fahrenheit\n");
	while (cels <= upper) {
		fahr = (9.0 / 5.0) * cels + 32.0;
		printf("%7.0f %10.1f\n", cels, fahr);
		cels = cels + step;
	}
}
