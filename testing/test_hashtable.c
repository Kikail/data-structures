#include "../src/hashtable/hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct NPC {
    char name[32];
    unsigned int health;
};
typedef struct NPC NPC;

void NPC_Afficher(NPC npc) {
    printf("{%s %u}\n", npc.name, npc.health);
}

int main(const int argc, const char *argv[]) {
    Hashtable* ht_default = Hashtable_CreateEmpty();
    assert(ht_default != NULL);
    assert(ht_default->capacity == HASHTABLE_DEFAULT_CAPACITY);
    Hashtable_Destroy(ht_default);

    Hashtable* hashtable = Hashtable_CreateEmptyWithCapacity(3);
    assert(hashtable != NULL);
    assert(hashtable->capacity == 3);

    NPC zelda   = {"zelda", 100};
    NPC link    = {"link", 200};
    NPC chicken = {"chicken", 10};
    NPC ganon   = {"ganon", 5000};
    NPC navi    = {"navi", 1};

    Hashtable_Put(hashtable, "/CHEMIN/VERS/UN/FICHIER/test.txt", &zelda);
    Hashtable_Put(hashtable, "/CHEMIN/VERS/UN/FICHIER/123.txt", &link);
    Hashtable_Put(hashtable, "/CHEMIN/VERS/UN/FICHIER/abx.txt", &chicken);
    Hashtable_Put(hashtable, "/CHEMIN/VERS/UN/FICHIER/oui.txt", &ganon);

    assert(Hashtable_Get(hashtable, "/CHEMIN/VERS/UN/FICHIER/test.txt") == &zelda);
    assert(Hashtable_Get(hashtable, "/CHEMIN/VERS/UN/FICHIER/123.txt") == &link);
    assert(Hashtable_Get(hashtable, "/CHEMIN/VERS/UN/FICHIER/abx.txt") == &chicken);
    assert(Hashtable_Get(hashtable, "/CHEMIN/VERS/UN/FICHIER/oui.txt") == &ganon);
    assert(Hashtable_Get(hashtable, "/CHEMIN/VERS/UN/FICHIER/inexistant.txt") == NULL);

    Hashtable_Put(hashtable, "/CHEMIN/VERS/UN/FICHIER/test.txt", &navi);
    assert(Hashtable_Get(hashtable, "/CHEMIN/VERS/UN/FICHIER/test.txt") == &navi);

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

    printf("Tous les tests ont reussi avec succes !\n");

    return EXIT_SUCCESS;
}