#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treenode *treePointer;
typedef struct stacknode *stackPointer;
typedef struct treenode{
	char data;
	treePointer leftChild, rightChild;
}treenode;
typedef struct stacknode {
	treePointer node;
	stackPointer link;
}stacknode;

void push(stackPointer *head, treePointer node);
treePointer pop(stackPointer *head);
int isOperand(char dat);
treePointer makeTree();
void deleteTree(treePointer root);
void inorder(treePointer node);
void preorder(treePointer node);
void postorder(treePointer node);

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

	printf("\ninorder traversal	: ");
	inorder(root);
	printf("\npreorder traversal	: ");
	preorder(root);
	printf("\npostorder traversal	: ");
	postorder(root);

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

void inorder(treePointer node) {
	if (node) {
		inorder(node->leftChild);
		printf("%c", node->data);
		inorder(node->rightChild);
	}
}

void preorder(treePointer node) {
	if (node) {
		printf("%c", node->data);
		preorder(node->leftChild);
		preorder(node->rightChild);
	}
}

void postorder(treePointer node) {
	if (node) {
		postorder(node->leftChild);
		postorder(node->rightChild);
		printf("%c", node->data);
	}
}
