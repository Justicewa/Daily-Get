#pragma once

typedef int SDataType;

typedef struct SListNode{
	SDataType data;
	struct SListNode* pNext;
}Node, *PNode;

typedef struct SList{
	PNode pHead;
}SList, *PSList;

void SListInit(SList* s);
void SListPushBack(SList* s, SDataType data);
void SListPopBack(SList* s);
void SListPushFront(SList* s, SDataType data);
void SListPopFront(SList* s);
void SListInsert(PNode pos, SDataType data);
void SListErase(SList* s, PNode pos);
PNode SListFind(SList* s, SDataType data);
int SListSize(SList* s);
int SListEmpty(SList* s);
void SListRemove(SList* s, SDataType data);
void SListRemoveAll(SList* s, SDataType data);



void TestSList(); 
