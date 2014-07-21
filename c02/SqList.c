#include <stdio.h>
#include <stdlib.h>

typedef int Status;
#define OK 1
#define ERROR 0

#define LIST_INIT_SIZE 10
#define LIST_INCREMENT 5

typedef struct
{
	int *elem;
	int length;
	int listsize;
}SqList;

Status InitList_Sq(SqList *L)
{
	L->elem = (int *)malloc(LIST_INIT_SIZE * sizeof(int));
	if(!L->elem) return ERROR;

	L->length = 0;
	L->listsize = LIST_INIT_SIZE;

	return OK;
}

Status ListInsert_Sq(SqList *L, int i, int e)
{
	if(i < 1 || i > L->length + 1) return ERROR;

	if(L->length >= L->listsize)
	{
		int *newbase = (int *)realloc(L->elem, (L->listsize + LIST_INCREMENT) * sizeof(int));
		if(!newbase) return ERROR;
		L->elem = newbase;
		L->listsize += LIST_INCREMENT;
	}

	int *q = &(L->elem[i-1]);
	int *p = &(L->elem[L->length-1]);
	for(; p >= q; --p)	*(p+1) = *p;

	*q = e;
	++L->length;

	return OK;
}

Status ListDelete_Sq(SqList *L, int i, int *e)
{
	if(i < 1 || i > L->length) return ERROR;

	int *p = &(L->elem[i-1]);
	*e = *p;

	int *q = &(L->elem[L->length-1]);
	for(++p; p <= q; ++p)
	{
		*(p-1) = *p;
	}
	--L->length;

	return OK;
}

void ListPrint_Sq(SqList *L)
{
	int *p = L->elem;
	int *q = L->elem + L->length - 1;
	for(; p <= q; ++p) printf("%d ", *p);
	printf("\n");
}

int main(int argc, char *argv[])
{
	SqList list;
	SqList *L = &list;
	
	InitList_Sq(L);

	int i;
	for(i = 1; i <= 20; i++)
	{
		ListInsert_Sq(L, i, i);
	}

	int e;
	ListDelete_Sq(L, 10, &e);

	ListPrint_Sq(L);

	return 0;
}
