#include <stdio.h>

float ftoc(float fahr);

main() {
	float fahr, cels;
	int lower, upper, step;

	lower = 0;
	upper = 300;
	step = 20;
	fahr = lower;

	printf("Fahrenheit Celsius\n");
	while (fahr <= upper) {
		printf("%10.0f %7.1f\n", fahr, ftoc(fahr));
		fahr = fahr + step;
	}

	return 0;
}

float ftoc(float fahr) {
	return (5.0 / 9.0) * (fahr - 32.0);
}
