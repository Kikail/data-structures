#include "../src/dynamic-array/dynamic-array.h"
#include <stdio.h>
#include <stdlib.h>


struct NPC {
    char name[32];
    unsigned int health;
};
typedef struct NPC NPC;

void NPC_Afficher(NPC npc) {
    printf("{%s %u}\n",npc.name, npc.health);
}

int main(const int argc, const char *argv[]) {
    DynamicArray* array = DynamicArray_CreateEmptyWithCapacity(1);

    NPC zelda       = {"zelda"      , 100};
    NPC link        = {"link"       , 200};
    NPC chicken     = {"chicken"    , 10};
    NPC ganon       = {"ganon"      , 5000};

    DynamicArray_Put(array, &zelda);
    DynamicArray_Put(array, &link);
    DynamicArray_Put(array, &chicken);
    DynamicArray_Put(array, &ganon);

    DynamicArray_Print(array);

    NPC zelda_get   = *((NPC*)(DynamicArray_Get(array, 0)));
    NPC link_get    = *((NPC*)(DynamicArray_Get(array, 1)));
    NPC chicken_get = *((NPC*)(DynamicArray_Get(array, 2)));
    NPC ganon_get   = *((NPC*)(DynamicArray_Get(array, 3)));

    NPC_Afficher(zelda_get);
    NPC_Afficher(link_get);
    NPC_Afficher(chicken_get);
    NPC_Afficher(ganon_get);

    DynamicArray_Destroy(array);

    return EXIT_SUCCESS;
}
