#include<stdio.h>
#include<malloc.h>
#define MAX_STACK_SIZE 3
#define MAX_STRING 100

//hw2_2_2.c

typedef struct {
	int num;
	char numString[MAX_STRING];
}element;

typedef struct {
	element data;
	struct StackNode* link;
}StackNode;

typedef struct {
	StackNode* top;
}LinkedStackType;

void init(LinkedStackType* s) {
	s->top = NULL;
}
int is_empty(LinkedStackType* s) {
	return (s->top == NULL);
}
int is_full(LinkedStackType* s) {
	return 0;
}
void push(LinkedStackType* s, element item) {
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	if (temp == NULL)
		printf("메모리 할당 에러 \n");
	else {
		temp->data = item;
		temp->link = s->top;
		s->top = temp;
	}
}
element pop(LinkedStackType* s) {
	if (is_empty(s)) {
		printf("스택이 비어있음\n");
	}
	else {
		StackNode* temp = s->top;
		element data = temp->data;
		s->top = s->top->link;
		free(temp);
		return data;
	}
}
element peek(LinkedStackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
	}
	else return s->top->data;
}
void stack_print(LinkedStackType* s) {
	int i, j;
	if (is_empty(s)) {
		printf("(empty)\n--\n");
	}
	else {
		for (StackNode* p = s->top; p != NULL; p = p->link)
		{
			printf("[[%d, %s]", p->data.num, p->data.numString);
			if (p == s->top)
				printf("<- top");
			printf("\n");
		}
	}
	printf("--\n");
}
void main(void) {
	LinkedStackType s;
	element e;

	init(&s); stack_print(&s);
	
	e.num = 10;
	strcpy(e.numString, "ten");
	push(&s, e);
	stack_print(&s);

	e.num = 20;
	strcpy(e.numString, "twenty");
	push(&s, e);
	stack_print(&s);
}