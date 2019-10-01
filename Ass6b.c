#include <stdio.h>

typedef struct size {
	int divx;
	int divy;
	int occurence;
	int profit;
} size;

void trace(int sz, size track[][sz], int x, int y) {
	if (track[x][y].divx != 0) {
		trace(sz, track, track[x][y].divx, y);
		trace(sz, track, x - track[x][y].divx, y);
	} else if (track[x][y].divy != 0) {
		trace(sz, track, x, track[x][y].divy);
		trace(sz, track, x, y - track[x][y].divy);
	} else {
		track[x][y].occurence++;
	}
	return;
}

int main() {
	int x, y, n, d1, d2, c, i, j;

	printf("Enter dimension of sheet: ");
	scanf("%d, %d", &x, &y);

	printf("Enter the number of products : ");
	scanf("%d", &n);

	int revenue[x + 1][y + 1];
	size track[x + 1][y + 1];

	//Initializing revenue and track;
	for (i = 0; i < x + 1; i++) {
		for (j = 0; j < y + 1; j++) {
			revenue[i][j] = 0;
			track[i][j].divy = 0;
			track[i][j].divx = 0;
			track[i][j].occurence = 0;
			track[i][j].profit = 0;
		}
	}

	printf("Enter dimensions of all products and profit respectively\n");
	for (i = 0; i < n; i++) {
		scanf("%d, %d, %d", &d1, &d2, &c);
		//Since we can cut cloth of 2x3 as well as 3x2
		revenue[d1][d2] = c;
		revenue[d2][d1] = c;
		track[d1][d2].profit = c;
		track[d2][d1].profit = c;
	}

	//Dynamic Programming approach;
	for (i = 0; i < x + 1; i++) {
		for (j = 0; j < y + 1; j++) {
			int x1 = i - 1, y1 = j - 1;
			while (y1 >= 0) {
				if (revenue[i][y1] + revenue[i][j - y1] > revenue[i][j]) {
					revenue[i][j] = revenue[i][y1] + revenue[i][j - y1];
					track[i][j].divy = y1;
					track[i][j].divx = 0;
				}
				y1--;
			}
			while (x1 >= 0) {
				if (revenue[x1][j] + revenue[i - x1][j] > revenue[i][j]) {
					revenue[i][j] = revenue[x1][j] + revenue[i - x1][j];
					track[i][j].divx = x1;
					track[i][j].divy = 0;
				}
				x1--;
			}
		}
	}

	printf("Maximum profit : %d\n", revenue[x][y]);

	//Printing the cloths;
	printf("Strategy of cutting cloth\n");
	trace(y + 1, track, x, y);
	for (i = 0; i < x + 1; i++) {
		for (j = 0; j < y + 1; j++) {
			if (track[i][j].occurence != 0 && track[i][j].profit != 0) {
				int occurence = track[i][j].occurence + track[j][i].occurence;
				track[i][j].occurence = 0;
				track[j][i].occurence = 0;
				if (i == j) occurence /= 2;
				printf("%d cloths of %dX%d\n", occurence, i, j);
			}
		}
	}
}