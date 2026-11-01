//
// Created by killi on 30/10/2026.
//
#include "dynamic-array.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DynamicArray* DynamicArray_CreateEmpty() {
    DynamicArray *array = malloc(sizeof(DynamicArray));
    array->capacity = DYNAMIC_ARRAY_DEFAULT_CAPACITY;
    array->size = 0;
    array->array = calloc(DYNAMIC_ARRAY_DEFAULT_CAPACITY,sizeof(void*));
    return array;
}

DynamicArray* DynamicArray_CreateEmptyWithCapacity(unsigned int capacity) {
    if (capacity == 0) capacity = DYNAMIC_ARRAY_DEFAULT_CAPACITY;
    DynamicArray *array = malloc(sizeof(DynamicArray));
    array->capacity = capacity;
    array->size = 0;
    array->array = calloc(capacity, sizeof(void*));
    return array;
}

void DynamicArray_DoubleCapacity(DynamicArray* array) {
    if (!array || !array->array) return;
    void* newArray = calloc(array->capacity * 2, sizeof(void*));
    if (!newArray) return;
    memcpy(newArray, array->array, array->capacity * sizeof(void*));
    array->capacity *= 2;
    free(array->array);
    array->array = newArray;
}

void DynamicArray_SetCapacity(DynamicArray* array, unsigned int capacity) {
    if (!array || !array->array) return;
    void* newArray = calloc(capacity, sizeof(void*));
    if (!newArray) return;
    unsigned int minCapacity = (capacity < array->capacity) ? capacity : array->capacity;
    memcpy(newArray, array->array, minCapacity * sizeof(void*));
    array->capacity = capacity;
    free(array->array);
    array->array = newArray;
}

void DynamicArray_Put(DynamicArray* array, void* value) {
    if (!array || !array->array || !value) return;

    // On verifie s'il reste de la place
    if (array->size == array->capacity) DynamicArray_DoubleCapacity(array);

    // On cherche la premiere place dispo ( pas forcement array->array[array->size] )
    unsigned int i = 0;
    while (i < array->capacity && array->array[i] != NULL) i++;

    // On ajoute dans le tableau
    array->array[i] = value;
    array->size += 1;
}

void DynamicArray_PutAt(DynamicArray* array, unsigned int index, void* value) {
    if (!array || !array->array || !value) return;

    // Si on depasse on augmente le tableau
    if (index >= array->capacity) DynamicArray_SetCapacity(array, index + 1);

    // On ajoute en taille que si c est pas une case deja utilisee
    if (array->array[index] == NULL) array->size += 1;

    array->array[index] = value;
}

void DynamicArray_RemoveAt(DynamicArray* array, unsigned int index) {
    if (!array || !array->array || !index) return;
    if (index >= array->capacity) return;
    array->array[index] = NULL;
    array->size -= 1;
}

void* DynamicArray_Get(DynamicArray* array, unsigned int index) {
    if (!array || !array->array || index >= array->capacity) return NULL;
    return array->array[index];
}

void DynamicArray_Destroy(DynamicArray *array) {
    free(array->array);
    free(array);
}

void DynamicArray_Print(DynamicArray *array) {
    if (!array || !array->array) return;
    printf("Array[\n");
    for (unsigned int i = 0; i < array->capacity; i++) {
        printf("\t[%d]: ", i);
        if (array->array[i] == NULL) printf("0x0,");
        else printf("0x%p,", array->array[i]);
        printf("\n");
    }
    printf("]\n");
}