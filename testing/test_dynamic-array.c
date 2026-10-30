#include "../src/dynamic-array/dynamic-array.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct NPC {
    char name[32];
    unsigned int health;
};
typedef struct NPC NPC;

int main(const int argc, const char *argv[]) {
    DynamicArray* array_default = DynamicArray_CreateEmpty();
    assert(array_default != NULL);
    assert(array_default->capacity == DYNAMIC_ARRAY_DEFAULT_CAPACITY);
    assert(array_default->size == 0);
    DynamicArray_Destroy(array_default);

    DynamicArray* array = DynamicArray_CreateEmptyWithCapacity(2);
    assert(array != NULL);
    assert(array->capacity == 2);
    assert(array->size == 0);

    NPC zelda   = {"zelda", 100};
    NPC link    = {"link", 200};
    NPC chicken = {"chicken", 10};
    NPC ganon   = {"ganon", 5000};
    NPC navi    = {"navi", 1};

    DynamicArray_Put(array, &zelda);
    assert(array->size == 1);
    assert(array->capacity == 2);
    assert(DynamicArray_Get(array, 0) == &zelda);

    DynamicArray_Put(array, &link);
    assert(array->size == 2);
    assert(array->capacity == 2);
    assert(DynamicArray_Get(array, 1) == &link);

    DynamicArray_Put(array, &chicken);
    assert(array->size == 3);
    assert(array->capacity == 4);
    assert(DynamicArray_Get(array, 2) == &chicken);

    assert(DynamicArray_Get(array, 99) == NULL);

    DynamicArray_SetCapacity(array, 10);
    assert(array->capacity == 10);
    assert(array->size == 3);
    assert(DynamicArray_Get(array, 0) == &zelda);
    assert(DynamicArray_Get(array, 1) == &link);
    assert(DynamicArray_Get(array, 2) == &chicken);

    DynamicArray_PutAt(array, 5, &ganon);
    assert(array->size == 4);
    assert(DynamicArray_Get(array, 5) == &ganon);

    DynamicArray_PutAt(array, 5, &navi);
    assert(array->size == 4);
    assert(DynamicArray_Get(array, 5) == &navi);

    DynamicArray_PutAt(array, 15, &zelda);
    assert(array->capacity >= 16);
    assert(DynamicArray_Get(array, 15) == &zelda);

    DynamicArray_Print(array);

    for (int i = 0; i < 100; i++) {
        DynamicArray_Put(array, &chicken);
    }
    assert(array->size >= 100);

    DynamicArray_Destroy(array);

    return EXIT_SUCCESS;
}