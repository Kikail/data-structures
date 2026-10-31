#include <assert.h>
#include "../src/stack/stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct NPC {
    char name[32];
    unsigned int health;
};
typedef struct NPC NPC;

/* ---------- Tests de base (originaux) ---------- */
static void test_basique(void) {
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
}

/* ---------- Capacite 1 ---------- */
static void test_capacite_un(void) {
    int a = 1, b = 2;
    Stack* stack = Stack_CreateEmptyWithCapacity(1);

    assert(Stack_IsEmpty(stack) == true);
    assert(Stack_IsFull(stack) == false);

    assert(Stack_Push(stack, &a) == true);
    assert(Stack_IsEmpty(stack) == false);
    assert(Stack_IsFull(stack) == true);

    assert(Stack_Push(stack, &b) == false);   /* pile pleine : refus */

    assert(Stack_Pop(stack) == &a);           /* b n'a pas ete empile */
    assert(Stack_IsEmpty(stack) == true);
    assert(Stack_IsFull(stack) == false);

    assert(Stack_Push(stack, &b) == true);
    assert(Stack_Pop(stack) == &b);

    Stack_Destroy(stack);
}

/* ---------- Pop repetes sur pile vide ---------- */
static void test_pop_pile_vide(void) {
    int a = 1;
    Stack* stack = Stack_CreateEmptyWithCapacity(5);

    for (int i = 0; i < 10; i++) {
        assert(Stack_Pop(stack) == NULL);
        assert(Stack_IsEmpty(stack) == true);
    }

    /* La pile fonctionne toujours apres des Pop a vide */
    assert(Stack_Push(stack, &a) == true);
    assert(Stack_Pop(stack) == &a);
    assert(Stack_Pop(stack) == NULL);

    Stack_Destroy(stack);
}

/* ---------- Push repetes sur pile pleine ---------- */
static void test_push_pile_pleine(void) {
    int values[4] = {0, 1, 2, 3};
    int extra = 99;
    Stack* stack = Stack_CreateEmptyWithCapacity(4);

    for (int i = 0; i < 4; i++) {
        assert(Stack_Push(stack, &values[i]) == true);
    }
    assert(Stack_IsFull(stack) == true);

    for (int i = 0; i < 10; i++) {
        assert(Stack_Push(stack, &extra) == false);
        assert(Stack_IsFull(stack) == true);
    }

    /* Le contenu n'a pas ete corrompu par les push refuses */
    for (int i = 3; i >= 0; i--) {
        assert(Stack_Pop(stack) == &values[i]);
    }
    assert(Stack_IsEmpty(stack) == true);

    Stack_Destroy(stack);
}

/* ---------- Ordre LIFO sur une grande pile ---------- */
static void test_lifo_grande_pile(void) {
    enum { N = 10000 };
    static int values[N];
    Stack* stack = Stack_CreateEmptyWithCapacity(N);

    for (int i = 0; i < N; i++) {
        values[i] = i;
        assert(Stack_Push(stack, &values[i]) == true);
        assert(Stack_IsEmpty(stack) == false);
    }
    assert(Stack_IsFull(stack) == true);
    assert(Stack_Push(stack, &values[0]) == false);

    for (int i = N - 1; i >= 0; i--) {
        assert(Stack_Pop(stack) == &values[i]);
        assert(Stack_IsFull(stack) == false);
    }
    assert(Stack_IsEmpty(stack) == true);
    assert(Stack_Pop(stack) == NULL);

    Stack_Destroy(stack);
}

/* ---------- Alternance Push / Pop ---------- */
static void test_alternance_push_pop(void) {
    int values[100];
    Stack* stack = Stack_CreateEmptyWithCapacity(2);

    for (int i = 0; i < 100; i++) {
        values[i] = i;
        assert(Stack_Push(stack, &values[i]) == true);
        assert(Stack_Pop(stack) == &values[i]);
        assert(Stack_IsEmpty(stack) == true);
    }

    Stack_Destroy(stack);
}

/* ---------- Remplissage partiel : ni vide ni pleine ---------- */
static void test_etat_intermediaire(void) {
    int a = 1, b = 2;
    Stack* stack = Stack_CreateEmptyWithCapacity(5);

    assert(Stack_Push(stack, &a) == true);
    assert(Stack_IsEmpty(stack) == false);
    assert(Stack_IsFull(stack) == false);

    assert(Stack_Push(stack, &b) == true);
    assert(Stack_IsEmpty(stack) == false);
    assert(Stack_IsFull(stack) == false);

    assert(Stack_Pop(stack) == &b);
    assert(Stack_IsEmpty(stack) == false);
    assert(Stack_Pop(stack) == &a);
    assert(Stack_IsEmpty(stack) == true);

    Stack_Destroy(stack);
}

/* ---------- Remplir / vider plusieurs fois ---------- */
static void test_cycles_remplissage(void) {
    int values[8];
    Stack* stack = Stack_CreateEmptyWithCapacity(8);

    for (int cycle = 0; cycle < 20; cycle++) {
        for (int i = 0; i < 8; i++) {
            values[i] = cycle * 8 + i;
            assert(Stack_Push(stack, &values[i]) == true);
        }
        assert(Stack_IsFull(stack) == true);

        for (int i = 7; i >= 0; i--) {
            assert(Stack_Pop(stack) == &values[i]);
        }
        assert(Stack_IsEmpty(stack) == true);
    }

    Stack_Destroy(stack);
}

/* ---------- Piles independantes ---------- */
static void test_piles_independantes(void) {
    int a = 1, b = 2;
    Stack* s1 = Stack_CreateEmptyWithCapacity(2);
    Stack* s2 = Stack_CreateEmptyWithCapacity(2);

    Stack_Push(s1, &a);
    assert(Stack_IsEmpty(s2) == true);
    assert(Stack_Pop(s2) == NULL);

    Stack_Push(s2, &b);
    assert(Stack_Pop(s1) == &a);
    assert(Stack_Pop(s2) == &b);

    Stack_Destroy(s1);
    Stack_Destroy(s2);
}

/* ---------- Cycles de creation / destruction (fuites : lancer avec valgrind) ---------- */
static void test_creation_destruction_repetee(void) {
    int v = 0;
    for (int i = 0; i < 1000; i++) {
        Stack* stack = Stack_CreateEmptyWithCapacity(1 + (i % 32));
        Stack_Push(stack, &v);
        Stack_Destroy(stack);
    }
}

int main(const int argc, const char *argv[]) {
    test_basique();
    test_capacite_un();
    test_pop_pile_vide();
    test_push_pile_pleine();
    test_lifo_grande_pile();
    test_alternance_push_pop();
    test_etat_intermediaire();
    test_cycles_remplissage();
    test_piles_independantes();
    test_creation_destruction_repetee();

    printf("Tous les tests de la pile ont reussi avec succes !\n");

    return EXIT_SUCCESS;
}