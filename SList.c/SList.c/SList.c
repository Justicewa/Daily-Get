#include "SList.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//��ʼ������
void SListInit(SList* s){
	assert(s);
	s->pHead = NULL;
}

//����һ���½��,����ֵ��һ��PNode�͵Ľṹ��
PNode CreateNewNode(SDataType data){
	PNode pNewNode = (PNode)malloc(sizeof(Node));
	if (pNewNode == NULL){
		return NULL;
	}
	pNewNode->data = data;
	pNewNode->pNext = NULL;
	
	return pNewNode;
}

//β��
//����һ�����
//�������Ϊ��,ֱ������Ϊͷ���
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

//βɾ
//�������Ϊ��,ֱ�ӷ���
//�����Ϊ��,��ͷ������һ�����Ϊ��,��ʱ�ͷ�ͷ���
//�����Ϊ��,�´���һ��pPreNode������ŵ����ڶ������,Ϊ�˷�ֹ����ָ
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

//ͷ��
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

//ͷɾ
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

//�м������
//�ҵ�λ��:���������е���find�����ҵ�pos
//�����½��ָ�� pos->next �ٽ� pPre->next ָ���½��
void SListInsert(PNode pos, SDataType data){
	PNode pNewNode = CreateNewNode(data);
	if (pos == NULL){
		return;
	}
	pNewNode->pNext = pos->pNext;
	pos->pNext = pNewNode;

}

void SListErase(SList* s, PNode pos);

//�������Ϊ��,����NULL,��Ϊ����ֵ�ǽṹ������
//����pCur��������
//�ҵ���Ԫ��,����pCur,û�ҵ��ͷ���NULL
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
	1.�������Ϊ��,ֱ�ӷ���
	2.������Ϊ��,�������������������ҵ�
		1)Ҫ�ҵ�������ͷ���,ֱ��������next������
		2)�������ͷ���,����һ��pPreNode��������������Ľ�����һ�����,֮��ʹ��ɾ�����ķ�ʽ�Ƴ�
	3.����Ϊ��,���ݲ���,��������
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
	SList s; //ͷ���
	SList* p = NULL;
	SListInit(&s);
	SListPushBack(&s, 1);
	SListPushBack(&s, 2);
	SListPushBack(&s, 3);
	SListPushBack(&s, 4);
	SListPushBack(&s, 5);
	SListPushBack(&s, 6);

	printf("�����С��%d\n",SListSize(&s));

	
	PrintSList(&s);
}