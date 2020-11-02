#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define TRUE 1
#define FALSE 0
#define MAX_TREE_SIZE 20	

typedef struct TreeNode {
	int key;
	struct TreeNode *left, *right;
} TreeNode;

TreeNode *search(TreeNode *node, int key) {
	if (node == NULL) return NULL;
	if (key == node->key)
		return node;
	else if (key < node->key)
		return search(node->left, key);
	else
		return search(node->right, key);
}
/*
//반복
TreeNode *search2(TreeNode *node, int key) {
	while (node != NULL) {
		if (key == node->key) return node;
		else if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}
	return NULL;
}*/

void insert_node(TreeNode **root, int key) {
	TreeNode *p, *t; //p는 부모노드, t는 현재노드
	TreeNode *n; //n은 새로운 노드

	t = *root;
	p = NULL;

	while (t != NULL) {
		if (t->key == key) return;
		p = t;
		if (key < t->key)
			t = t->left;
		else
			t = t->right;
	}
	n = (TreeNode *)malloc(sizeof(TreeNode));
	if (n == NULL) return;
	n->key = key;
	n->left = n->right = NULL;

	//부모노드 링크 연결
	if (p != NULL) {
		if (key < p->key)
			p->left = n;
		else
			p->right = n;
	}
	else //애초에 트리가 비어있으면
		*root = n;
}
void delete_node(TreeNode **root, int key) {
	TreeNode *p, *child, *succ, *succ_p, *t;

	p = NULL;
	t = *root;

	//key를 갖는 노드 t를 탐색, p는 t의 부모노드
	while (t != NULL && t->key != key) {
		p = t;
		t = (key < t->key) ? t->left : t->right;

	}

	//탐색이 종료된 시점에 t가 NULL이면 트리 안에 키 없음.
	if (t == NULL) {
		printf("key is not in the tree\n");
		return;
	}

	//첫 번째경우 : 단말노드인 경우
	if ((t->left == NULL) && (t->right = NULL)) {
		if (p != NULL) {
			//부모노드의 자식 필드를 NULL로 만든다.
			if (p->left == t)//부모를 자식과 연결
				p->left = NULL;
			else
				p->right = NULL;
		}
		else //만약 부모 노드가 NULL이면 삭제되는 노드가 루트
			*root = NULL;
	}

	//두번째 경우 : 하나의 자식만 가지는 경우
	else if ((t->left == NULL) || (t->right == NULL)) {
		child = (t->left != NULL) ? t->left : t->right;
		if (p != NULL) {
			if (p->left == t)
				p->left = child;
			else
				p->right = child;
		}
		else //만약 부모 노드가 NULL이면 삭제되는 노드가 루트
			*root = child;
	}

	//세번째 경우 : 두 개의 자식을 가지는 경우
	else {
		//오른쪽 서브트리에서 후계자를 찾는다.
		succ_p = t;
		succ = t->right;

		//후계자를 찾아서 계속 왼쪽으로 이동한다.
		while (succ->left != NULL) {
			succ_p = succ;
			succ = succ->left;
		}

		//후속자의 부모와 자식을 연결
		if (succ_p->left == succ)
			succ_p->left = succ->right;
		else
			succ_p->right = succ->right;

		//후속자가 가진 키값을 현재 노드에 복사
		t->key = succ->key;
		//원래의 후속자 삭제
		t = succ;
	}
	free(t);
}
void preorder(TreeNode *root) // p271 코드 복사
{
	if (root) {
		printf("%d ", root->key);
		preorder(root->left);
		preorder(root->right);
	}
}

int get_node_count(TreeNode *node) {
	int count = 0;
	if (node != NULL)
		count = 1 + get_node_count(node->left) + get_node_count(node->right);
	return count;
}

int get_height(TreeNode *node) {
	int height = 0;
	if (node != NULL)
		height = 1 + max(get_height(node->left), get_height(node->right));
	return height;
}

int get_maximum(TreeNode *node) {
	while (node->right != NULL) {
		node = node->right;
	}
	return node->key;
}
int get_minimum(TreeNode *node) {
	while (node->left != NULL) {
		node = node->left;
	}
	return node->key;
}
int main(void) {
	char command;
	int num;
	TreeNode *root = NULL;
	TreeNode *tmp;

	do {
		printf("Enter i(nsert), d(elete), s(earch), p(rint), h(eight), c(ount), m(ax), n(min), q(uit): ");
		scanf("%c", &command);
		getchar();
		switch(command) {
			case 'i':
				printf("삽입할 key값 입력: ");
				scanf("%d", &num);
				insert_node(&root, num);
				getchar();
				break;
			case 'd' :
				printf("삭제할 key값 입력: ");
				scanf("%d", &num);
				delete_node(&root, num);
				getchar();
				break;
			case 's':
				printf("탐색할 key값 입력: ");
				scanf("%d", &num);
				if (search(root, num) != NULL)
					printf("있음.\n");
				else			
					printf("없음.\n");
				getchar();
				break;
			case 'p':
				preorder(root);
				printf("\n");
				break;
			case 'h':
				printf("트리의 높이는 %d\n", get_height(root));
				break;
			case 'c':
				printf("노드의 개수는 %d\n", get_node_count(root));
				break;
			case 'm':
				printf("가장 큰 값은 %d\n", get_maximum(root));
				break;
			case 'n':
				printf("가장 작은 값은 %d\n", get_minimum(root));
				break;
		}
	} while (command != 'q');
}