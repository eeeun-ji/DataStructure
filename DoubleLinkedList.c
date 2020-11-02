#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DListNode {	// ���߿��� ��� Ÿ��
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
} DListNode;

// ���� ���� ����Ʈ�� �ʱ�ȭ
void init(DListNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

// ���� ���� ����Ʈ�� ��带 ���
void print_dlist(DListNode* phead)
{
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("<-| |%d| |-> ", p->data);
	}
	printf("\n");
}
// ���ο� �����͸� ��� before�� �����ʿ� �����Ѵ�.
void dinsert(DListNode* before, element data)
{
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	newnode->data = data;

	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}
// ��� removed�� �����Ѵ�.
void ddelete(DListNode* head, DListNode* removed)
{
	if (removed == head) return;

	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}

DListNode* print_reverse_dlist(DListNode* head) {
	//�������� ��ȸ�ϸ鼭 ����� ������ ���� ���

	
	DListNode* p;
	for(p = head->llink; p != head; p = p->llink)
		printf("<-| |%d| |->", p->data);
	printf("\n");
}

DListNode* search(DListNode* head, element data) {
	//data�� ���� ��带 ã�Ƽ� ��ȯ�Ѵ�.

	DListNode* p;
	for(p = head->rlink; p != head; p = p->rlink){
		if(p->data == data)
			return p;
	}
	return NULL;
}

// ���� ���� ����Ʈ �׽�Ʈ ���α׷�
int main(void)
{
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	init(head);
	printf("�߰� �ܰ�\n");

	// ó���� ����
	dinsert(head, 10);
	print_dlist(head);
	dinsert(head, 20);
	print_dlist(head);
	dinsert(head, 30);
	print_dlist(head);

	// �ڿ� �����Ϸ���?
	dinsert(head->llink, 99);
	print_dlist(head);

	printf("\n���� �ܰ�\n");
	// �տ����� ���� 
	ddelete(head, head->rlink);
	print_dlist(head);

	// �ڿ����� ���� 
	ddelete(head, head->llink);
	print_dlist(head);

	printf("���� ���\n");
	print_reverse_dlist(head);
	print_dlist(head);

	search(head, 10);

	free(head);
	return 0;
}