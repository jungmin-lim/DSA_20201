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
listNode *makeMaleList(listNode *maleList, listNode *head);
listNode *makeFemaleList(listNode *femaleList, listNode *head);
void printData(listNode *head);

int main(int argc, char *argv[]) {
	listNode *linkedList = NULL;
	listNode *maleList = NULL;
	listNode *femaleList = NULL;

	linkedList = makeList(linkedList);
	printf("전체 리스트\n");
	printData(linkedList);
	printf("\n\n");

	maleList = makeMaleList(maleList, linkedList);
	printf("남자 리스트\n");
	printData(maleList);
	printf("\n\n");
	
	femaleList = makeFemaleList(femaleList, linkedList);
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

	return head;
}

listNode *makeMaleList(listNode *maleList, listNode *head) {
	listNode *p, *q, *node;
	p = maleList;
	q = head;
	while (q != NULL) {
		if (!strcmp(q->gender, "남자")) {
			if ((node = (listNode *)malloc(sizeof(*node))) == NULL) {
				fprintf(stderr, "Insufficient Memory");
				exit(EXIT_FAILURE);
			}
			strcpy(node->name, q->name);
			strcpy(node->work, q->work);
			strcpy(node->gender, q->gender);
			node->link = NULL;

			if (p == NULL) {
				maleList = node;
				p = maleList;
			}
			else {
				p->link = node;
				p = p->link;
			}
		}

		q = q->link;
	}

	return maleList;
}

listNode *makeFemaleList(listNode *femaleList, listNode *head) {
	listNode *p, *q, *node;
	p = femaleList;
	q = head;
	while (q != NULL) {
		if (!strcmp(q->gender, "여자")) {
			if ((node = (listNode *)malloc(sizeof(*node))) == NULL) {
				fprintf(stderr, "Insufficient Memory");
				exit(EXIT_FAILURE);
			}
			strcpy(node->name, q->name);
			strcpy(node->work, q->work);
			strcpy(node->gender, q->gender);
			node->link = NULL;

			if (p == NULL) {
				femaleList = node;
				p = femaleList;
			}
			else {
				p->link = node;
				p = p->link;
			}
		}

		q = q->link;
	}

	return femaleList;
}

void printData(listNode *head) {
	listNode *p;
	p = head;
	while (p != NULL) {
		printf("(%p, %s, %s, %s, %p )  ", p, p->name, p->work, p->gender, p->link);
		p = p->link;
	}
}