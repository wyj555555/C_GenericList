#include <stdio.h>
#include <stdlib.h>
#include "genericlist.h"  // �������ṩ��ͷ�ļ�

// �Զ�����Խṹ��
typedef struct TestNode {
    GENERIC_LIST list;  // ����ṹ
    int data;
} TestNode;

// ��ӡ�����е����нڵ�����
void PrintList(const GENERIC_LIST* list) {
    const GENERIC_LIST* node;
    for (node = list->pstNext; node != list; node = node->pstNext) {
        TestNode* testNode = GET_STRUCT_FROM_LIST(node, TestNode, list);
        printf("Node data: %d\n", testNode->data);
    }
}

// �������в���
void TestGenericList() {
    GENERIC_LIST head;
    GenericListInit(&head);

    // �����ͳ�ʼ���ڵ�
    TestNode node1 = { .data = 1 };
    TestNode node2 = { .data = 2 };
    TestNode node3 = { .data = 3 };
    TestNode node4 = { .data = 4 };

    // ����ڵ㵽����
    GenericListHeadInsert(&head, &node1.list);
    GenericListTailInsert(&head, &node2.list);
    GenericListTailInsert(&head, &node3.list);
    GenericListTailInsert(&head, &node4.list);

    // ��ӡ����
    printf("List after inserting 4 nodes:\n");
    PrintList(&head);

    // ����������
    //size_t length = CalculateListLength(&head);
    //printf("List length: %zu\n", length);

    // ɾ���ڵ�
    GENERIC_ListRemoveHeadType(&head, TestNode, list);
    printf("List after removing the head node:\n");
    PrintList(&head);

    // ����������
    //length = CalculateListLength(&head);
    //printf("List length after removal: %zu\n", length);

    // �������
    GenericListDelInit(&head);
    printf("List after clearing:\n");
    PrintList(&head);

    // ����������
    //length = CalculateListLength(&head);
    //printf("List length after clearing: %zu\n", length);
}

int main() {
    TestGenericList();
    return 0;
}
