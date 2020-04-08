#include <stdio.h>
#include <string.h>`
#include <stdlib.h>
#define max_string_size 100
#define max_pattern_size 100

int failure[max_pattern_size];
char string[max_pattern_size];
char pattern[max_pattern_size];

void fail(char *pattern) {
	int i, j;
	int n = strlen(pattern);
	failure[0] = -1;
	for (j = 1; j < n; ++j) {
		i = failure[j - 1];
		while ((pattern[j] != pattern[i + 1]) && (i >= 0)) {
			i = failure[i];
		}
		if (pattern[j] == pattern[i + 1]) {
			failure[j] = i + 1;
		}
		else {
			failure[j] = -1;
		}
	}
}

int pmatch(char *string, char *pattern) {
	int i = 0, j = 0;
	int lens = strlen(string);
	int lenp = strlen(pattern);

	while (i < lens && j < lenp) {
		if (string[i] == pattern[j]) {
			i++;
			j++;
		}
		else if (j == 0) {
			i++;
		}
		else {
			j = failure[j - 1] + 1;
		}
	}
	return ((j == lenp) ? (i - lenp) : -1);
}

int main(void) {

	int i, l;

	printf("문자열을 입력하세요 : ");
	gets(string);
	printf("비교할 패턴을 입력하세요 : ");
	gets(pattern);

	l = strlen(pattern);
	fail(pattern);
	printf("pat의 위치 정보 값\n");
	for (i = 0; i < l; ++i) {
		printf("failure[%d]=%4d\n", i, failure[i]);
	}
	printf("문자열 %d 번째부터 패턴이 시작됨...", pmatch(string, pattern));
}