#ifndef _GENERICLIST_H__
#define _GENERICLIST_H__

#include <stddef.h>
#include <stdbool.h>

// ˫������ڵ㶨��
typedef struct GENERIC_LIST
{
    struct GENERIC_LIST* pstPrev; // ָ��ǰһ���ڵ��ָ��
    struct GENERIC_LIST* pstNext; // ָ����һ���ڵ��ָ��
    size_t length;                // �����ȣ��ڵ�����
} GENERIC_LIST;

// ��ʼ������
void GenericListInit(GENERIC_LIST* list);

// �����������һ���ڵ�
void GenericListAdd(GENERIC_LIST* list, GENERIC_LIST* node);

// ������β������һ���ڵ�
void GenericListTailInsert(GENERIC_LIST* list, GENERIC_LIST* node);

// ������ͷ������һ���ڵ�
void GenericListHeadInsert(GENERIC_LIST* list, GENERIC_LIST* node);

// ɾ��һ���ڵ�
void GenericListDelete(GENERIC_LIST* node);

// �ж������Ƿ�Ϊ��
bool GenericListEmpty(GENERIC_LIST* list);

// ��һ��������ӵ���һ�������β��
void GenericListAddList(GENERIC_LIST* oldList, GENERIC_LIST* newList);

// ��һ��������뵽��һ�������β��
void GenericListTailInsertList(GENERIC_LIST* oldList, GENERIC_LIST* newList);

// ��һ��������뵽��һ�������ͷ��
void GenericListHeadInsertList(GENERIC_LIST* oldList, GENERIC_LIST* newList);

// ɾ��������ʼ������
void GenericListDelInit(GENERIC_LIST* list);

// ��ȡ����ĳ���
size_t GenericListLength(const GENERIC_LIST* list);

GENERIC_LIST* GenericListFind(GENERIC_LIST* list, bool (*predicate)(GENERIC_LIST*));

GENERIC_LIST* GenericListDeepCopy(const GENERIC_LIST* list, void* (*copy_func)(const GENERIC_LIST*));

// �궨�岿��

// ��ȡ����ĵ�һ���ڵ�
#define GENERIC_DL_LIST_FIRST(object) ((object)->pstNext)

// �ж�һ���ڵ��Ƿ�Ϊ����Ľ����ڵ�
#define GENERIC_DL_LIST_IS_END(list, node) ((list) == (node) ? TRUE : FALSE)

// ��ȡ��������һ���ڵ�
#define GENERIC_DL_LIST_LAST(object) ((object)->pstPrev)

// ��ȡĳ�ṹ���г�Ա�ֶε�ƫ����
#define GENERIC_OF_FIELD(type, field) ((unsigned int)&((type *)0)->field)

// ��ȡĳ�ṹ���Ա��ƫ����
#define GENERIC_OFF_SET_OF(type, member) ((unsigned int)&((type *)0)->member)

// ��ȡ����ڵ�Ľṹ��ָ��
#define GENERIC_DL_LIST_ENTRY(item, type, member) \
    ((type *)(void *)((char *)(item) - GENERIC_OFF_SET_OF(type, member)))

// ���������е����нڵ�
#define GENERIC_DL_LIST_FOR_EACH_ENTRY(item, list, type, member)             \
    for (item = Generic_DL_LIST_ENTRY((list)->pstNext, type, member);        \
         &(item)->member != (list);                                      \
         item = GENERIC_OFF_SET_OF((item)->member.pstNext, type, member))

// ��ȫ���������е����нڵ㣨֧��ɾ��������
#define GENERIC_DL_LIST_FOR_EACH_ENTRY_SAFE(item, next, list, type, member)               \
    for (item = Generic_DL_LIST_ENTRY((list)->pstNext, type, member),                     \
         next = Generic_DL_LIST_ENTRY((item)->member.pstNext, type, member);              \
         &(item)->member != (list);                                                   \
         item = next, next = Generic_DL_LIST_ENTRY((item)->member.pstNext, type, member))

// ���������е����нڵ�
#define GENERIC_DL_LIST_FOR_EACH(item, list) \
    for (item = (list)->pstNext;         \
         (item) != (list);               \
         item = (item)->pstNext)

// ��ȫ���������е����нڵ㣨֧��ɾ��������
#define GENERIC_DL_LIST_FOR_EACH_SAFE(item, next, list)      \
    for (item = (list)->pstNext, next = (item)->pstNext; \
         (item) != (list);                               \
         item = next, next = (item)->pstNext)

// ������ڵ��л�ȡ��Ӧ�Ľṹ��ָ��
#define GET_STRUCT_FROM_LIST(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

// ���������ͷ�ڵ�
#define GENERIC_DL_LIST_HEAD(list) GENERIC_LIST list = { &(list), &(list) }

// ��ȡ����ͷ�����ض����ͽڵ�
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

// �Ƴ�����ͷ�����ض����ͽڵ�
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

// ��ȡ��������һ���ض����ͽڵ�
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
