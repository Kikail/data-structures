//
// Created by killian on 10/30/26.
//
#include "hashtable.h"

#include <stdio.h>
#include <stdlib.h>

Hashtable* Hashtable_CreateEmpty() {
    Hashtable* hashtable = malloc(sizeof(Hashtable));
    hashtable->capacity = HASHTABLE_DEFAULT_CAPACITY;
    hashtable->table = calloc(HASHTABLE_DEFAULT_CAPACITY ,sizeof(struct HashtableNode));
    return hashtable;
}

Hashtable* Hashtable_CreateEmptyWithCapacity(const int capacity) {
    Hashtable* hashtable = malloc(sizeof(Hashtable));
    hashtable->capacity = capacity;
    hashtable->table = calloc(capacity ,sizeof(struct HashtableNode));
    return hashtable;
}

unsigned int hash(char* key) {
    unsigned int hash = 5381;   // Nombre magique !
    while (*key++) hash = (hash * 33) + *key; // 33 est magique aussi !
    return hash;
}

void Hashtable_Put(Hashtable* hashtable, const char* key, void* value) {
    unsigned int hashed_key = hash(key);
    hashed_key = hashed_key % hashtable->capacity;  // si on ne fait pas le modulo on depasse du tableau
    struct HashtableNode* node = &hashtable->table[hashed_key];

    // On verifie si le premier noeud est vide
    if (node->value == NULL) {
        node->value = value;
        node->key = key;    // possible grace au const
        return;
    }

    // Ici on concatene si la cle est differente sinon on remplace
    struct HashtableNode* current = node;
    struct HashtableNode* last = NULL;
    while (current != NULL) {
        if (current->key != NULL && strcmp(current->key, key) == 0) {
            current->value = value;
            return;
        }
        last = current;
        current = current->next;
    }

    struct HashtableNode* new_node  = malloc(sizeof(struct HashtableNode));
    new_node->value = value;
    new_node->key = key;
    new_node->next = NULL;
    last->next = new_node;

    return;
}

void* Hashtable_Get(Hashtable* hashtable, const char* key) {
    unsigned int hashed_key = hash(key);
    hashed_key = hashed_key % hashtable->capacity;
    struct HashtableNode* node = &hashtable->table[hashed_key];
    struct HashtableNode* current = node;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void Hashtable_Destroy(Hashtable* hashtable) {
    if (hashtable->table == NULL) return;

    for (int i = 0; i < hashtable->capacity; i++) {
        struct HashtableNode* node = hashtable->table[i].next;
        while (node != NULL) {
            struct HashtableNode* temp = node->next;
            free(node);
            node = temp;
        }
    }
    free(hashtable->table);
    free(hashtable);
}

void Hashtable_Print(Hashtable* hashtable) {
    printf("Hashtable{\n");
    for (int i = 0; i < hashtable->capacity; i++) {
        struct HashtableNode* node = &hashtable->table[i];

        if (node->value == NULL) {
            printf("\t()\n");
            continue;
        }

        printf("\t");
        while (node != NULL) {
            printf("(%s, %p) ", node->key, node->value);
            node = node->next;
        }
        printf("\n");
    }
    printf("}\n");
}