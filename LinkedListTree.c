#include <stdio.h> 
#include <stdlib.h> 
#include <memory.h> 
#define TRUE 1 
#define FALSE 0 
#define MAX_TREE_SIZE 20
int count = 0;
typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

TreeNode n1 = { 15, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 15, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode* root = &n6;
TreeNode m1 = { 15, NULL, NULL };
TreeNode m2 = { 4, &n1, NULL };
TreeNode m3 = { 16, NULL, NULL };
TreeNode m7 = { 28, NULL, NULL }; // �߰�
TreeNode m4 = { 25, NULL, &m7 }; // ���� 
TreeNode m5 = { 15, &m3, &m4 };
TreeNode m6 = { 15, &m2, &m5 };
TreeNode* root2 = &m6;

//p281 Quiz 01
int get_nonleaf_count(TreeNode* t) {
	//return get_oneleaf_count(t) + get_twoleaf_count(t);
	int count = 0;
	if (t == NULL) return 0;
	else {
		if (t->left == NULL && t->right == NULL)
			return 0;
		else
			count = get_nonleaf_count(t->left) + get_nonleaf_count(t->right) + 1;
	}
}

//p281 Quiz 02
int equal(TreeNode* t1, TreeNode* t2) {
	if (t1->data != t2->data)
		return FALSE;
	if ((t1 == NULL) || (t2 == NULL))
		return FALSE;
	else if ((t1 == NULL) && (t2 == NULL))
		return TRUE;
	return ((t1->data == t2->data) && equal(t1->left, t2->left) && equal(t1->right, t2->right));

}

//p308 #25
int get_oneleaf_count(TreeNode* node) {
	if (node == NULL)
		return 0;
	else if (node->left == NULL && node->right == NULL)
		return 0;
	else if (node->left == NULL)
		return 1 + get_oneleaf_count(node->right);
	else if (node->right == NULL)
		return 1 + get_oneleaf_count(node->left);
	else
		return get_oneleaf_count(node->left) + get_oneleaf_count(node->right);
}

//p308 #26
int get_twoleaf_count(TreeNode* node) {
	if (node == NULL)
		return 0;
	else if (node->left == NULL && node->right == NULL)
		return 0;
	else if (node->left == NULL)
		return get_twoleaf_count(node->right);
	else if (node->right == NULL)
		return get_twoleaf_count(node->left);
	else
		return get_twoleaf_count(node->left) + get_twoleaf_count(node->right);
}

//p308 #27 // �̷������� �ߴ�.
int get_max(TreeNode* node) {
	if (node)
		return max(max(node->data, get_max(node->left)), get_max(node->right));
	else
		return INT_MIN;
}

int get_min(TreeNode* node) {
	if (node)
		return min(min(node->data, get_max(node->left)), get_max(node->right));
	else
		return INT_MAX;
}

//p308 #30
void node_increase(TreeNode* node) {
	if (node) {
		printf("%d  ", ++(node->data));
		node_increase(node->left);
		node_increase(node->right);
	}
	else return;
}

//������ȸ
void preorder(TreeNode* root) // p271 �ڵ� ����
{
	if (root) {
		printf("%d  ", root->data); // ��� �湮
		preorder(root->left); // ���ʼ���Ʈ�� ��ȸ
		preorder(root->right); // �����ʼ���Ʈ�� ��ȸ
	}
}

TreeNode* copy(TreeNode* t) {
	TreeNode* temp;
	if (t == NULL)
		return NULL;
	else {
		temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->left = copy(t->left);
		temp->right = copy(t->right);
		temp->data = t->data;
		return temp;
	}

}
int main(void) {
	TreeNode* result[MAX_TREE_SIZE];
	TreeNode* clone;
	int i, num;
	printf("��)\n");
	printf("Ʈ�� root �� ��ܸ������ ������ %d.\n", get_nonleaf_count(root));
	printf("Ʈ�� root2 �� ��ܸ������ ������ %d.\n", get_nonleaf_count(root2));
	printf("Ʈ�� root �� �ڽ��� �ϳ��� �ִ� ����� ������ %d.\n", get_oneleaf_count(root));
	printf("Ʈ�� root2 �� �ڽ��� �ϳ��� �ִ� ����� ������ %d.\n", get_oneleaf_count(root2));
	printf("Ʈ�� root �� �ڽ��� ���� �ִ� ����� ������ %d.\n", get_twoleaf_count(root));
	printf("Ʈ�� root2 �� �ڽ��� ���� �ִ� ����� ������ %d.\n", get_twoleaf_count(root2));
	printf("Ʈ�� root ���� ���� ū ���� %d.\n", get_max(root));
	printf("Ʈ�� root2 ���� ���� ū ���� %d.\n", get_max(root2));
	printf("Ʈ�� root ���� ���� ���� ���� %d.\n", get_min(root));
	printf("Ʈ�� root2 ���� ���� ���� ���� %d.\n", get_min(root2));
	printf("\n ��)\n");
	//num = search(root, 15, result);
	//for (i = 0; i < num; i++) printf("(0x%p, %d), ", result[i], result[i]->data);
	printf("\n");
	printf("\n ��)\n");
	preorder(root);
	printf("\n1�� ���� Ʈ��\n");
	node_increase(root);
	printf("\n");

	printf("\n");
	printf("%s\n", equal(root, root) ? "����" : "�ٸ���");
	printf("%s\n", equal(root2, root2) ? "����" : "�ٸ���");
	printf("%s\n", equal(root, root2) ? "����" : "�ٸ���");
	printf("\n ��)\n");
	clone = copy(root);
	preorder(root);
	printf("\n");
	preorder(clone);
	printf("\n");
}