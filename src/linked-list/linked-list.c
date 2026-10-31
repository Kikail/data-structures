//
// Created by killi on 30/10/2026.
//
#include "linked-list.h"

#include <stdio.h>
#include <stdlib.h>

struct LinkedListNode* LinkedListNode_Create(void* data) {
    struct LinkedListNode* node = (struct LinkedListNode*)malloc(sizeof(struct LinkedListNode));
    node->data = data;
    node->next = NULL;
    node->previous = NULL;
    return node;
}

LinkedList* LinkedList_CreateEmpty() {
    LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

bool LinkedList_IsEmpty(LinkedList* list) {
    if (!list) return true;
    return !list->head || !list->tail || list->size == 0;
}

void LinkedList_PutHead(LinkedList* list, void* data) {
    struct LinkedListNode* newNode = LinkedListNode_Create(data);

    // Cas de liste vide
    if (LinkedList_IsEmpty(list)) {
        list->head = newNode;
        list->tail = list->head;
        list->size += 1;
        return;
    }

    newNode->next = list->head;
    list->head->previous = newNode;
    list->head = newNode;
    list->size += 1;
}
void LinkedList_PutTail(LinkedList* list, void* data) {
    struct LinkedListNode* newNode = LinkedListNode_Create(data);

    // Cas de liste vide
    if (LinkedList_IsEmpty(list)) {
        list->head = newNode;
        list->tail = list->head;
        list->size += 1;
        return;
    }

    newNode->previous = list->tail;
    list->tail->next = newNode;
    list->tail = newNode;
    list->size += 1;
}
void LinkedList_PutAt(LinkedList* list, void* data, unsigned int index) {
    // Cas de liste vide
    if (LinkedList_IsEmpty(list)) {
        LinkedList_PutHead(list, data);
        return;
    }

    // Cas ou index > taille de la liste
    if (index >= list->size) {
        LinkedList_PutTail(list, data);
        return;
    }

    // Cas ou index == 0
    if (index == 0) {
        LinkedList_PutHead(list, data);
        return;
    }

    // A inserer entre 2 nodes
    struct LinkedListNode* newNode = LinkedListNode_Create(data);
    struct LinkedListNode* current = list->head; unsigned int i = 0;
    while (current != NULL && i < index) {
        current = current->next;
        i++;
    }
    newNode->next = current;
    newNode->previous = current->previous;
    current->previous->next = newNode;
    current->previous = newNode;
    list->size += 1;
}

void LinkedList_RemoveHead(LinkedList* list) {
    if (LinkedList_IsEmpty(list)) return;

    // Cas ou la liste est de taille 1
    if (list->size == 1) {
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
        return;
    }

    struct LinkedListNode* head = list->head;
    struct LinkedListNode* next = head->next;
    next->previous = NULL;
    list->head = next;
    list->size -= 1;
    free(head);
}

void LinkedList_RemoveTail(LinkedList* list) {
    if (LinkedList_IsEmpty(list)) return;

    // Cas ou la liste est de taille 1
    if (list->size == 1) {
        free(list->tail);
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
        return;
    }

    struct LinkedListNode* tail = list->tail;
    struct LinkedListNode* previous = tail->previous;
    previous->next = NULL;
    list->tail = previous;
    list->size -= 1;
    free(tail);
}

void LinkedList_RemoveAt(LinkedList* list, unsigned int index) {
    if (LinkedList_IsEmpty(list)) return;

    // Cas ou l'index est le debut
    if (index == 0) {
        LinkedList_RemoveHead(list);
        return;
    }

    // Cas ou l'index est la fin
    if (index >= list->size - 1) {
        LinkedList_RemoveTail(list);
        return;
    }

    // On parcours la liste
    struct LinkedListNode* current = list->head;
    unsigned int i = 0;
    while (current != NULL && i < index) {
        current = current->next;
        i++;
    }

    // On enleve le noeud
    current->previous->next = current->next;
    current->next->previous = current->previous;
    list->size -= 1;
    free(current);
}

void* LinkedList_ExtractHead(LinkedList* list) {
    if (LinkedList_IsEmpty(list)) return NULL;

    // Cas ou la liste est de taille 1
    if (list->size == 1) {
        void* data = list->head->data;
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
        return data;
    }

    struct LinkedListNode* head = list->head;
    struct LinkedListNode* next = head->next;
    next->previous = NULL;
    list->head = next;
    void* data = head->data;
    list->size -= 1;
    free(head);
    return data;
}
void* LinkedList_ExtractTail(LinkedList* list) {
    if (LinkedList_IsEmpty(list)) return NULL;

    // Cas ou la liste est de taille 1
    if (list->size == 1) {
        void* data = list->tail->data;
        free(list->tail);
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
        return data;
    }

    void* data = list->tail->data;
    struct LinkedListNode* tail = list->tail;
    struct LinkedListNode* previous = tail->previous;
    previous->next = NULL;
    list->tail = previous;
    free(tail);
    list->size -= 1;
    return data;
}
void* LinkedList_ExtractAt(LinkedList* list, unsigned int index) {
    if (LinkedList_IsEmpty(list)) return NULL;

    // Cas ou l'index est le debut
    if (index == 0) {
        return LinkedList_ExtractHead(list);
    }

    // Cas ou l'index est la fin
    if (index >= list->size - 1) {
        return LinkedList_ExtractTail(list);
    }

    // On parcours la liste
    struct LinkedListNode* current = list->head;
    unsigned int i = 0;
    while (current != NULL && i < index) {
        current = current->next;
        i++;
    }

    // On enleve le noeud
    current->previous->next = current->next;
    current->next->previous = current->previous;
    void* data = current->data;
    free(current);
    list->size -= 1;
    return data;
}

void LinkedList_Destroy(LinkedList* list) {
    struct LinkedListNode* current = list->head;
    while (current != NULL) {
        struct LinkedListNode* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void LinkedList_Print(LinkedList* list) {
    if (!list || !list->head || !list->tail) return;
    printf("LinkedList[\n");
    struct LinkedListNode* current = list->head;
    unsigned int i = 0;
    while (current != NULL) {
        printf("\t[%d]: ", i);
        printf("0x%p,\n", current->data);
        current = current->next;
        i++;
    }
    printf("]\n");
}