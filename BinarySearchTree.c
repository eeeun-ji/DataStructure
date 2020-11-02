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
//�ݺ�
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
	TreeNode *p, *t; //p�� �θ���, t�� ������
	TreeNode *n; //n�� ���ο� ���

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

	//�θ��� ��ũ ����
	if (p != NULL) {
		if (key < p->key)
			p->left = n;
		else
			p->right = n;
	}
	else //���ʿ� Ʈ���� ���������
		*root = n;
}
void delete_node(TreeNode **root, int key) {
	TreeNode *p, *child, *succ, *succ_p, *t;

	p = NULL;
	t = *root;

	//key�� ���� ��� t�� Ž��, p�� t�� �θ���
	while (t != NULL && t->key != key) {
		p = t;
		t = (key < t->key) ? t->left : t->right;

	}

	//Ž���� ����� ������ t�� NULL�̸� Ʈ�� �ȿ� Ű ����.
	if (t == NULL) {
		printf("key is not in the tree\n");
		return;
	}

	//ù ��°��� : �ܸ������ ���
	if ((t->left == NULL) && (t->right = NULL)) {
		if (p != NULL) {
			//�θ����� �ڽ� �ʵ带 NULL�� �����.
			if (p->left == t)//�θ� �ڽİ� ����
				p->left = NULL;
			else
				p->right = NULL;
		}
		else //���� �θ� ��尡 NULL�̸� �����Ǵ� ��尡 ��Ʈ
			*root = NULL;
	}

	//�ι�° ��� : �ϳ��� �ڽĸ� ������ ���
	else if ((t->left == NULL) || (t->right == NULL)) {
		child = (t->left != NULL) ? t->left : t->right;
		if (p != NULL) {
			if (p->left == t)
				p->left = child;
			else
				p->right = child;
		}
		else //���� �θ� ��尡 NULL�̸� �����Ǵ� ��尡 ��Ʈ
			*root = child;
	}

	//����° ��� : �� ���� �ڽ��� ������ ���
	else {
		//������ ����Ʈ������ �İ��ڸ� ã�´�.
		succ_p = t;
		succ = t->right;

		//�İ��ڸ� ã�Ƽ� ��� �������� �̵��Ѵ�.
		while (succ->left != NULL) {
			succ_p = succ;
			succ = succ->left;
		}

		//�ļ����� �θ�� �ڽ��� ����
		if (succ_p->left == succ)
			succ_p->left = succ->right;
		else
			succ_p->right = succ->right;

		//�ļ��ڰ� ���� Ű���� ���� ��忡 ����
		t->key = succ->key;
		//������ �ļ��� ����
		t = succ;
	}
	free(t);
}
void preorder(TreeNode *root) // p271 �ڵ� ����
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
				printf("������ key�� �Է�: ");
				scanf("%d", &num);
				insert_node(&root, num);
				getchar();
				break;
			case 'd' :
				printf("������ key�� �Է�: ");
				scanf("%d", &num);
				delete_node(&root, num);
				getchar();
				break;
			case 's':
				printf("Ž���� key�� �Է�: ");
				scanf("%d", &num);
				if (search(root, num) != NULL)
					printf("����.\n");
				else			
					printf("����.\n");
				getchar();
				break;
			case 'p':
				preorder(root);
				printf("\n");
				break;
			case 'h':
				printf("Ʈ���� ���̴� %d\n", get_height(root));
				break;
			case 'c':
				printf("����� ������ %d\n", get_node_count(root));
				break;
			case 'm':
				printf("���� ū ���� %d\n", get_maximum(root));
				break;
			case 'n':
				printf("���� ���� ���� %d\n", get_minimum(root));
				break;
		}
	} while (command != 'q');
}