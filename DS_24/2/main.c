#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RADIX 10
#define MAX_ELEMENT 100

int digit(int num, int d, int dig, int radix) {
	int i, j, temp;
	for (i = 0; i < dig - d - 1; ++i) {
		num = num / 10;
	}

	while (num >= 10) {
		num = num % 10;
	}

	return num;
}

int radixSort(int a[], int link[], int dig, int radix, int num) {
	int front[RADIX], rear[RADIX];
	int i, bin, current, first, last;
	int printi, printcurrent;

	first = 1;
	for (i = 1; i < num; ++i) {
		link[i] = i + 1;
	}
	link[num] = 0;

	// print list
	fprintf(stdout, "******************** initial chain ********************\n\t");
	for (i = 1; i <= num; ++i) {
		fprintf(stdout, "[%2d] ", i);
	}
	fprintf(stdout, "\n%7s:", "link");
	for (i = 1; i <= num; ++i) {
		fprintf(stdout, "%4d ", link[i]);
	}
	fprintf(stdout, "\n%7s:", "a");
	for (i = 1; i <= num; ++i) {
		fprintf(stdout, "%4d ", a[i]);
	}
	fprintf(stdout, "\n%7s:%4d\n", "first", first);
	fprintf(stdout, "\n%7s:", "result");
	for (current = first; current; current = link[current]) {
		fprintf(stdout, "%4d ", a[current]);
	}

	for (i = dig - 1; i >= 0; --i) {
		// init bin to empty queues
		for (bin = 0; bin < radix; ++bin) {
			front[bin] = 0;
			rear[bin] = 0;
		}

		for (current = first; current; current = link[current]) {
			bin = digit(a[current], i, dig, radix);
			if (front[bin] == 0) front[bin] = current;
			else link[rear[bin]] = current;
			rear[bin] = current;
		}

		for (bin = 0; !front[bin]; ++bin) {
			// skip
		}
		first = front[bin];
		last = rear[bin];

		for (bin++; bin < radix; bin++) {
			if (front[bin]) {
				link[last] = front[bin];
				last = rear[bin];
			}
		}

		link[last] = 0;

		fprintf(stdout, "\n\n******************** pass %d ********************\n\t", dig - i);
		for (printi = 1; printi <= num; ++printi) {
			fprintf(stdout, "[%2d] ", printi);
		}
		fprintf(stdout, "\n%7s:", "link");
		for (printi = 1; printi <= num; ++printi) {
			fprintf(stdout, "%4d ", link[printi]);
		}
		fprintf(stdout, "\n%7s:", "a");
		for (printi = 1; printi <= num; ++printi) {
			fprintf(stdout, "%4d ", a[printi]);
		}
		fprintf(stdout, "\n%7s:%4d\n", "first", first);
		fprintf(stdout, "\n%7s:", "result");
		for (printcurrent = first; printcurrent; printcurrent = link[printcurrent]) {
			fprintf(stdout, "%4d ", a[printcurrent]);
		}
		fprintf(stdout, "\n\n\t");
		for (printi = 0; printi < radix; ++printi) {
			fprintf(stdout, "[%2d] ", printi);
		}
		fprintf(stdout, "\n%7s:", "rear");
		for (printi = 0; printi < radix; ++printi) {
			fprintf(stdout, "%4d ", rear[printi]);
		}
		fprintf(stdout, "\n%7s:", "front");
		for (printi = 0; printi < radix; ++printi) {
			fprintf(stdout, "%4d ", front[printi]);
		}
	}
	return first;
}

int main(int argc, char *argv[]) {
	FILE *fp;
	int dig, radix = 10, size;
	int data[MAX_ELEMENT], link[MAX_ELEMENT];
	int i;

	fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d", &dig, &size);
	for (i = 1; i <= size; ++i) {
		fscanf(fp, "%d", &data[i]);
	}

	radixSort(data, link, dig, radix, size);

	fclose(fp);
	return 0;
}