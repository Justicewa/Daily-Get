#include "SList.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//初始化链表
void SListInit(SList* s){
	assert(s);
	s->pHead = NULL;
}

//创建一个新结点,返回值是一个PNode型的结构体
PNode CreateNewNode(SDataType data){
	PNode pNewNode = (PNode)malloc(sizeof(Node));
	if (pNewNode == NULL){
		return NULL;
	}
	pNewNode->data = data;
	pNewNode->pNext = NULL;
	
	return pNewNode;
}

//尾插
//创建一个结点
//如果链表为空,直接令其为头结点
//
void SListPushBack(SList* s, SDataType data){
	assert(s);
	PNode pNewNode = CreateNewNode(data);
	if (s->pHead == NULL){
		s->pHead = pNewNode;
	}
	else{
		PNode pCur = s->pHead;
		while (pCur->pNext){
			pCur = pCur->pNext;
		}
		pCur->pNext = pNewNode;
	}
}

//尾删
//如果链表为空,直接返回
//如果不为空,但头结点的下一个结点为空,此时释放头结点
//如果不为空,新创建一个pPreNode用来存放倒数第二个结点,为了防止它乱指
void SListPopBack(SList* s){
	assert(s);
	if (s->pHead == NULL){
		return;
	}
	else if (s->pHead->pNext == NULL){
		free(s->pHead);
		s->pHead = NULL;
	}
	else{
		PNode pPreNode = NULL;
		PNode pCur = s->pHead;
		while (pCur->pNext){
			pPreNode = pCur;
			pCur = pCur->pNext;
		}
		free(pCur);
		pPreNode->pNext = NULL;
	}
}

void PrintSList(SList* s){
	assert(s);
	PNode pCur = s->pHead;
	while (pCur){
		printf("%d--->", pCur->data);
		pCur = pCur->pNext;
	}
	printf("NULL\n");
}

//头插
void SListPushFront(SList* s, SDataType data){
	assert(s);
	PNode pNewNode = CreateNewNode(data);
	if (s->pHead == NULL){
		s->pHead = pNewNode;
	}
	else{
		pNewNode->pNext = s->pHead;
		s->pHead = pNewNode;
	}

}

//头删
void SListPopFront(SList* s){
	assert(s);
	PNode pDelNode = NULL;
	if (s->pHead == NULL){
		return;
	}
	else{
		pDelNode = s->pHead;
		s->pHead = pDelNode->pNext;
	}
	free(pDelNode);

}

//中间插入结点
//找到位置:在主函数中调用find函数找到pos
//先用新结点指向 pos->next 再将 pPre->next 指向新结点
void SListInsert(PNode pos, SDataType data){
	PNode pNewNode = CreateNewNode(data);
	if (pos == NULL){
		return;
	}
	pNewNode->pNext = pos->pNext;
	pos->pNext = pNewNode;

}

void SListErase(SList* s, PNode pos);

//如果链表为空,返回NULL,因为返回值是结构体类型
//建立pCur遍历数组
//找到了元素,返回pCur,没找到就返回NULL
PNode SListFind(SList* s, SDataType data){
	assert(s);
	if (s->pHead == NULL){
		return NULL;
	}
	PNode pCur = s->pHead;
	while (pCur){
		if (pCur->data == data){
			return pCur;
		}
		pCur = pCur->pNext;
	}
	return NULL;
}

int SListSize(SList* s){
	size_t count = 0;
	PNode pCur = s->pHead;
	while (pCur){
		pCur = pCur->pNext;
		count++;
	}
	return count;
}

int SListEmpty(SList* s){
	assert(s);
	return s->pHead == NULL;
}

/*
	1.如果链表为空,直接返回
	2.若链表不为空,遍历整个链表且数据找到
		1)要找的数据是头结点,直接用它的next覆盖它
		2)如果不是头结点,建立一个pPreNode用来存放所遍历的结点的上一个结点,之后使用删除结点的方式移除
	3.链表不为空,数据不对,继续遍历
*/
void SListRemove(SList* s, SDataType data){
	assert(s);
	if (s->pHead == NULL){
		return;
	}
	PNode pPreNode = NULL;
	PNode pCur = s->pHead;
	while (pCur){
		if (pCur->data == data){
			if (pCur == s->pHead){
				s->pHead = s->pHead->pNext;
			}
			else{
				pPreNode->pNext = pCur->pNext;
			}
			free(pCur);
		
		}
		else{
			pPreNode = pCur;
			pCur = pCur->pNext;
		}
	}

}

void SListRemoveAll(SList* s, SDataType data);

void TestSList(){
	SList s; //头结点
	SList* p = NULL;
	SListInit(&s);
	SListPushBack(&s, 1);
	SListPushBack(&s, 2);
	SListPushBack(&s, 3);
	SListPushBack(&s, 4);
	SListPushBack(&s, 5);
	SListPushBack(&s, 6);

	printf("链表大小是%d\n",SListSize(&s));

	
	PrintSList(&s);
}