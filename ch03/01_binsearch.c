#include <stdio.h>

int binsearch(int x, int arr[], int size);

main() {
	const int size = 100000;
	int arr[size];
	int i;
	
	for (i = 0; i < size; ++i) {
		arr[i] = 2 * i;
	}
	
	for (i = 0; i < 2*size; ++i) {
		printf("%d\n", binsearch(i, arr, size));
	}

	return 0;
}

int binsearch(int x, int v[], int n) {
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low < high) {
		mid = (low + high) / 2;
		if (x <= v[mid]) {
			high = mid;
		} else {
			low = mid + 1 ;
		} 
	}

	if (v[low] == x) {
		return low;
	}

	return -1;
}
