#include "stddef.h"

#include "linkedlist.h"

linkedListStatus_t linkedListInit(linkedList_t* pList) {
    linkedListStatus_t status = linkedListStatusError;
    if (pList != NULL) {
        pList->size = 0;
        pList->head = (linkedListNode_t*)0;
        pList->tail = (linkedListNode_t*)0;
        status = linkedListStatusOk;
    }
    return status;
}

linkedListStatus_t linkedListInsertHead(linkedList_t* pList, linkedListNode_t* pNode) {
    linkedListStatus_t status = linkedListStatusError;
    if (pList != NULL && pNode != NULL) {
        pNode->list = pList;
        if (pList->head == NULL) {
            pList->head = pNode;
            pList->tail = pNode;
        } else {
            pList->head->prev = pNode;
            pNode->next = pList->head;
            pList->head = pNode;
        }
        pList->size++;
    }
    return status;
}

linkedListStatus_t linkedListInsertTail(linkedList_t* pList, linkedListNode_t* pNode) {
    linkedListStatus_t status = linkedListStatusError;
    if (pList != NULL && pNode != NULL) {
        pNode->list = pList;
        if (pList->tail == NULL) {
            pList->tail = pNode;
            pList->head = pNode;
        } else {
            pList->tail->next = pNode;
            pNode->prev = pList->tail;
            pList->tail = pNode;
        }
        pList->size++;
    }
    return status;
}

linkedListStatus_t linkedListRemove(linkedListNode_t* pNode) {
    linkedListStatus_t status = linkedListStatusError;
    if (pNode != NULL) {
        // removed node references from previous and next
        if (pNode->prev != NULL) {
            pNode->prev->next = pNode->next;
        }
        if (pNode->next != NULL) {
            pNode->next->prev = pNode->prev;
        }

        // update the list if removing head and/or tail
        if (pNode == pNode->list->head) {
            pNode->list->head = pNode->next;
        }
        if (pNode == pNode->list->tail) {
            pNode->list->tail = pNode->prev;
        }

        // decrement size of the list
        if (pNode->list->size > 0) {
            pNode->list->size--;
        } else {
            status = linkedListStatusNoMemory;
        }
    }
    return status;
}

linkedListNode_t* linkedListIterate(linkedList_t* pList, linkedListCallback_t callback, linkedListDirection_t direction, void* pData) {
    linkedListNode_t* rNode = (linkedListNode_t*)0;

    // check for nulls
    if (pList != NULL && callback != NULL) {
        int32_t retCode = 0;

        // set initial node of linked list
        if (direction == linkedListDirectionForward) {
            rNode = pList->head;
        } else {
            rNode = pList->tail;
        }

        // iterate through list of nodes
        while (retCode == 0 && rNode != NULL) {
            retCode = callback(rNode, pData);
            // check retCode, if 0 continue loop. anything else will abort loop
            if (retCode == 0) {
                if (direction == linkedListDirectionForward) {
                    rNode = rNode->next;
                } else {
                    rNode = rNode->prev;
                }
            }
        }
    }
    return rNode;
}