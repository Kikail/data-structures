#include "../src/dynamic-array/dynamic-array.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct NPC {
    char name[32];
    unsigned int health;
};
typedef struct NPC NPC;

/* ---------- Tests de base (originaux) ---------- */
static void test_basique(void) {
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
}

/* ---------- Tableau vide ---------- */
static void test_tableau_vide(void) {
    DynamicArray* array = DynamicArray_CreateEmpty();
    assert(DynamicArray_Get(array, 0) == NULL);
    assert(DynamicArray_Get(array, array->capacity) == NULL);
    assert(DynamicArray_Get(array, 99999) == NULL);
    DynamicArray_Print(array);   /* ne doit pas planter sur un tableau vide */
    DynamicArray_Destroy(array);
}

/* ---------- Capacite de depart minimale ---------- */
static void test_capacite_un(void) {
    DynamicArray* array = DynamicArray_CreateEmptyWithCapacity(1);
    assert(array != NULL);
    assert(array->capacity == 1);

    int a = 1, b = 2, c = 3, d = 4, e = 5;

    DynamicArray_Put(array, &a);
    assert(array->size == 1);
    assert(array->capacity == 1);

    DynamicArray_Put(array, &b);
    assert(array->size == 2);
    assert(array->capacity == 2);

    DynamicArray_Put(array, &c);
    assert(array->size == 3);
    assert(array->capacity == 4);

    DynamicArray_Put(array, &d);
    assert(array->size == 4);
    assert(array->capacity == 4);

    DynamicArray_Put(array, &e);
    assert(array->size == 5);
    assert(array->capacity == 8);

    assert(DynamicArray_Get(array, 0) == &a);
    assert(DynamicArray_Get(array, 1) == &b);
    assert(DynamicArray_Get(array, 2) == &c);
    assert(DynamicArray_Get(array, 3) == &d);
    assert(DynamicArray_Get(array, 4) == &e);

    DynamicArray_Destroy(array);
}

/* ---------- Beaucoup d'insertions : l'ordre et les valeurs sont conserves ---------- */
static void test_grand_nombre_insertions(void) {
    enum { N = 5000 };
    static int values[N];
    DynamicArray* array = DynamicArray_CreateEmptyWithCapacity(2);

    for (int i = 0; i < N; i++) {
        values[i] = i;
        DynamicArray_Put(array, &values[i]);
        assert((int)array->size == i + 1);
        assert((int)array->capacity >= i + 1);
    }

    for (int i = 0; i < N; i++) {
        assert(DynamicArray_Get(array, i) == &values[i]);
    }

    assert(DynamicArray_Get(array, N) == NULL);

    DynamicArray_Destroy(array);
}

/* ---------- La capacite ne diminue jamais lors de Put ---------- */
static void test_capacite_croissante(void) {
    DynamicArray* array = DynamicArray_CreateEmptyWithCapacity(2);
    int v = 0;
    size_t derniere_capacite = array->capacity;

    for (int i = 0; i < 500; i++) {
        DynamicArray_Put(array, &v);
        assert(array->capacity >= derniere_capacite);
        assert(array->capacity >= array->size);
        derniere_capacite = array->capacity;
    }

    DynamicArray_Destroy(array);
}

/* ---------- PutAt a l'indice 0 sur tableau vide ---------- */
static void test_putat_zero(void) {
    DynamicArray* array = DynamicArray_CreateEmptyWithCapacity(4);
    NPC zelda = {"zelda", 100};
    NPC link  = {"link", 200};

    DynamicArray_PutAt(array, 0, &zelda);
    assert(array->size == 1);
    assert(DynamicArray_Get(array, 0) == &zelda);

    /* Ecrasement : la taille ne change pas */
    DynamicArray_PutAt(array, 0, &link);
    assert(array->size == 1);
    assert(DynamicArray_Get(array, 0) == &link);

    DynamicArray_Destroy(array);
}

/* ---------- PutAt au dela de la capacite : agrandissement ---------- */
static void test_putat_hors_capacite(void) {
    DynamicArray* array = DynamicArray_CreateEmptyWithCapacity(2);
    int a = 1, b = 2;

    DynamicArray_Put(array, &a);
    DynamicArray_PutAt(array, 100, &b);

    assert(array->capacity > 100);
    assert(DynamicArray_Get(array, 0) == &a);     /* ancien contenu conserve */
    assert(DynamicArray_Get(array, 100) == &b);
    assert(array->size == 2);

    DynamicArray_Destroy(array);
}

/* ---------- SetCapacity : agrandir conserve les donnees ---------- */
static void test_setcapacity_agrandir(void) {
    DynamicArray* array = DynamicArray_CreateEmptyWithCapacity(4);
    int values[4] = {10, 20, 30, 40};

    for (int i = 0; i < 4; i++) {
        DynamicArray_Put(array, &values[i]);
    }

    DynamicArray_SetCapacity(array, 1000);
    assert(array->capacity == 1000);
    assert(array->size == 4);

    for (int i = 0; i < 4; i++) {
        assert(DynamicArray_Get(array, i) == &values[i]);
    }

    DynamicArray_Destroy(array);
}

/* ---------- SetCapacity a la meme valeur : sans effet ---------- */
static void test_setcapacity_identique(void) {
    DynamicArray* array = DynamicArray_CreateEmptyWithCapacity(8);
    int a = 1, b = 2;

    DynamicArray_Put(array, &a);
    DynamicArray_Put(array, &b);

    DynamicArray_SetCapacity(array, 8);
    assert(array->capacity == 8);
    assert(array->size == 2);
    assert(DynamicArray_Get(array, 0) == &a);
    assert(DynamicArray_Get(array, 1) == &b);

    DynamicArray_Destroy(array);
}

/* ---------- Plusieurs tableaux independants ---------- */
static void test_tableaux_independants(void) {
    DynamicArray* a1 = DynamicArray_CreateEmpty();
    DynamicArray* a2 = DynamicArray_CreateEmpty();
    int x = 1, y = 2;

    DynamicArray_Put(a1, &x);
    assert(a1->size == 1);
    assert(a2->size == 0);

    DynamicArray_Put(a2, &y);
    assert(DynamicArray_Get(a1, 0) == &x);
    assert(DynamicArray_Get(a2, 0) == &y);

    DynamicArray_Destroy(a1);
    DynamicArray_Destroy(a2);
}

/* ---------- Cycles de creation / destruction (fuites : lancer avec valgrind) ---------- */
static void test_creation_destruction_repetee(void) {
    int v = 0;
    for (int i = 0; i < 1000; i++) {
        DynamicArray* array = DynamicArray_CreateEmptyWithCapacity(1 + (i % 16));
        for (int j = 0; j < 20; j++) {
            DynamicArray_Put(array, &v);
        }
        DynamicArray_Destroy(array);
    }
}

int main(const int argc, const char *argv[]) {
    test_basique();
    test_tableau_vide();
    test_capacite_un();
    test_grand_nombre_insertions();
    test_capacite_croissante();
    test_putat_zero();
    test_putat_hors_capacite();
    test_setcapacity_agrandir();
    test_setcapacity_identique();
    test_tableaux_independants();
    test_creation_destruction_repetee();

    printf("Tous les tests ont reussi avec succes !\n");

    return EXIT_SUCCESS;
}