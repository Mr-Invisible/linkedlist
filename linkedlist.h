#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include "stdint.h"

typedef enum {
    linkedListStatusOk,
    linkedListStatusError,
    linkedListStatusNoMemory,
} linkedListStatus_t;

typedef struct __linkedList {
    struct __linkedListNode* head;
    struct __linkedListNode* tail;
    uint32_t size;
    int32_t status;
} linkedList_t;

typedef struct __linkedListNode {
    struct __linkedListNode* next;
    struct __linkedListNode* prev;
    struct __linkedList* list;
    void* data;
} linkedListNode_t;

typedef enum {
    linkedListDirectionForward,
    linkedListDirectionBackward,
} linkedListDirection_t;

/**
 * @brief Linked List Callback Function
 * 
 */
typedef int32_t (*linkedListCallback_t)(linkedListNode_t* pNode, void* pData);

/**
 * @brief Initializes linked list
 * 
 * @param pList Linked List Pointer
 * @return int32_t 
 */
linkedListStatus_t linkedListInit(linkedList_t* pList);
linkedListStatus_t linkedListInsertHead(linkedList_t* pList, linkedListNode_t* pNode);
linkedListStatus_t linkedListInsertTail(linkedList_t* pList, linkedListNode_t* pNode);
linkedListStatus_t linkedListRemove(linkedListNode_t* pNode);
linkedListNode_t* linkedListIterate(linkedList_t* pList, linkedListCallback_t callback, linkedListDirection_t direction, void* pData);

#endif /*_LINKED_LIST_H_*/