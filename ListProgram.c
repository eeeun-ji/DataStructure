#include<stdio.h>
#include<stdlib.h>
#include <malloc.h>
typedef int element; // 항목의 정의
typedef struct ListNode {
	element data; // 배열 정의 
	struct ListNode* link; // 현재 리스트에 저장된 항목들의 개수 
}ListNode;

// 오류 처리 함수 
void error(char* message) {
	fprintf(stderr, "%s\n", message);
	//exit(1);
}

ListNode* delete_pos(ListNode* head, int pos);
ListNode* insert_first(ListNode* head, int value)//item 을 리스트의 첫번째 항목에 추가한다 
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
	if (head == NULL) printf("삭제할 항목이 없음.");
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

	if (head == NULL) printf("삭제할 항목이 없음");

	if (head->link == NULL) { // 하나의 노드 
		free(temp);
		head = NULL;
	}
	else { // 둘 이상의 노드
		while (temp->link != NULL) {
			prevTemp = temp;
			temp = temp->link;
		}
		prevTemp->link = NULL;

		return head; // 그대로 
	}
}

void print_list(ListNode* head) {
	ListNode* p;
	for (p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("NULL\n");
}

//강의안
ListNode* search(ListNode* head, int x) {
	ListNode* p;
	p = head;
	while (p != NULL) {
		if (p->data == x) return p; // 탐색 성공 p = p->link;
	}
	return NULL; // 탐색 실패일 경우 NULL 반환
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

ListNode* reverse(ListNode* head) { // 순회 포인터로 p, q, r을 사용 
	ListNode* p, * q, * r;
	p = head; // p는 역순으로 만들 리스트
	q = NULL; // q는 역순으로 만들 노드 
	while (p != NULL) {
		r = q; // r은 역순으로 된 리스트. r은 q, q는 p를 차례로 따라간다.
		q = p;
		p = p->link;
		q->link = r; // q의 링크 방향을 바꾼다.
	}
	return q; // q는 역순으로 된 리스트의 헤드 포인터
}

//item이 리스트에 있으면 1 을 아니면 0을 반환
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

//단순연결리스트에 존재하는 노드의 수를 반환
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

//단순연결리스트의 모든 데이터 값을 더한 합을 반환
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

//pos 위치(0이 첫번째 노드에) 있는 노드의 data를 반환
// 
element get_entry(ListNode* head, int pos) {
	int i;
	if (pos >= 0 && pos < get_length(head)) { //이범위를 잡을수있어야함.
		for (i = 0; i < pos; i++)
			head = head->link;
	}
	else {
		printf("잘못된 pos");

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

	//여기서 pos 0 을주고 head가 NULL일때도 돌아가나 봐야함, -> 안되네
	//시험보기전에 적절하게 !!수정하기 !!!
	//바운더리 테스트
	//1) 비어있고 pos = 0
	//2) 비어있지 않고 pos = 0 , 중간, 길이
}
ListNode* delete_pos(ListNode* head, int pos) {
	ListNode *temp = head;
	ListNode *prevTemp = NULL;
	ListNode *removed;
	int index = 0;

	if (temp->link == NULL)
		error("삭제할 항목이 없음");

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

	//list1의 맨 앞 노드를 삭제한다 즉, list1 = 20->30->
	delete_last(list1);

	// list1을 출력
	printf("list1 = ");
	print_list(list1);

	//list2 = 11->22->33->44->를 만든다. 이때 11, 22, 33, 44의 순으로 노드를 삽입한다.
	list2 = insert_last(list2, 11);
	list2 = insert_last(list2, 22);
	list2 = insert_last(list2, 33);
	list2 = insert_last(list2, 44);

	// list2를 출력
	printf("list2 = ");
	print_list(list2);

	// list2의 맨 뒤 노드를 삭제한다. 즉, list2 = 11->22->33->
	delete_last(list2);

	// list2를 출력
	printf("list2 = ");
	print_list(list2);

	//list2를 역순으로 바꾼 리스트를 list3가 가리키게 한다. list3 = 33->22->11->를 만든다.
	list3 = reverse(list2);
	//list3를 출력한다.
	printf("list3 = ");
	print_list(list3);

	// list1 = 20->30->33->22->11->를 만든다. 즉, list1과 list3를 합쳐서 list1이 가리키게 한다.
	list1 = concat(list1, list3);

	//list1을 출력한다.
	printf("list1 = ");
	print_list(list1);

	//(A) 주의: 여기서부터는 list1만 사용하여 함수들을 테스트하자 
}