//------	Last Date : 12/23/2017 19:44	------//
//------	GitHub: www.GitHub.com/LinuxGu	------//

//------	Copyrigth (C) GuYongZeng - GuYz	------//
//------				 GPL~				------//

#ifndef	_SQSTACK_H
#define	_SQSTACK_H

#include <stdlib.h>
#include <stdio.h>
#include "ElemType.h"
//	用户制定ElemType

#define TRUE	1
#define FALSE	0
#define OK		1
#define ERROR	0
#define INFEASIBLE	-1	// 不可行
#define OVERFLOW	-2	// 溢出
// Status 函数类型，值是函数结果状态代码
typedef int Status;


#define STACK_INIT_SIZE 100	// 栈存储空间初始分配量
#define STACKINCREMENT 10	// 栈存储空间分配增量

typedef struct {
	ElemType* base;	// 栈底
	ElemType* top;	// 栈顶指针
	int		stacksize; // 当前可用最大容量
} SqStack;

Status init_stack(SqStack *S);
// 初始化栈S
Status destroy_stack(SqStack *S);
// 销毁栈S
Status cleal_stack(SqStack *S);
// 清空栈S

Status Push(SqStack *S, ElemType e);
// 在S栈顶插入元素e
Status Pop(SqStack *S,  ElemType* e);	
// 在S栈删除栈顶并用e返回,弹栈
int get_stack_len(SqStack *S);
// 返回栈S的长读
Status get_stack_top(SqStack *S, ElemType *e);
// 用e返回栈S的栈顶元素
Status stack_empty(SqStack *S);
// 判断是否为空栈，如果是，返回TRUE


int get_stack_len(SqStack *S)
{
	if(!(S->base && S->top)) return INFEASIBLE;

	return S->top - S->base;
}// get_stack_len

Status stack_empty(SqStack *S)
	// 判断栈是否为空，则返回TRUE，否则返回FALSE
{
	if(!(S->base || S->top)) return INFEASIBLE;

	if(S->base == S->top) return TRUE;
	else return FALSE;
}// stack_empty

Status init_stack(SqStack *S)
	// 初始化 S栈,构造一个空的栈S
{
	S->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
	// if(!S->base) exit(OVERFLOW);	// 分配失败
	printf("test\n");
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;

	return OK;
} // init_stack

Status destroy_stack(SqStack *S)
	// 销毁栈
{
	free(S->base);	
	S->stacksize = 0;
	if(!S->base) return OK;
	return ERROR;
}

Status cleal_stack(SqStack *S)
	// 清空栈S
{
	if(stack_empty(S)) return OVERFLOW; 
	int i;

	for(i=0; i < get_stack_len(S); i++)
		S->base[i] = NULL_ELEM;
	return OK;
}

Status get_stack_top(SqStack *S, ElemType *e)
	// 用e返回S栈栈顶
{
	*e = *(S->top - 1);
	return OK;
}

Status Push(SqStack *S, ElemType e)
	// 入栈 
{
	ElemType* newbase = NULL;

	if(get_stack_len(S) >= S->stacksize)
	{
		newbase = (ElemType*)realloc(S->base,
				(S->stacksize + STACKINCREMENT) * sizeof(ElemType));
		if(!newbase) exit(OVERFLOW);
		S->base = newbase;
		S->stacksize += STACKINCREMENT;
	}else{
		*S->top = e;
		S->top++;
	}
	return OK;	
}

Status Pop(SqStack *S, ElemType *e)
	// 弹栈，删除栈顶元素并用e返回该元素
{
	if(stack_empty(S)) return INFEASIBLE;
	
	*e = *--S->top;

	return OK;
}

#endif
