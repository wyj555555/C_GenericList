#ifndef _GENERICLIST_H__
#define _GENERICLIST_H__

#include <stddef.h>
#include <stdbool.h>

// 双向链表节点定义
typedef struct GENERIC_LIST
{
    struct GENERIC_LIST* pstPrev; // 指向前一个节点的指针
    struct GENERIC_LIST* pstNext; // 指向下一个节点的指针
    size_t length;                // 链表长度（节点数）
} GENERIC_LIST;

// 初始化链表
void GenericListInit(GENERIC_LIST* list);

// 向链表中添加一个节点
void GenericListAdd(GENERIC_LIST* list, GENERIC_LIST* node);

// 在链表尾部插入一个节点
void GenericListTailInsert(GENERIC_LIST* list, GENERIC_LIST* node);

// 在链表头部插入一个节点
void GenericListHeadInsert(GENERIC_LIST* list, GENERIC_LIST* node);

// 删除一个节点
void GenericListDelete(GENERIC_LIST* node);

// 判断链表是否为空
bool GenericListEmpty(GENERIC_LIST* list);

// 将一个链表添加到另一个链表的尾部
void GenericListAddList(GENERIC_LIST* oldList, GENERIC_LIST* newList);

// 将一个链表插入到另一个链表的尾部
void GenericListTailInsertList(GENERIC_LIST* oldList, GENERIC_LIST* newList);

// 将一个链表插入到另一个链表的头部
void GenericListHeadInsertList(GENERIC_LIST* oldList, GENERIC_LIST* newList);

// 删除链表并初始化链表
void GenericListDelInit(GENERIC_LIST* list);

// 获取链表的长度
size_t GenericListLength(const GENERIC_LIST* list);

GENERIC_LIST* GenericListFind(GENERIC_LIST* list, bool (*predicate)(GENERIC_LIST*));

GENERIC_LIST* GenericListDeepCopy(const GENERIC_LIST* list, void* (*copy_func)(const GENERIC_LIST*));

// 宏定义部分

// 获取链表的第一个节点
#define GENERIC_DL_LIST_FIRST(object) ((object)->pstNext)

// 判断一个节点是否为链表的结束节点
#define GENERIC_DL_LIST_IS_END(list, node) ((list) == (node) ? TRUE : FALSE)

// 获取链表的最后一个节点
#define GENERIC_DL_LIST_LAST(object) ((object)->pstPrev)

// 获取某结构体中成员字段的偏移量
#define GENERIC_OF_FIELD(type, field) ((unsigned int)&((type *)0)->field)

// 获取某结构体成员的偏移量
#define GENERIC_OFF_SET_OF(type, member) ((unsigned int)&((type *)0)->member)

// 获取链表节点的结构体指针
#define GENERIC_DL_LIST_ENTRY(item, type, member) \
    ((type *)(void *)((char *)(item) - GENERIC_OFF_SET_OF(type, member)))

// 遍历链表中的所有节点
#define GENERIC_DL_LIST_FOR_EACH_ENTRY(item, list, type, member)             \
    for (item = Generic_DL_LIST_ENTRY((list)->pstNext, type, member);        \
         &(item)->member != (list);                                      \
         item = GENERIC_OFF_SET_OF((item)->member.pstNext, type, member))

// 安全遍历链表中的所有节点（支持删除操作）
#define GENERIC_DL_LIST_FOR_EACH_ENTRY_SAFE(item, next, list, type, member)               \
    for (item = Generic_DL_LIST_ENTRY((list)->pstNext, type, member),                     \
         next = Generic_DL_LIST_ENTRY((item)->member.pstNext, type, member);              \
         &(item)->member != (list);                                                   \
         item = next, next = Generic_DL_LIST_ENTRY((item)->member.pstNext, type, member))

// 遍历链表中的所有节点
#define GENERIC_DL_LIST_FOR_EACH(item, list) \
    for (item = (list)->pstNext;         \
         (item) != (list);               \
         item = (item)->pstNext)

// 安全遍历链表中的所有节点（支持删除操作）
#define GENERIC_DL_LIST_FOR_EACH_SAFE(item, next, list)      \
    for (item = (list)->pstNext, next = (item)->pstNext; \
         (item) != (list);                               \
         item = next, next = (item)->pstNext)

// 从链表节点中获取对应的结构体指针
#define GET_STRUCT_FROM_LIST(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

// 定义链表的头节点
#define GENERIC_DL_LIST_HEAD(list) GENERIC_LIST list = { &(list), &(list) }

// 获取链表头部的特定类型节点
#define GENERIC_ListPeekHeadType(list, type, element)                    \
    do {                                                               \
        type *__t;                                                     \
        if ((list)->pstNext == list) {                                 \
            __t = NULL;                                                \
        } else {                                                       \
            __t = Generic_DL_LIST_ENTRY((list)->pstNext, type, element); \
        }                                                              \
        __t;                                                           \
    } while (0)

// 移除链表头部的特定类型节点
#define GENERIC_ListRemoveHeadType(list, type, element)                  \
    do {                                                               \
        type *__t;                                                     \
        if ((list)->pstNext == list) {                                 \
            __t = NULL;                                                \
        } else {                                                       \
            __t = GENERIC_DL_LIST_ENTRY((list)->pstNext, type, element); \
            GenericListDelete((list)->pstNext);                         \
        }                                                              \
        __t;                                                           \
    } while (0)

// 获取链表中下一个特定类型节点
#define GENERIC_ListNextType(list, item, type, element)                  \
    do {                                                               \
        type *__t;                                                     \
        if ((item)->pstNext == list) {                                 \
            __t = NULL;                                                \
        } else {                                                       \
            __t = Generic_DL_LIST_ENTRY((item)->pstNext, type, element); \
        }                                                              \
        __t;                                                           \
    } while (0)

#endif // !_GENERICLIST_H__
