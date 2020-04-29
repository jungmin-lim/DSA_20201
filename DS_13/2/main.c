#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treenode *treePointer;
typedef struct stacknode *stackPointer;
typedef struct queuenode *queuePointer;
typedef struct treenode{
	char data;
	treePointer leftChild, rightChild;
}treenode;
typedef struct stacknode {
	treePointer node;
	stackPointer link;
}stacknode;
typedef struct queuenode {
	treePointer node;
	queuePointer link;
}queuenode;

void push(stackPointer *head, treePointer node);
treePointer pop(stackPointer *head);
void enqueue(queuePointer *queue, treePointer node);
treePointer dequeue(queuePointer *queue);
int isOperand(char dat);
treePointer makeTree();
void deleteTree(treePointer root);
void iterInorder(treePointer node);
void levelOrder(treePointer node);

int main(int argc, char *argv[]) {
	FILE *f;
	treePointer root = NULL;
	char input[80];

	f = fopen("input.txt", "r");
	fscanf(f, "%s", input);

	printf("the length of input string should be less than 80\n");
	printf("input sting (postfix expression : %s\n", input);

	printf("creating binary tree\n");
	root = makeTree();

	printf("\niterative inorder traversal	: ");
	iterInorder(root);
	printf("\nlevel order traversal	: ");
	levelOrder(root);

	printf("\n\n");
	deleteTree(root);
	root = NULL;

	fclose(f);
	return 0;
}

void push(stackPointer *head, treePointer node) {
	stackPointer newStacknode;
	if((newStacknode = (stackPointer)malloc(sizeof(*newStacknode))) == NULL){
		fprintf(stderr, "Insufficient memory");
		exit(EXIT_FAILURE);
	}
	newStacknode->node = node;
	newStacknode->link = (*head);

	(*head) = newStacknode;
	return;
}

treePointer pop(stackPointer *head) {
	treePointer ret;
	stackPointer temp;
	if (!(*head)) {
		return NULL;
	}

	temp = (*head);
	(*head) = (*head)->link;

	ret = temp->node;
	free(temp);

	return ret;
}

void enqueue(queuePointer *queue, treePointer node) {
	queuePointer newQueuenode, p = (*queue);
	if ((newQueuenode = (queuePointer)malloc(sizeof(*newQueuenode))) == NULL) {
		fprintf(stderr, "Insufficient memory");
		exit(EXIT_FAILURE);
	}
	newQueuenode->node = node;
	if (!(*queue)) {
		newQueuenode->link = newQueuenode;
		(*queue) = newQueuenode;
		return;
	}

	while(p->link != (*queue)){
		p = p->link;
	}

	p->link = newQueuenode;
	newQueuenode->link = (*queue);
	return;
}

treePointer dequeue(queuePointer *queue) {
	queuePointer p, q;
	treePointer ret;
	if (!(*queue)) {
		return NULL;
	}

	p = (*queue);
	q = (*queue);
	while (q->link != (*queue)) {
		q = q->link;
	}

	(*queue) = (*queue)->link;
	if (p == (*queue)) {
		(*queue) = NULL;
	}
	else {
		q->link = (*queue);
	}

	ret = p->node;
	free(p);
	return ret;
}

int isOperand(char dat) {
	if ((dat >= 'A' && dat <= 'Z') || (dat >= 'a' && dat <= 'z')) {
		return 1;
	}
	return 0;
}

treePointer makeTree() {
	FILE *f;
	treePointer newTreenode = NULL;
	stackPointer stack = NULL;
	char dat;
	
	f = fopen("input.txt", "r");
	while (fscanf(f, "%c", &dat) != EOF) {
		if (isOperand(dat)) {
			if ((newTreenode = (treePointer)malloc(sizeof(*newTreenode))) == NULL) {
				fprintf(stderr, "Insufficient memory");
				exit(EXIT_FAILURE);
			}
			newTreenode->data = dat;
			newTreenode->leftChild = NULL;
			newTreenode->rightChild = NULL;
			push(&stack, newTreenode);
		}
		else {
			if ((newTreenode = (treePointer)malloc(sizeof(*newTreenode))) == NULL) {
				fprintf(stderr, "Insufficient memory");
				exit(EXIT_FAILURE);
			}
			newTreenode->data = dat;
			newTreenode->rightChild = pop(&stack);
			newTreenode->leftChild = pop(&stack);
			push(&stack, newTreenode);
		}
	}

	fclose(f);
	return newTreenode;
}

void deleteTree(treePointer root) {
	if (root) {
		deleteTree(root->leftChild);
		deleteTree(root->rightChild);
		free(root);
	}
}

void iterInorder(treePointer node) {
	stackPointer stack = NULL;
	for (;;) {
		for (; node; node = node->leftChild) {
			push(&stack, node);
		}
		node = pop(&stack);
		if (!node) break;
		printf("%c", node->data);
		node = node->rightChild;
	}
	return;
}

void levelOrder(treePointer node) {
	queuePointer queue = NULL;
	if (!node) {
		return;
	}

	enqueue(&queue, node);
	for (;;) {
		node = dequeue(&queue);
		if (node) {
			printf("%c", node->data);
			if (node->leftChild) {
				enqueue(&queue, node->leftChild);
			}
			if (node->rightChild) {
				enqueue(&queue, node->rightChild);
			}
		}
		else {
			break;
		}
	}
	return;
}