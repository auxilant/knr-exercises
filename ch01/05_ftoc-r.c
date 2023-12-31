#include <stdio.h>

main() {
	int fahr;

	printf("Fahrenheit Celsius\n");
	for (fahr = 300; fahr >= 0; fahr = fahr - 20) {
		printf("%10d %7.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));
	}
}
