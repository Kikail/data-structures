#include "../src/hashtable/hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct NPC {
    char name[32];
    unsigned int health;
};
typedef struct NPC NPC;

void NPC_Afficher(NPC npc) {
    printf("{%s %u}\n", npc.name, npc.health);
}

/* ---------- Tests de base (originaux) ---------- */
static void test_basique(void) {
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
}

/* ---------- Table vide ---------- */
static void test_table_vide(void) {
    Hashtable* ht = Hashtable_CreateEmpty();
    assert(Hashtable_Get(ht, "n'importe quoi") == NULL);
    assert(Hashtable_Get(ht, "") == NULL);
    Hashtable_Print(ht);
    Hashtable_Destroy(ht);
}

/* ---------- Collisions forcees : capacite 1, tout tombe dans le meme bucket ---------- */
static void test_collisions_capacite_un(void) {
    Hashtable* ht = Hashtable_CreateEmptyWithCapacity(1);
    assert(ht != NULL);
    assert(ht->capacity == 1);

    int a = 1, b = 2, c = 3, d = 4;

    Hashtable_Put(ht, "alpha", &a);
    Hashtable_Put(ht, "beta", &b);
    Hashtable_Put(ht, "gamma", &c);
    Hashtable_Put(ht, "delta", &d);

    assert(Hashtable_Get(ht, "alpha") == &a);
    assert(Hashtable_Get(ht, "beta") == &b);
    assert(Hashtable_Get(ht, "gamma") == &c);
    assert(Hashtable_Get(ht, "delta") == &d);
    assert(Hashtable_Get(ht, "epsilon") == NULL);

    /* Ecrasement au milieu d'une chaine de collisions */
    int nouveau = 99;
    Hashtable_Put(ht, "beta", &nouveau);
    assert(Hashtable_Get(ht, "beta") == &nouveau);
    assert(Hashtable_Get(ht, "alpha") == &a);
    assert(Hashtable_Get(ht, "gamma") == &c);
    assert(Hashtable_Get(ht, "delta") == &d);

    Hashtable_Destroy(ht);
}

/* ---------- Beaucoup de cles dans une petite table ---------- */
static void test_beaucoup_de_cles(void) {
    enum { N = 500 };
    static char keys[N][32];
    static int values[N];

    Hashtable* ht = Hashtable_CreateEmptyWithCapacity(3);

    for (int i = 0; i < N; i++) {
        snprintf(keys[i], sizeof(keys[i]), "cle_%d", i);
        values[i] = i;
        Hashtable_Put(ht, keys[i], &values[i]);
    }

    for (int i = 0; i < N; i++) {
        assert(Hashtable_Get(ht, keys[i]) == &values[i]);
    }

    assert(Hashtable_Get(ht, "cle_500") == NULL);
    assert(Hashtable_Get(ht, "cle_") == NULL);
    assert(Hashtable_Get(ht, "cle") == NULL);

    Hashtable_Destroy(ht);
}

/* ---------- Ecrasements successifs de la meme cle ---------- */
static void test_ecrasements_repetes(void) {
    Hashtable* ht = Hashtable_CreateEmpty();
    int values[100];

    for (int i = 0; i < 100; i++) {
        values[i] = i;
        Hashtable_Put(ht, "unique", &values[i]);
        assert(Hashtable_Get(ht, "unique") == &values[i]);
    }

    Hashtable_Destroy(ht);
}

/* ---------- Cles proches mais differentes ---------- */
static void test_cles_proches(void) {
    Hashtable* ht = Hashtable_CreateEmpty();
    int a = 1, b = 2, c = 3, d = 4;

    Hashtable_Put(ht, "abc", &a);
    Hashtable_Put(ht, "abd", &b);
    Hashtable_Put(ht, "ABC", &c);   /* la casse compte */
    Hashtable_Put(ht, "abc ", &d);  /* espace final */

    assert(Hashtable_Get(ht, "abc") == &a);
    assert(Hashtable_Get(ht, "abd") == &b);
    assert(Hashtable_Get(ht, "ABC") == &c);
    assert(Hashtable_Get(ht, "abc ") == &d);
    assert(Hashtable_Get(ht, "ab") == NULL);

    Hashtable_Destroy(ht);
}

/* ---------- Anagrammes (mauvaises fonctions de hash : somme des caracteres) ---------- */
static void test_anagrammes(void) {
    Hashtable* ht = Hashtable_CreateEmpty();
    int a = 1, b = 2, c = 3;

    Hashtable_Put(ht, "listen", &a);
    Hashtable_Put(ht, "silent", &b);
    Hashtable_Put(ht, "enlist", &c);

    assert(Hashtable_Get(ht, "listen") == &a);
    assert(Hashtable_Get(ht, "silent") == &b);
    assert(Hashtable_Get(ht, "enlist") == &c);

    Hashtable_Destroy(ht);
}

/* ---------- Cle vide et cle longue ---------- */
static void test_cles_limites(void) {
    Hashtable* ht = Hashtable_CreateEmpty();
    int vide = 1, longue = 2;

    char cle_longue[2048];
    memset(cle_longue, 'x', sizeof(cle_longue) - 1);
    cle_longue[sizeof(cle_longue) - 1] = '\0';

    Hashtable_Put(ht, "", &vide);
    Hashtable_Put(ht, cle_longue, &longue);

    assert(Hashtable_Get(ht, "") == &vide);
    assert(Hashtable_Get(ht, cle_longue) == &longue);

    char autre_cle[2048];
    memcpy(autre_cle, cle_longue, sizeof(autre_cle));
    autre_cle[sizeof(autre_cle) - 2] = 'y';   /* un seul caractere de difference */
    assert(Hashtable_Get(ht, autre_cle) == NULL);

    Hashtable_Destroy(ht);
}

/* ---------- Plusieurs tables independantes ---------- */
static void test_tables_independantes(void) {
    Hashtable* h1 = Hashtable_CreateEmpty();
    Hashtable* h2 = Hashtable_CreateEmpty();
    int a = 1, b = 2;

    Hashtable_Put(h1, "k", &a);
    assert(Hashtable_Get(h2, "k") == NULL);

    Hashtable_Put(h2, "k", &b);
    assert(Hashtable_Get(h1, "k") == &a);
    assert(Hashtable_Get(h2, "k") == &b);

    Hashtable_Destroy(h1);
    Hashtable_Destroy(h2);
}

/* ---------- Cycles de creation / destruction (fuites : lancer avec valgrind) ---------- */
static void test_creation_destruction_repetee(void) {
    int v = 0;
    /* La table stocke le pointeur de cle (pas de copie) : les cles doivent rester valides */
    static char cles[20][16];
    for (int j = 0; j < 20; j++) snprintf(cles[j], sizeof(cles[j]), "k%d", j);
    for (int i = 0; i < 500; i++) {
        Hashtable* ht = Hashtable_CreateEmptyWithCapacity(1 + (i % 10));
        for (int j = 0; j < 20; j++) {
            Hashtable_Put(ht, cles[j], &v);
        }
        Hashtable_Destroy(ht);
    }
}

int main(const int argc, const char *argv[]) {
    test_basique();
    test_table_vide();
    test_collisions_capacite_un();
    test_beaucoup_de_cles();
    test_ecrasements_repetes();
    test_cles_proches();
    test_anagrammes();
    test_cles_limites();
    test_tables_independantes();
    test_creation_destruction_repetee();

    printf("Tous les tests ont reussi avec succes !\n");

    return EXIT_SUCCESS;
}