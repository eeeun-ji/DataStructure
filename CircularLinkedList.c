#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { 	// ��� Ÿ��
	element data;
	struct ListNode* link;
} ListNode;

// ����Ʈ�� �׸� ���
void print_list(ListNode* head)
{
	ListNode* p;

	if (head == NULL) {
		return; //��尡 1��
	}

	p = head->link;
	while (p != head) {
		printf("%d->", p->data);
		p = p->link;
	}

	printf("%d->", p->data); // ������ ��� ���
	printf("����Ʈ�� ��\n");

}

ListNode* insert_first(ListNode* head, element data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = node;
	}
	else {
		node->link = head->link;	// (1)
		head->link = node;		// (2)
	}
	return head;	// ����� ��� �����͸� ��ȯ�Ѵ�. 
}


ListNode* insert_last(ListNode* head, element data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link;	// (1)
		head->link = node;		// (2)
		head = node;		// (3)
	}
	return head;	// ����� ��� �����͸� ��ȯ�Ѵ�. 
}

ListNode* delete_first(ListNode* head)
{
	ListNode* temp;
	if (head == NULL) {
		printf("����Ʈ�� ��� ������ ����\n");
		return NULL;
	}

	else if (head == head->link) {  // �� �ϳ��� ��尡 �������� 
		temp = head;
		head = NULL;
		free(temp);
	}
	else {
		temp = head->link;
		head->link = temp->link;
		free(temp);
	}
	return head;

}


//������
ListNode* delete_last(ListNode* head)
{
	ListNode* removed;
	ListNode* pre;

	if (head == NULL){
		printf("����Ʈ�� ��� ������ ����\n");
		return NULL;
	} else if (head == head->link) {
		removed = head;
		head = NULL;
	}
	else {
		pre = head->link;
		while(head != pre->link)
			pre = pre->link;
		removed = head;
		pre->link = removed->link;
		head = pre;
	}
	free(removed);
	return head;
}

ListNode* search(ListNode* head, element data)
{
	ListNode* cur = head;
	int i = 0;
		while (cur != head) {
			if (cur->data == data)
				printf("%d��° ��忡 %d�� �ִ�.", i, data);
			i++;
			cur = cur->link;
		}
	return head;

	//head�� null�϶��� üũ�� �ؾ��Ѵ�.
}

int get_size(ListNode* head)
{
	ListNode* p;
	int cnt = 0;
	if (head == NULL) return 0;
	p = head->link;
	do {
		cnt++;
		p = p->link;
	} while (p != head);
	return cnt;
}

// ���� ���� ����Ʈ �׽�Ʈ ���α׷�
int main(void)
{
	ListNode* head = NULL;

	// list = 10->20->30->40
	head = insert_last(head, 20);
	print_list(head);

	head = insert_last(head, 30);
	print_list(head);

	head = insert_last(head, 40);
	print_list(head);

	head = insert_first(head, 10);
	print_list(head);


	printf("ù��° ����\n");
	head = delete_first(head);
	print_list(head);

	printf("������ ����\n");
	head = delete_last(head);
	print_list(head);

	printf("����Ʈ�� ���̴� = %d\n", get_size(head));
	printf("data�� ������ �ִ� ù��° ���� %d�̴� \n", search(head, 20));


	return 0;
}
