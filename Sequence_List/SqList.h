#ifndef	_SQLIST_H
#define	_SQLIST_H

#include <stdlib.h>
#include <stdio.h>
#include "ElemType.h"
//	用户制定ElemType

#define TURE	1
#define FALSE	0
#define OK		1
#define ERROR	0
#define INFEASIBLE	-1	// 不可行
#define OVERFLOW	-2	// 溢出
// Status 函数类型，值是函数结果状态代码
typedef int Status;


#define LIST_INIT_SIZE 100	// 线性表存储空间初始分配量
#define LISTINCREMENT 10	// 线性表存储空间分配增量

typedef struct {
	ElemType	*elem;	// 基地址,用户自行定义元素类型
	int		length;		// 当前长度
	int		listsize;	// 当前分配的存储容量，sizeof(ElemType)
} SqList;

Status init_Sqlist(SqList *sqlist);	// 初始化顺序表
Status destroy_Sqlist(SqList *sqlist);	// 销毁顺序表
Status insert_Sqlist(SqList *sqlist, int n, ElemType e);	// 在第n位置插入元素e
Status delete_Sqlist(SqList *sqlist, int n, ElemType* e);	
// 在i位置删除e并用e返回
Status get_Sqlist(SqList *sqlist, int n, ElemType* e);	// 用e返回第n位置的元素
int locate_Sqlist(SqList *sqlist, ElemType e,
		Status (*cmp)(ElemType p, ElemType e));	
// 查找第一个与e相等的元素的位序并返回位序,若未找到返回0
void merge_Sqlist(SqList *La, SqList *Lb, SqList *Lc);
// 归并递增序列La 和 Lb 得到递增序列Lc

Status init_Sqlist(SqList *sqlist)
	// 初始化 sqlist顺序表,构造一个空的sqlist
{
	sqlist->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if(sqlist->elem == NULL) exit(OVERFLOW);	// 分配失败
	sqlist->length = 0;
	sqlist->listsize = LIST_INIT_SIZE;
	return OK;
} // init_Sqlist

Status destroy_Sqlist(SqList *sqlist)
// 销毁顺序表
{
	free(sqlist->elem);	
	sqlist->length = 0;
	sqlist->listsize = 0;
	return OK;
}

Status insert_Sqlist(SqList *sqlist, int n, ElemType e)
	//在sqlist中第n位置插入e元素
{
	int j;
	int i = n-1;
	ElemType* newbase = NULL;

	if(n < 1) return ERROR;

	if(sqlist->length >= sqlist->listsize)
	{
		newbase =(ElemType*) realloc(sqlist->elem,
				(sqlist->listsize + LISTINCREMENT)	* sizeof(ElemType)); 
		if(newbase == NULL) exit(OVERFLOW);

		sqlist->elem = newbase;
		sqlist->listsize += LISTINCREMENT;
	}

	for(j = sqlist->length-1; j>=i; j--)
	{
		sqlist->elem[j+1] = sqlist->elem[j];
	}
	sqlist->elem[i] = e;
	sqlist->length++;
	return OK;
}// insert_Sqlist

Status delete_Sqlist(SqList *sqlist, int n, ElemType *e)
	//删除第n个元素，并用e返回其值
{
	int i = n-1;
	if(sqlist == NULL || n > sqlist->length) return ERROR;

	*e = sqlist->elem[i];

	for(; i < sqlist->length-1; i++)
	{
		sqlist->elem[i] = sqlist->elem[i+1];
	}
	sqlist->length--;
	return OK;
}// delete_Sqlist

int locate_Sqlist(SqList* sqlist, ElemType e,
	Status (*cmp)(ElemType p, ElemType e))
	// 查找第一个与e相等的元素的位置并返回（0<i<=length),若未找到返回0
{
	int i;
	ElemType p;

	for(i = 0; cmp(p, e) == FALSE; i++) p = sqlist->elem[i];
	//cmp在比较成功返回TURE
	if(i >= sqlist->length) return ERROR;
	return i+1;
}

Status get_Sqlist(SqList *sqlist, int n, ElemType* e)
	// 用e返回第i个元素
{
	int i = n-1;
	if(n < 1 || n > sqlist->length) return OVERFLOW;

	*e =  sqlist->elem[i];
	return OK;
}// get_Sqlist

void merge_Sqlist(SqList *La, SqList *Lb, SqList *Lc)
	// 归并递增序列La,Lb得到Lc
{
	int i, j;
	int k = 1;	// insert_Sqlist是按位置插入的
	ElemType e;

	if(La == NULL || Lb == NULL) exit(ERROR);
	for(i=0 ,j=0; i < La->length && j < Lb->length; )
	{
		if(La->elem[i].data < Lb->elem[j].data)
		{
			insert_Sqlist(Lc, k, La->elem[i]);
			k++;
			i++;
		}else{
			insert_Sqlist(Lc, k, Lb->elem[j]);
			k++;
			j++; 
		} // if
	}// for
	if(La->length == i) 
		for( ;j < Lb->length; j++, k++)
			insert_Sqlist(Lc, k, Lb->elem[j]);
	else
		for( ;i < La->length; i++, k++)
			insert_Sqlist(Lc, k, La->elem[i]);
	return ;
}//	merge_Sqlist

#endif
