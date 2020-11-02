#include<stdio.h>
#include <stdlib.h>
#define MAX_LIST_SIZE 100 // ����Ʈ�� �ִ�ũ��

//�������� ���ư���. !!

typedef int element; // �׸��� ����
typedef struct { 
	element array[MAX_LIST_SIZE]; // �迭 ���� 
	int size; // ���� ����Ʈ�� ����� �׸���� ���� 
} ArrayListType;

// ���� ó�� �Լ� 
void error(char *message) { 
	fprintf(stderr, "%s\n", message);
	//exit(1);
}

// ����Ʈ �ʱ�ȭ �Լ� 
void init(ArrayListType *L) {
	L-> size = 0;
}

// ����Ʈ�� ��� ������ 1�� ��ȯ 
// �׷��� ������ 0�� ��ȯ 
int is_empty(ArrayListType *L) {
	return L->size == 0;
}

// ����Ʈ�� ���� �� ������ 1�� ��ȯ 
// �׷��� ������ 1�� ��ȯ 
int is_full(ArrayListType *L) {
	return L->size == MAX_LIST_SIZE;
}

element get_entry(ArrayListType *L, int pos){
	if(pos < 0 || pos >= L->size)
		printf("��ġ ����");
	return L->array[pos];
}

// ����Ʈ ��� 
void print_list(ArrayListType *L) { 
	int i;
	for (i = 0; i<L->size; i++) 
		printf("%d->", L->array[i]);
	printf("����Ʈ��\n");
} 

void insert_last(ArrayListType *L, element item) { 
	if( L->size >= MAX_LIST_SIZE ) { 
		printf("����Ʈ �����÷ο�");
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
			for(j = i; j < L->size-1; j++) //�� for�� �� ���� !!
				L->array[j] = L->array[j+1];
			L->size--;
			return;
		}
	printf("�����Ϸ��� key�� %d�� ����Ʈ�� �����ϴ�,\n", key);
}

void clear(ArrayListType *L)//����Ʈ�� ���� 
{
	L->size = 0;
}

void insert_first(ArrayListType *L, element item)//item �� ����Ʈ�� ù��° �׸� �߰��Ѵ� 
{
	if(!is_full(L)){
		for(int i = (get_length(L) - 1); i >= 0; i--)
			L->array[i+1] = L->array[i];
		L->array[0] = item;
		L->size++;
	}
	else
		printf("����Ʈ �����÷ο�\n");
}

int get_length(ArrayListType *L) //����Ʈ�� �׸���� ��ȯ�Ѵ�
{
	return L->size;
}

void replace(ArrayListType *L, int pos, element item) //pos ��° �׸��� item ���� �ٲ۴� 
{
	if((pos >= 0) &&(pos < get_length(L)) )
		L->array[pos] = item;
	else 
		printf("��ġ ����");
}

int is_in_list(ArrayListType *L, element item) //item �� ����Ʈ�� ������ 1 �� �ƴϸ� 0 �� ��ȯ 
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

	printf("\n-�� ���Ĵ� HW1_1���� �߰��� �Լ��� �׽�Ʈ-\n");

	insert_first(&list1, 9); print_list(&list1);
	insert_last(&list1, 99); print_list(&list1);

	// ���� ����Ʈ�� �� ��(ũ�� 5��) �����̹Ƿ� �� �׸��� �� �߰��ϸ� "����Ʈ �����÷ο�"�� ����Ѵ�.
	insert_first(&list1, 1); print_list(&list1);

	printf("���̴� %d\n", get_length(&list1));
	printf("3��° ����Ÿ�� %d\n", get_entry(&list1, 2));

	replace(&list1, 3, 40); print_list(&list1);
	printf("20�� ����Ʈ�� %s\n", is_in_list(&list1, 20) ? "�ֽ��ϴ�" : "�����ϴ�");
	printf("22�� ����Ʈ�� %s\n", is_in_list(&list1, 22) ? "�ֽ��ϴ�" : "�����ϴ�");

	delete_by_key(&list1, 20); print_list(&list1);
	delete_by_key(&list1, 22); print_list(&list1);
}