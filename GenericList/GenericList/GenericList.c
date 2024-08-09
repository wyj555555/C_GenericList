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

// 根据链表节点中的字段进行查找的函数
GENERIC_LIST* GenericListFind(GENERIC_LIST* list, bool (*predicate)(GENERIC_LIST*))
{
    GENERIC_LIST* current = list->pstNext;  // 从链表的第一个实际节点开始

    // 遍历链表
    while (current != list)  // 遇到头节点时结束
    {
        if (predicate(current))  // 使用回调函数检查当前节点
        {
            return current;  // 返回当前节点
        }
        current = current->pstNext;  // 移动到下一个节点
    }

    return NULL;  // 如果未找到符合条件的节点，返回 NULL
}


// 深拷贝链表的函数
GENERIC_LIST* GenericListDeepCopy(const GENERIC_LIST* list, void* (*copy_func)(const GENERIC_LIST*))
{
    GENERIC_LIST* new_list = (GENERIC_LIST*)malloc(sizeof(GENERIC_LIST));
    if (new_list == NULL) {
        return NULL;  // 内存分配失败
    }

    GenericListInit(new_list);  // 初始化新链表

    GENERIC_LIST* current = list->pstNext;  // 从原链表的第一个实际节点开始
    GENERIC_LIST* new_node;

    // 遍历原链表
    while (current != list)  // 遇到头节点时结束
    {
        new_node = copy_func(current);  // 使用回调函数复制节点
        if (new_node == NULL) {
            // 如果节点复制失败，需要清理已分配的内存
            GenericListDelInit(new_list);
            return NULL;
        }
        GenericListTailInsert(new_list, new_node);  // 将新节点插入到新链表尾部
        current = current->pstNext;  // 移动到下一个节点
    }

    return new_list;  // 返回新链表的头节点
}