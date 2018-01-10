//------	Last Date : 01/10/2018 17:30	------//
//------	GitHub: www.GitHub.com/LinuxGu	------//

//------	Copyrigth (C) GuYongZeng - GuYz	------//
//------				 GPL~				------//

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

typedef struct T_LNode{
	ElemType	data;	// 用户自行定义元素类型的数据域
	struct T_LNode* next;
} LinkList;

typedef struct {
	int length;
	struct LinkList* next;
} LinkHead;

Status init_LinkList(LinkHead**  p);
	// 初始化单链表头节点
int get_LinkList_len(LinkHead*  L);
	// 获取链表长度


Status init_LinkList(LinkHead**  p)
	// 初始化单链表头节点
{
	LinkHead* linkhead;

	*p = (LinkHead* )malloc(sizeof(LinkHead)); // 对上层指针重定位
	if(!*p) return ERROR;

	linkhead = *p;
	linkhead->length = 0;
	linkhead->next = NULL;
	return OK;
} // init_linklist

int get_LinkList_len(LinkHead* L)
	// 获取链表长度
{
	return L->length;
}// get_LinkList_len

LinkList* get_LinkList_addre(LinkHead* L, int i)
	// 返回L中地i个元素的地址
{
	int j;
	LinkList *p = (LinkList *) L->next;

	if(i == 0) return p;

	if(i > L->length) return ERROR;

	for(j = 1; j < i; j++)
	{
		if(p->next == NULL)
			break;
		p = p->next;	
	}
	return p;
}// get_LinkList_adder

Status insert_LinkList(LinkHead* L, int i, ElemType e)
	// 在第i位置插入元素e
{
	LinkList* pn; // 指向新元素的指针
	LinkList* p;	// 指向第i个元素的前驱

	int len = get_LinkList_len(L);
	if(len < 0 || i <= 0)	return ERROR;

	pn = (LinkList* )malloc(sizeof(LinkList));
	if(!pn) return ERROR;
	pn->next = NULL;
	
	if(i == 1)
	{
		 L->next = pn;
		 L->length++;
		 return OK;
	}

	p = get_LinkList_addre(L, i-1); // 取得第i-1个元素的指针
	pn->next = p->next;	// 令新元素的next指向第i个元素的后继
	p->next = pn;			// 令第i个元素指向新元素
	pn->data = e;
	L->length++;

	return OK;
}// insert_LinkList

Status get_LinkList(LinkHead *  L, int i, ElemType* e)
	// 在单链表L中用e返回第i个元素
{
	if(i > L->length) ERROR;

	LinkList* p = get_LinkList_addre(L, i);
	if(!p) return ERROR;
	*e = p->data;

	return OK;
}// get_LinkList

Status destroy_LinkList(LinkHead *L)
	// 销毁单链表
{
	LinkList *p = (LinkList*) L->next;

	if(!p)	return ERROR;	

	while(p->next != NULL)
	{
		p = p->next;
		free(p);
	}
	L->next = NULL;
	L->length = 0;
	return OK;
}// destroy_LinkList

Status delete_LinkList(LinkHead *  L, int i, ElemType* e)
// 删除单链表L中第i个元素，并用e返回
{
	int len = get_LinkList_len(L);
	if(len < i) return ERROR;

	LinkList *  p = get_LinkList_addre(L, i-1);
	LinkList *  q = NULL; // 指向待删除元素

	q = p->next;
	p->next = p->next->next;
	*e = q->data;
	free(q);
	return OK;
}// delete_LinkList

LinkList *  locate_list_L(LinkHead* L, ElemType e,
		Status (*cmp)(ElemType e1, ElemType e2))
	// 在L中用"ElemType.h"中提供的cmp函数比较哪一个元素与e相等,
	// 并返回它的地址
	// cmp()应在对比成功是返回1
{
	if(!cmp) return ERROR;

	LinkList* p = (LinkList *) L->next;

	while(!cmp(p->data, e))
	{
		p = p->next;	
		if(!p) break;
	}
	return p;
}

#endif
