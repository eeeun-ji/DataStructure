#include<stdio.h>
#include<stdlib.h>
#include <malloc.h>
typedef int element; // �׸��� ����
typedef struct ListNode {
	element data; // �迭 ���� 
	struct ListNode* link; // ���� ����Ʈ�� ����� �׸���� ���� 
}ListNode;

// ���� ó�� �Լ� 
void error(char* message) {
	fprintf(stderr, "%s\n", message);
	//exit(1);
}

ListNode* delete_pos(ListNode* head, int pos);
ListNode* insert_first(ListNode* head, int value)//item �� ����Ʈ�� ù��° �׸� �߰��Ѵ� 
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

ListNode* insert_next(ListNode* head, ListNode* pre, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode)); //(1) 
	p->data = value; //(2) 
	p->link = pre->link; //(3) 
	pre->link = p; //(4) 
	return head; //(5)
}

ListNode* insert_last(ListNode* head, int value) {
	ListNode* temp = head;
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = NULL;

	if (head == NULL)
		head = p;
	else {
		while (temp->link != NULL)
			temp = temp->link;
		temp->link = p;
	}
	return head;
}

ListNode* insert(ListNode* head, ListNode* pre, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link;
	pre->link = p;
	return head;
}

ListNode* delete_first(ListNode* head) {
	ListNode* removed;
	if (head == NULL) printf("������ �׸��� ����.");
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

ListNode* delete_next(ListNode* head, ListNode* pre) {
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);
	return head;
}

ListNode* delete_last(ListNode* head) {
	ListNode* temp = head;
	ListNode* prevTemp = NULL;
	ListNode* removed;

	if (head == NULL) printf("������ �׸��� ����");

	if (head->link == NULL) { // �ϳ��� ��� 
		free(temp);
		head = NULL;
	}
	else { // �� �̻��� ���
		while (temp->link != NULL) {
			prevTemp = temp;
			temp = temp->link;
		}
		prevTemp->link = NULL;

		return head; // �״�� 
	}
}

void print_list(ListNode* head) {
	ListNode* p;
	for (p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("NULL\n");
}

//���Ǿ�
ListNode* search(ListNode* head, int x) {
	ListNode* p;
	p = head;
	while (p != NULL) {
		if (p->data == x) return p; // Ž�� ���� p = p->link;
	}
	return NULL; // Ž�� ������ ��� NULL ��ȯ
}

ListNode* concat(ListNode* head1, ListNode* head2) {
	ListNode* p;
	if (head1 == NULL) return head2;
	else if (head2 == NULL) return head1;
	else {
		p = head1;
		while (p->link != NULL) p = p->link;
		p->link = head2;
		return head1;
	}
}

ListNode* reverse(ListNode* head) { // ��ȸ �����ͷ� p, q, r�� ��� 
	ListNode* p, * q, * r;
	p = head; // p�� �������� ���� ����Ʈ
	q = NULL; // q�� �������� ���� ��� 
	while (p != NULL) {
		r = q; // r�� �������� �� ����Ʈ. r�� q, q�� p�� ���ʷ� ���󰣴�.
		q = p;
		p = p->link;
		q->link = r; // q�� ��ũ ������ �ٲ۴�.
	}
	return q; // q�� �������� �� ����Ʈ�� ��� ������
}

//item�� ����Ʈ�� ������ 1 �� �ƴϸ� 0�� ��ȯ
int is_in_list(ListNode* head, element item) {
	ListNode* p;
	p = head;
	while (p != NULL) {
		if (p->data == item)
			return 1;
		p = p->link;
	}
	return 0;
}

//�ܼ����Ḯ��Ʈ�� �����ϴ� ����� ���� ��ȯ
int get_length(ListNode* head) {
	int len = 0;
	ListNode* p;

	p = head;
	while (p != NULL) {
		p = p->link;
		len++;
	}
	return len;
}

//�ܼ����Ḯ��Ʈ�� ��� ������ ���� ���� ���� ��ȯ
int get_total(ListNode* head) {
	int total = 0;
	ListNode* p;

	p = head;
	while (p != NULL) {
		total += p->data;
		p = p->link;
	}

	return total;
}

//pos ��ġ(0�� ù��° ��忡) �ִ� ����� data�� ��ȯ
// 
element get_entry(ListNode* head, int pos) {
	int i;
	if (pos >= 0 && pos < get_length(head)) { //�̹����� �������־����.
		for (i = 0; i < pos; i++)
			head = head->link;
	}
	else {
		printf("�߸��� pos");

	}
	return head->data;
}

ListNode* delete_by_key(ListNode* head, int key) {
	ListNode* p;
	int index = 0;

	p = head;
	while (p != NULL) {
		if (key == p->data) {
			p = delete_pos(head, index);
			return p;
		}
		index++;
		p = p->link;
	}
}


ListNode* insert_pos(ListNode* head, int pos, element value) {
	ListNode* p;
	int index = 0;

	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));

	p = head;
	while (index != pos - 1) {
		index++;
		p = p->link;
	}

	newNode->data = value;
	newNode->link = p->link;
	p->link = newNode;

	return head;

	//���⼭ pos 0 ���ְ� head�� NULL�϶��� ���ư��� ������, -> �ȵǳ�
	//���躸������ �����ϰ� !!�����ϱ� !!!
	//�ٿ���� �׽�Ʈ
	//1) ����ְ� pos = 0
	//2) ������� �ʰ� pos = 0 , �߰�, ����
}
ListNode* delete_pos(ListNode* head, int pos) {
	ListNode *temp = head;
	ListNode *prevTemp = NULL;
	ListNode *removed;
	int index = 0;

	if (temp->link == NULL)
		error("������ �׸��� ����");

	if (temp->link == NULL)
		delete_first(head);
	else {
		while (index != pos) {
			index++;
			prevTemp = temp;
			temp = temp->link;
		}
		removed = temp;
		prevTemp->link = NULL;
		free(removed);

		return head;
	}
}

int main(void) {
	ListNode* list1 = NULL;
	ListNode* list2 = NULL;
	ListNode* list3;

	list1 = insert_first(list1, 10);
	list1 = insert_first(list1, 20);
	list1 = insert_first(list1, 30);

	printf("list1 = ");
	print_list(list1);

	//list1�� �� �� ��带 �����Ѵ� ��, list1 = 20->30->
	delete_last(list1);

	// list1�� ���
	printf("list1 = ");
	print_list(list1);

	//list2 = 11->22->33->44->�� �����. �̶� 11, 22, 33, 44�� ������ ��带 �����Ѵ�.
	list2 = insert_last(list2, 11);
	list2 = insert_last(list2, 22);
	list2 = insert_last(list2, 33);
	list2 = insert_last(list2, 44);

	// list2�� ���
	printf("list2 = ");
	print_list(list2);

	// list2�� �� �� ��带 �����Ѵ�. ��, list2 = 11->22->33->
	delete_last(list2);

	// list2�� ���
	printf("list2 = ");
	print_list(list2);

	//list2�� �������� �ٲ� ����Ʈ�� list3�� ����Ű�� �Ѵ�. list3 = 33->22->11->�� �����.
	list3 = reverse(list2);
	//list3�� ����Ѵ�.
	printf("list3 = ");
	print_list(list3);

	// list1 = 20->30->33->22->11->�� �����. ��, list1�� list3�� ���ļ� list1�� ����Ű�� �Ѵ�.
	list1 = concat(list1, list3);

	//list1�� ����Ѵ�.
	printf("list1 = ");
	print_list(list1);

	//(A) ����: ���⼭���ʹ� list1�� ����Ͽ� �Լ����� �׽�Ʈ���� 
}