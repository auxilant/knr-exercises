void swap(int *a, int *b);

void myqsort(int *arr, int left, int right) {
	if (left >= right) {
		return;
	}
	int mid = left;
	int i;
	for (i = left + 1; i <= right; i++) {
		if (arr[i] < arr[left]) {
			mid++;
			swap(arr + mid, arr + i);
		}
	}
	swap(arr + left, arr + mid);
	myqsort(arr, left, mid-1);
	myqsort(arr, mid+1, right);
}

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
