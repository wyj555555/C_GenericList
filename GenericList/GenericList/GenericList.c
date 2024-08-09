#include "GenericList.h"

void GenericListInit(GENERIC_LIST* list)
{
    list->pstNext = list;
    list->pstPrev = list;
}

void GenericListAdd(GENERIC_LIST* list, GENERIC_LIST* node)
{
    node->pstNext = list->pstNext;
    node->pstPrev = list;
    list->pstNext->pstPrev = node;
    list->pstNext = node;
}

void GenericListTailInsert(GENERIC_LIST* list, GENERIC_LIST* node)
{
    GenericListAdd(list->pstPrev, node);
}

void GenericListHeadInsert(GENERIC_LIST* list, GENERIC_LIST* node)
{
    GenericListAdd(list, node);
}

void GenericListDelete(GENERIC_LIST* node)
{
    node->pstNext->pstPrev = node->pstPrev;
    node->pstPrev->pstNext = node->pstNext;
    node->pstNext = NULL;
    node->pstPrev = NULL;
}

bool GenericListEmpty(GENERIC_LIST* list)
{
    return (bool)(list->pstNext == list);
}

void GenericListAddList(GENERIC_LIST* oldList, GENERIC_LIST* newList)
{
    GENERIC_LIST* oldListHead = oldList->pstNext;
    GENERIC_LIST* oldListTail = oldList;
    GENERIC_LIST* newListHead = newList;
    GENERIC_LIST* newListTail = newList->pstPrev;

    oldListTail->pstNext = newListHead;
    newListHead->pstPrev = oldListTail;
    oldListHead->pstPrev = newListTail;
    newListTail->pstNext = oldListHead;
}

void GenericListTailInsertList(GENERIC_LIST* oldList, GENERIC_LIST* newList)
{
    GenericListAddList(oldList->pstPrev, newList);
}

void GenericListHeadInsertList(GENERIC_LIST* oldList, GENERIC_LIST* newList)
{
    GenericListAddList(oldList, newList);
}

void GenericListDelInit(GENERIC_LIST* list)
{
    list->pstNext->pstPrev = list->pstPrev;
    list->pstPrev->pstNext = list->pstNext;
    GenericListInit(list);
}

size_t GenericListLength(const GENERIC_LIST* list) {
    size_t length = 0;
    const GENERIC_LIST* item;
    GENERIC_DL_LIST_FOR_EACH(item, list) {
        length++;
    }
    return length;
}

// ��������ڵ��е��ֶν��в��ҵĺ���
GENERIC_LIST* GenericListFind(GENERIC_LIST* list, bool (*predicate)(GENERIC_LIST*))
{
    GENERIC_LIST* current = list->pstNext;  // ������ĵ�һ��ʵ�ʽڵ㿪ʼ

    // ��������
    while (current != list)  // ����ͷ�ڵ�ʱ����
    {
        if (predicate(current))  // ʹ�ûص�������鵱ǰ�ڵ�
        {
            return current;  // ���ص�ǰ�ڵ�
        }
        current = current->pstNext;  // �ƶ�����һ���ڵ�
    }

    return NULL;  // ���δ�ҵ����������Ľڵ㣬���� NULL
}


// �������ĺ���
GENERIC_LIST* GenericListDeepCopy(const GENERIC_LIST* list, void* (*copy_func)(const GENERIC_LIST*))
{
    GENERIC_LIST* new_list = (GENERIC_LIST*)malloc(sizeof(GENERIC_LIST));
    if (new_list == NULL) {
        return NULL;  // �ڴ����ʧ��
    }

    GenericListInit(new_list);  // ��ʼ��������

    GENERIC_LIST* current = list->pstNext;  // ��ԭ����ĵ�һ��ʵ�ʽڵ㿪ʼ
    GENERIC_LIST* new_node;

    // ����ԭ����
    while (current != list)  // ����ͷ�ڵ�ʱ����
    {
        new_node = copy_func(current);  // ʹ�ûص��������ƽڵ�
        if (new_node == NULL) {
            // ����ڵ㸴��ʧ�ܣ���Ҫ�����ѷ�����ڴ�
            GenericListDelInit(new_list);
            return NULL;
        }
        GenericListTailInsert(new_list, new_node);  // ���½ڵ���뵽������β��
        current = current->pstNext;  // �ƶ�����һ���ڵ�
    }

    return new_list;  // �����������ͷ�ڵ�
}