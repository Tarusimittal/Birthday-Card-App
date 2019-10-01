#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
	return;
}

int partition(int a[], int l, int r) {
	int x = l;
	int i;
	for (i = l; i < r; i++) {
		if (a[i] < a[r-1]) {
			swap(&a[x++], &a[i]);
		}
	}
	swap(&a[x], &a[r-1]);
	return x;
}

int random_partition(int a[], int l, int r) {
	if (l == r) return r;
	srand(time(0));
	int rp = l + (rand() % (r - l));
	swap(&a[rp], &a[r-1]);
	return partition(a, l, r);
}

int quickselect(int a[], int k, int l, int r) {
	int q = random_partition(a, l, r);
	if (q == k) return a[q];
	else if (q > k) return quickselect(a, k, l, q-1);
	else return quickselect(a, k, q + 1, r);
}

int main() {
	int n;
	printf("Enter the total number of computers: ");
	scanf("%d", &n);
	getchar();
	printf("Enter the positions of the computers in coordinate system:\n");
	int y[n];
	int i;
	for (i = 0; i < n; i++) {
		scanf("(%*d,%d)", &y[i]);
		if (i != n-1) {
			scanf(",");
		}
	}

	printf("Output = Line should be at y = %d\n", quickselect(y, (n-1)/2, 0, n));
}