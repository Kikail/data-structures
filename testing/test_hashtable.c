//
// Created by killian on 10/30/26.
//

#include "../src/hashtable/hashtable.h"
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
    Hashtable* hashtable = Hashtable_CreateEmptyWithCapacity(16);

    NPC zelda       = {"zelda"      , 100};
    NPC link        = {"link"       , 200};
    NPC chicken     = {"chicken"    , 10};
    NPC ganon       = {"ganon"      , 5000};

    Hashtable_Put(hashtable, "/CHEMIN/VERS/UN/FICHIER/test.txt",    &zelda);
    Hashtable_Put(hashtable, "/CHEMIN/VERS/UN/FICHIER/123.txt",     &link);
    Hashtable_Put(hashtable, "/CHEMIN/VERS/UN/FICHIER/abx.txt",  &chicken);
    Hashtable_Put(hashtable, "/CHEMIN/VERS/UN/FICHIER/oui.txt",    &ganon);

    Hashtable_Print(hashtable);

    NPC zelda_get   = *((NPC*)(Hashtable_Get(hashtable, "/CHEMIN/VERS/UN/FICHIER/test.txt")));
    NPC link_get    = *((NPC*)(Hashtable_Get(hashtable, "/CHEMIN/VERS/UN/FICHIER/123.txt")));
    NPC chicken_get = *((NPC*)(Hashtable_Get(hashtable, "/CHEMIN/VERS/UN/FICHIER/abx.txt")));
    NPC ganon_get   = *((NPC*)(Hashtable_Get(hashtable, "/CHEMIN/VERS/UN/FICHIER/oui.txt")));

    NPC_Afficher(zelda_get);
    NPC_Afficher(link_get);
    NPC_Afficher(chicken_get);
    NPC_Afficher(ganon_get);

    Hashtable_Destroy(hashtable);

    return EXIT_SUCCESS;
}