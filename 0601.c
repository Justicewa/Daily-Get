#include "SeqList.h"
#include <malloc.h>
#include <assert.h>
#include <stdio.h>

void SeqListInit(PSeq ps, int capacity)
{
	ps->_array = (DataType*)malloc(sizeof(DataType)*capacity);
	if (NULL == ps->_array)
	{
		assert(0);
		return;
	}

	ps->_capacity = capacity;
	ps->_size = 0;
}

void SeqListPushBack(PSeq ps, DataType data)
{
#if 0
	assert(ps);

	// 顺序表满
	// CheckCapacity(ps);

	ps->_array[ps->_size] = data;
	ps->_size++;
#endif

	SeqListInsert(ps, ps->_size, data);
}

void SeqListPopBack(PSeq ps)
{
#if 0
	assert(ps);
	if (SeqListEmpty(ps))
		return;

	ps->_size--;
#endif

	SeqListErase(ps, ps->_size - 1);
}

void SeqListPushFront(PSeq ps, DataType data)
{
#if 0
	assert(ps);
	// CheckCapacity(ps);

	// 将顺序表中所有的元素统一向后搬移一个位置
	for (int i = ps->_size - 1; i >= 0; i--)
	{
		ps->_array[i+1] = ps->_array[i];
	}

	// 插入元素
	ps->_array[0] = data;
	ps->_size++;
#endif

	SeqListInsert(ps, 0, data);
}

void SeqListPopFront(PSeq ps)
{
#if 0
	if (SeqListEmpty(ps))
		return;

	for (int i = 1; i < ps->_size; ++i)
		ps->_array[i-1] = ps->_array[i];

	ps->_size--;
#endif

	SeqListErase(ps, 0);
}

void SeqListInsert(PSeq ps, int pos, DataType data)
{
	assert(ps);
	if (pos < 0 || pos > ps->_size)
		return;

	CheckCapacity(ps);

	for (int i = ps->_size - 1; i >= pos; i--)
		ps->_array[i+1] = ps->_array[i];

	ps->_array[pos] = data;
	ps->_size++;
}

void SeqListErase(PSeq ps, int pos)
{
	assert(ps);
	if (pos < 0 || pos >= ps->_size)
		return;

	for (int i = pos + 1; i < ps->_size; ++i)
		ps->_array[i-1] = ps->_array[i];

	ps->_size--;
}

int SeqListFind(PSeq ps, DataType data)
{
	assert(ps);
	for (int i = 0; i < ps->_size; i++)
	{
		if (ps->_array[i] == data)
			return i;
	}

	return -1;
}


int SeqListSize(PSeq ps)
{
	assert(ps);
	return ps->_size;
}

int SeqListCapacity(PSeq ps)
{
	assert(ps);
	return ps->_capacity;
}

int SeqListEmpty(PSeq ps)
{
	assert(ps);
	return 0 == ps->_size;
}

void SeqListClear(PSeq ps)
{
	assert(ps);
	ps->_size = 0;
}

// 移除第一个值为data的元素
// 1  2  3   2   2  4   1  2   2
void SeqListRemove(PSeq ps, DataType data)
{
	SeqListErase(ps, SeqListFind(ps, data));
}

// 1  2  3   2   2  4   1  2   2
// 移除所有值为data的元素
void SeqListRemoveAll(PSeq ps, DataType data)
{
	assert(ps);
	int count = 0;
	for (int i = 0; i < ps->_size; ++i)
	{
		if (ps->_array[i] == data)
			count++;
		else
			ps->_array[i - count] = ps->_array[i];
	}

	ps->_size -= count;
	/*
	int pos = -1;
	while (-1 != (pos = SeqListFind(ps, data)))
	{
		SeqListErase(ps, pos);
	}
	*/


}

void SeqListDestroy(PSeq ps)
{
	if (ps->_array)
	{
		free(ps->_array);
		ps->_array = NULL;
		ps->_capacity = 0;
		ps->_size = 0;
	}
}

void CheckCapacity(PSeq ps)
{
	assert(ps);
	if (ps->_size == ps->_capacity)
	{
		// 顺序表中已经没有空间了
		int newCapacity = ps->_capacity * 2;

		// realloc(p, size)
		// 申请新空间
		int* pTemp = (DataType*)malloc(newCapacity*sizeof(DataType));
		if (NULL == pTemp)
		{
			assert(0);
			return;
		}

		// 拷贝元素 memcpy
		for (int i = 0; i < ps->_size; ++i)
			pTemp[i] = ps->_array[i];

		// 释放旧空间
		free(ps->_array);

		// 更新
		ps->_array = pTemp;
		ps->_capacity = newCapacity;
	}
}

void SeqListPrint(PSeq ps)
{
	for (int i = 0; i < ps->_size; ++i)
		printf("%d ", ps->_array[i]);
	printf("\n");
}


////////////////////////////////////////////
// 

void Swap(int* pLeft, int* pRight)
{
	int temp = *pLeft;
	*pLeft = *pRight;
	*pRight = temp;
}

void BubbleSort(PSeq ps)
{
	// N---->N-1
	for (int i = 0; i < ps->_size - 1; ++i) // 控制冒泡总的趟数
	{
		int Ischange = 0;
		// 冒泡的具体方式：将相邻的两个元素进行比较， 可能需要交换
		for (int j = 1; j < ps->_size - i; ++j)
		{
			if (ps->_array[j-1] > ps->_array[j])
			{
				Ischange = 1;
				Swap(&ps->_array[j-1], &ps->_array[j]);
			}
		}

		if (!Ischange)
			return;
	}
}

int BinarySearch(PSeq ps, DataType data);

void TestSeqList()
{
	SeqList s;
	int pos = -1;
	SeqListInit(&s, 10);
	SeqListPushBack(&s, 1);
	SeqListPushBack(&s, 2);
	SeqListPushBack(&s, 2);
	SeqListPushBack(&s, 4);
	SeqListPushBack(&s, 2);
	SeqListPushBack(&s, 6);
	SeqListPushBack(&s, 7);
	SeqListPushBack(&s, 2);
	SeqListPushBack(&s, 9);
	SeqListPushBack(&s, 2);
	printf("size = %d\n", SeqListSize(&s));
	printf("capacity = %d\n", SeqListCapacity(&s));
	SeqListPrint(&s);

	SeqListRemoveAll(&s, 2);
	SeqListPrint(&s);

	SeqListPushBack(&s, 1);
	printf("size = %d\n", SeqListSize(&s));
	printf("capacity = %d\n", SeqListCapacity(&s));
	SeqListPrint(&s);

	SeqListPopBack(&s);
	SeqListPrint(&s);

	SeqListPushFront(&s, 0);
	SeqListPrint(&s);

	SeqListPopFront(&s);
	SeqListPrint(&s);

	SeqListInsert(&s, 1, 5);
	SeqListPrint(&s);

	pos = SeqListFind(&s, 5);
	if (pos != -1)
		printf("5 is in %d!!!\n", pos);
	else
		printf("5 is not in %d!!!\n", pos);

	SeqListErase(&s, 1);

	pos = SeqListFind(&s, 5);
	if (pos != -1)
		printf("5 is in %d!!!\n", pos);
	else
		printf("5 is not in %d!!!\n", pos);

	SeqListPrint(&s);
	printf("size = %d\n", SeqListSize(&s));
	printf("capacity = %d\n", SeqListCapacity(&s));

	SeqListDestroy(&s);
}