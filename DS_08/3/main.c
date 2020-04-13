#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 80

typedef struct listNode {
	char name[MAX_STRING_SIZE];
	char work[MAX_STRING_SIZE];
	char gender[MAX_STRING_SIZE];
	struct listNode *link;
}listNode;

listNode *makeList(listNode *head);
void makeGenderList(listNode **maleList, listNode **femaleList, listNode *head);
void printData(listNode *head);

int main(int argc, char *argv[]) {
	listNode *linkedList = NULL;
	listNode *maleList = NULL;
	listNode *femaleList = NULL;

	linkedList = makeList(linkedList);
	printf("전체 리스트\n");
	printData(linkedList);
	printf("\n\n");

	makeGenderList(&maleList, &femaleList, linkedList);
	printf("남자 리스트\n");
	printData(maleList);
	printf("\n\n");
	
	printf("여자 리스트\n");
	printData(femaleList);
	printf("\n");

	return 0;
}

listNode *makeList(listNode *head) {
	FILE *f;
	char n[MAX_STRING_SIZE], w[MAX_STRING_SIZE], g[MAX_STRING_SIZE];
	listNode *p, *node;

	p = head;
	f = fopen("input.txt", "r");
	while (fscanf(f, "%s %s %s", n, w, g) != EOF) {
		if ((node = (listNode *)malloc(sizeof(*node))) == NULL) {
			fprintf(stderr, "Insufficient memory");
			exit(EXIT_FAILURE);
		}	
		strcpy(node->name, n);
		strcpy(node->work, w);
		strcpy(node->gender, g);
		node->link = NULL;

		if (p == NULL) {
			head = node;
			p = head;
		}
		else {
			p->link = node;
			p = p->link;
		}
	}

	fclose(f);

	return head;
}

void makeGenderList(listNode **maleList, listNode **femaleList, listNode *head) {
	listNode *p, *q, *r;
	p = *maleList;
	q = *femaleList;
	r = head;
	while (r != NULL) {
		if (!strcmp(r->gender, "남자")) {
			if (p == NULL) {
				*maleList = r;
				p = *maleList;
			}
			else {
				p->link = r;
				p = p->link;
			}
		}
		else {
			if (q == NULL) {
				*femaleList = r;
				q = *femaleList;
			}
			else {
				q->link = r;
				q = q->link;

			}
		}
		r = r->link;
	}
	p->link = NULL;
	q->link = NULL;
}

void printData(listNode *head) {
	listNode *p;
	p = head;
	while (p != NULL) {
		printf("(%p, %s, %s, %s, %p )  ", p, p->name, p->work, p->gender, p->link);
		p = p->link;
	}
}