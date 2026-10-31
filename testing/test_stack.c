#include <assert.h>
#include "../src/stack/stack.h"
#include <stdio.h>
#include <stdlib.h>

struct NPC {
    char name[32];
    unsigned int health;
};
typedef struct NPC NPC;

int main(const int argc, const char *argv[]) {
    NPC zelda   = {"Zelda", 100};
    NPC link    = {"Link", 200};
    NPC chicken = {"Chicken", 10};
    NPC ganon   = {"Ganon", 5000};

    Stack* stack = Stack_CreateEmptyWithCapacity(3);

    assert(Stack_IsEmpty(stack) == true);
    assert(Stack_IsFull(stack) == false);
    assert(Stack_Pop(stack) == NULL);

    assert(Stack_Push(stack, &zelda) == true);
    assert(Stack_Push(stack, &link) == true);
    assert(Stack_Push(stack, &chicken) == true);

    assert(Stack_IsFull(stack) == true);

    assert(Stack_Push(stack, &ganon) == false);

    NPC* popped = (NPC*)Stack_Pop(stack);
    assert(popped == &chicken);

    popped = (NPC*)Stack_Pop(stack);
    assert(popped == &link);

    assert(Stack_IsFull(stack) == false);

    assert(Stack_Push(stack, &ganon) == true);

    popped = (NPC*)Stack_Pop(stack);
    assert(popped == &ganon);

    popped = (NPC*)Stack_Pop(stack);
    assert(popped == &zelda);

    assert(Stack_IsEmpty(stack) == true);

    Stack_Destroy(stack);

    printf("Tous les tests de la pile ont reussi avec succes !\n");

    return EXIT_SUCCESS;
}