#include <stdio.h>
#include <ctype.h>

int isVowel(char c) {
	char vowel[] = { 'a', 'e', 'i', 'o', 'u' };
	int i = 0;
	for (i = 0; i < 5; ++i) {
		if (c == vowel[i]) {
			return 1;
		}
	}
	return 0;
}

int main(int argc, const char* argv[]) {
	char str[1000];
	int i = 0;

	printf("���ڿ� �Է� : ");
	gets(str);
	printf("������ �빮�ڷ� ��ȯ ��� : ");

	while (str[i] != '\0') {
		if (!isVowel(str[i])) {
			printf("%c", toupper(str[i]));
		}
		else {
			printf("%c", str[i]);
		}
		++i;
	}
	printf("\n");
	return 0;
}