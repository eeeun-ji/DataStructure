#include<stdio.h>
#include <stdlib.h>
#define MAX_LIST_SIZE 100 // 리스트의 최대크기

//수정했음 돌아간다. !!

typedef int element; // 항목의 정의
typedef struct { 
	element array[MAX_LIST_SIZE]; // 배열 정의 
	int size; // 현재 리스트에 저장된 항목들의 개수 
} ArrayListType;

// 오류 처리 함수 
void error(char *message) { 
	fprintf(stderr, "%s\n", message);
	//exit(1);
}

// 리스트 초기화 함수 
void init(ArrayListType *L) {
	L-> size = 0;
}

// 리스트가 비어 있으면 1을 반환 
// 그렇지 않으면 0을 반환 
int is_empty(ArrayListType *L) {
	return L->size == 0;
}

// 리스트가 가득 차 있으면 1을 반환 
// 그렇지 많으면 1을 반환 
int is_full(ArrayListType *L) {
	return L->size == MAX_LIST_SIZE;
}

element get_entry(ArrayListType *L, int pos){
	if(pos < 0 || pos >= L->size)
		printf("위치 오류");
	return L->array[pos];
}

// 리스트 출력 
void print_list(ArrayListType *L) { 
	int i;
	for (i = 0; i<L->size; i++) 
		printf("%d->", L->array[i]);
	printf("리스트끝\n");
} 

void insert_last(ArrayListType *L, element item) { 
	if( L->size >= MAX_LIST_SIZE ) { 
		printf("리스트 오버플로우");
	}
	L->array[L->size] = item;
	L->size++;
}

void insert(ArrayListType *L, int pos, element item) { 
	if (!is_full(L) && (pos >= 0 && pos <= L->size)){
		for(int i = (L->size - 1); i >= pos; i--) 
			L->array[i + 1]  = L->array[i];
		L->array[pos] = item;
		L->size++;
	}
}

element delete_by_key(ArrayListType *L, element key) { 
	int i, j;
	for(i = 0; i < L->size; i++)
		if(L->array[i] == key){
			for(j = i; j < L->size-1; j++) //이 for문 잘 볼것 !!
				L->array[j] = L->array[j+1];
			L->size--;
			return;
		}
	printf("삭제하려는 key값 %d는 리스트에 없습니다,\n", key);
}

void clear(ArrayListType *L)//리스트를 비운다 
{
	L->size = 0;
}

void insert_first(ArrayListType *L, element item)//item 을 리스트의 첫번째 항목에 추가한다 
{
	if(!is_full(L)){
		for(int i = (get_length(L) - 1); i >= 0; i--)
			L->array[i+1] = L->array[i];
		L->array[0] = item;
		L->size++;
	}
	else
		printf("리스트 오버플로우\n");
}

int get_length(ArrayListType *L) //리스트의 항목수를 반환한다
{
	return L->size;
}

void replace(ArrayListType *L, int pos, element item) //pos 번째 항목을 item 으로 바꾼다 
{
	if((pos >= 0) &&(pos < get_length(L)) )
		L->array[pos] = item;
	else 
		printf("위치 오류");
}

int is_in_list(ArrayListType *L, element item) //item 이 리스트에 있으면 1 을 아니면 0 을 반환 
{
	for(int i = 0; L->array[i]!=NULL;i++){ 
		if(L->array[i]==item){
			return 1;
		} 
	} return 0;
}

int main(void) 
{ 
	ArrayListType list1;

	init(&list1);
	insert(&list1, 0, 20);
	insert(&list1, 0, 10); print_list(&list1);
	clear(&list1); print_list(&list1);

	insert_last(&list1, 90); print_list(&list1);

	insert(&list1, 0, 30);
	insert(&list1, 0, 20);
	insert(&list1, 0, 10); print_list(&list1);

	delete_by_key(&list1, 2); print_list(&list1);

	printf("\n-이 이후는 HW1_1에서 추가한 함수들 테스트-\n");

	insert_first(&list1, 9); print_list(&list1);
	insert_last(&list1, 99); print_list(&list1);

	// 현재 리스트가 꽉 찬(크기 5개) 상태이므로 한 항목을 더 추가하면 "리스트 오버플로우"을 출력한다.
	insert_first(&list1, 1); print_list(&list1);

	printf("길이는 %d\n", get_length(&list1));
	printf("3번째 데이타는 %d\n", get_entry(&list1, 2));

	replace(&list1, 3, 40); print_list(&list1);
	printf("20은 리스트에 %s\n", is_in_list(&list1, 20) ? "있습니다" : "없습니다");
	printf("22는 리스트에 %s\n", is_in_list(&list1, 22) ? "있습니다" : "없습니다");

	delete_by_key(&list1, 20); print_list(&list1);
	delete_by_key(&list1, 22); print_list(&list1);
}