#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct treeNode *treePointer;
typedef struct treeNode {
	int l_thread;
	treePointer left;
	int data;
	treePointer right;
	int r_thread;
}treeNode;

treePointer insucc(treePointer node) {
	treePointer temp;
	temp = node->right;
	if (!(node->r_thread)) {
		while (!(temp->l_thread)) {
			temp = temp->left;
		}
	}
	return temp;
}

void tinorder(treePointer head) {
	treePointer temp = head;

	while (!temp->l_thread) {
		temp = temp->left;
	}
	printf("(%p, %3d, %3d, %3d, %p) ", temp->left, temp->l_thread, temp->data, temp->r_thread, temp->right);
	
	for (;;) {
		temp = insucc(temp);
		if (temp == head) {
			break;
		}
		printf("(%p, %3d, %3d, %3d, %p) ", temp->left, temp->l_thread, temp->data, temp->r_thread, temp->right);
	}
}

int main(int argc, char *argv[]) {
	
	treeNode n1 = { FALSE, NULL, 10, NULL, FALSE };
	treeNode n2 = { FALSE, NULL, 20, NULL, FALSE };
	treeNode n3 = { FALSE, NULL, 30, NULL, FALSE };
	treeNode n4 = { FALSE, NULL, 40, NULL, FALSE };
	treeNode n5 = { TRUE, NULL, 50, NULL, TRUE};
	treeNode n6 = { TRUE, NULL, 60, NULL, TRUE};
	treeNode n7 = { TRUE, NULL, 70, NULL, TRUE};
	treeNode n8 = { TRUE, NULL, 80, NULL, TRUE};
	treeNode n9 = { TRUE, NULL, 90, NULL, TRUE};

	treeNode head = { FALSE, &n1, -999, &head, TRUE};

	n1.left = &n2;
	n1.right = &n3;

	n2.left = &n4;
	n2.right = &n5;

	n3.left = &n6;
	n3.right = &n7;

	n4.left = &n8;
	n4.right = &n9;

	n5.left = &n3;
	n5.right = &n1;

	n6.left = &n1;
	n6.right = &n3;

	n7.left = &n3;
	n7.right = &head;

	n8.left = &head;
	n8.right = &n4;

	n9.left = &n4;
	n9.right = &n2;

	printf("head node : (%p, %3d, %3d, %3d, %p)\n", head.left, head.l_thread, head.data, head.r_thread, head.right);
	tinorder(&head);

	return 0;
}