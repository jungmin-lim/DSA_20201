#include <stdio.h>
#include <string.h>
#define max_string_size 101
#define max_pattern_size 101

int nfind(char *string, char *pattern) {
	int i = 0, j = 0, start = 0;
	int lasts = strlen(string) - 1;
	int lastp = strlen(pattern) - 1;
	int endmatch = lastp;

	for (i = 0; endmatch <= lasts; ++endmatch, ++start) {
		if (string[endmatch] == pattern[lastp]) {
			for (j = 0, i = start; j < lastp && string[i] == pattern[j]; ++i, ++j) {
			}
		}
		if (j == lastp) {
			return start;
		}
	}
	return -1;
}

int main(void) {

	char string[max_string_size];
	char pattern[max_pattern_size];

	printf("���ڿ��� �Է��ϼ��� : ");
	gets(string);
	printf("���� ������ �Է��ϼ��� : ");
	gets(pattern);
	printf("���ڿ� %d ��°���� ������ ���۵�..\n", nfind(string, pattern));

	return 0;
}