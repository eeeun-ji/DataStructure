#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { 	// 노드 타입
	element data;
	struct ListNode* link;
} ListNode;

// 리스트의 항목 출력
void print_list(ListNode* head)
{
	ListNode* p;

	if (head == NULL) {
		return; //노드가 1개
	}

	p = head->link;
	while (p != head) {
		printf("%d->", p->data);
		p = p->link;
	}

	printf("%d->", p->data); // 마지막 노드 출력
	printf("리스트의 끝\n");

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
	return head;	// 변경된 헤드 포인터를 반환한다. 
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
	return head;	// 변경된 헤드 포인터를 반환한다. 
}

ListNode* delete_first(ListNode* head)
{
	ListNode* temp;
	if (head == NULL) {
		printf("리스트가 비어 삭제를 못함\n");
		return NULL;
	}

	else if (head == head->link) {  // 즉 하나의 노드가 남았을때 
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


//수정함
ListNode* delete_last(ListNode* head)
{
	ListNode* removed;
	ListNode* pre;

	if (head == NULL){
		printf("리스트가 비어 삭제를 못함\n");
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
				printf("%d번째 노드에 %d가 있다.", i, data);
			i++;
			cur = cur->link;
		}
	return head;

	//head가 null일때도 체크를 해야한다.
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

// 원형 연결 리스트 테스트 프로그램
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


	printf("첫번째 삭제\n");
	head = delete_first(head);
	print_list(head);

	printf("마지막 삭제\n");
	head = delete_last(head);
	print_list(head);

	printf("리스트의 길이는 = %d\n", get_size(head));
	printf("data를 가지고 있는 첫번째 노드는 %d이다 \n", search(head, 20));


	return 0;
}
