#include <stdio.h>
#include <stdlib.h>
#include "genericlist.h"  // 包含你提供的头文件

// 自定义测试结构体
typedef struct TestNode {
    GENERIC_LIST list;  // 链表结构
    int data;
} TestNode;

// 打印链表中的所有节点数据
void PrintList(const GENERIC_LIST* list) {
    const GENERIC_LIST* node;
    for (node = list->pstNext; node != list; node = node->pstNext) {
        TestNode* testNode = GET_STRUCT_FROM_LIST(node, TestNode, list);
        printf("Node data: %d\n", testNode->data);
    }
}

// 测试所有操作
void TestGenericList() {
    GENERIC_LIST head;
    GenericListInit(&head);

    // 创建和初始化节点
    TestNode node1 = { .data = 1 };
    TestNode node2 = { .data = 2 };
    TestNode node3 = { .data = 3 };
    TestNode node4 = { .data = 4 };

    // 插入节点到链表
    GenericListHeadInsert(&head, &node1.list);
    GenericListTailInsert(&head, &node2.list);
    GenericListTailInsert(&head, &node3.list);
    GenericListTailInsert(&head, &node4.list);

    // 打印链表
    printf("List after inserting 4 nodes:\n");
    PrintList(&head);

    // 计算链表长度
    //size_t length = CalculateListLength(&head);
    //printf("List length: %zu\n", length);

    // 删除节点
    GENERIC_ListRemoveHeadType(&head, TestNode, list);
    printf("List after removing the head node:\n");
    PrintList(&head);

    // 计算链表长度
    //length = CalculateListLength(&head);
    //printf("List length after removal: %zu\n", length);

    // 清空链表
    GenericListDelInit(&head);
    printf("List after clearing:\n");
    PrintList(&head);

    // 计算链表长度
    //length = CalculateListLength(&head);
    //printf("List length after clearing: %zu\n", length);
}

int main() {
    TestGenericList();
    return 0;
}
