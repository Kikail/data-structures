#include <assert.h>
#include "../src/linked-list/linked-list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
    NPC zelda   = {"Zelda", 100};
    NPC link    = {"Link", 200};
    NPC chicken = {"Chicken", 10};
    NPC ganon   = {"Ganon", 5000};
    NPC epona   = {"Epona", 150};
    NPC navi    = {"Navi", 1};

    LinkedList* list = LinkedList_CreateEmpty();

    assert(LinkedList_IsEmpty(list) == true);
    assert(list->size == 0);

    LinkedList_RemoveHead(list);
    LinkedList_RemoveTail(list);
    LinkedList_RemoveAt(list, 0);
    assert(LinkedList_ExtractHead(list) == NULL);
    assert(LinkedList_ExtractTail(list) == NULL);
    assert(LinkedList_ExtractAt(list, 5) == NULL);

    LinkedList_PutHead(list, &link);
    assert(!LinkedList_IsEmpty(list));
    assert(list->size == 1);
    assert(list->head->data == &link);
    assert(list->tail->data == &link);

    LinkedList_RemoveHead(list);
    assert(LinkedList_IsEmpty(list));
    assert(list->head == NULL);
    assert(list->tail == NULL);
    assert(list->size == 0);

    LinkedList_PutTail(list, &zelda);
    LinkedList_RemoveTail(list);
    assert(LinkedList_IsEmpty(list));
    assert(list->head == NULL);
    assert(list->tail == NULL);

    LinkedList_PutHead(list, &link);
    LinkedList_PutHead(list, &zelda);
    LinkedList_PutTail(list, &ganon);

    assert(list->size == 3);
    assert(list->head->data == &zelda);
    assert(list->tail->data == &ganon);

    LinkedList_PutAt(list, &chicken, 0);
    assert(list->head->data == &chicken);

    LinkedList_PutAt(list, &epona, list->size);
    assert(list->tail->data == &epona);

    LinkedList_PutAt(list, &navi, 2);

    assert(list->size == 6);

    NPC* extracted = (NPC*)LinkedList_ExtractHead(list);
    assert(extracted == &chicken);
    assert(list->size == 5);

    extracted = (NPC*)LinkedList_ExtractTail(list);
    assert(extracted == &epona);
    assert(list->size == 4);

    extracted = (NPC*)LinkedList_ExtractAt(list, 1);
    assert(extracted == &navi);
    assert(list->size == 3);

    LinkedList_RemoveAt(list, 0);

    LinkedList_RemoveAt(list, list->size - 1);

    assert(list->size == 1);

    LinkedList_RemoveHead(list);
    assert(LinkedList_IsEmpty(list));

    for (int i = 0; i < 100; i++) {
        LinkedList_PutTail(list, &chicken);
    }
    assert(list->size == 100);

    for (int i = 0; i < 100; i++) {
        LinkedList_RemoveHead(list);
    }
    assert(LinkedList_IsEmpty(list));

    LinkedList_PutHead(list, &zelda);
    LinkedList_PutTail(list, &link);
    LinkedList_PutTail(list, &ganon);

    LinkedList_Destroy(list);
}

/* ---------- Comportement FIFO : PutTail puis ExtractHead ---------- */
static void test_fifo(void) {
    enum { N = 50 };
    int values[N];
    LinkedList* list = LinkedList_CreateEmpty();

    for (int i = 0; i < N; i++) {
        values[i] = i;
        LinkedList_PutTail(list, &values[i]);
        assert(list->tail->data == &values[i]);
        assert(list->head->data == &values[0]);
    }
    assert(list->size == N);

    for (int i = 0; i < N; i++) {
        assert(LinkedList_ExtractHead(list) == &values[i]);
        assert((int)list->size == N - 1 - i);
    }
    assert(LinkedList_IsEmpty(list));
    assert(list->head == NULL);
    assert(list->tail == NULL);

    LinkedList_Destroy(list);
}

/* ---------- Comportement LIFO : PutHead puis ExtractHead ---------- */
static void test_lifo(void) {
    enum { N = 50 };
    int values[N];
    LinkedList* list = LinkedList_CreateEmpty();

    for (int i = 0; i < N; i++) {
        values[i] = i;
        LinkedList_PutHead(list, &values[i]);
        assert(list->head->data == &values[i]);
        assert(list->tail->data == &values[0]);
    }

    for (int i = N - 1; i >= 0; i--) {
        assert(LinkedList_ExtractHead(list) == &values[i]);
    }
    assert(LinkedList_IsEmpty(list));

    LinkedList_Destroy(list);
}

/* ---------- ExtractTail renvoie les elements en ordre inverse ---------- */
static void test_extract_tail(void) {
    enum { N = 30 };
    int values[N];
    LinkedList* list = LinkedList_CreateEmpty();

    for (int i = 0; i < N; i++) {
        values[i] = i;
        LinkedList_PutTail(list, &values[i]);
    }

    for (int i = N - 1; i >= 0; i--) {
        assert(LinkedList_ExtractTail(list) == &values[i]);
        if (i > 0) {
            assert(list->tail->data == &values[i - 1]);
        }
    }
    assert(LinkedList_IsEmpty(list));
    assert(list->head == NULL);
    assert(list->tail == NULL);

    LinkedList_Destroy(list);
}

/* ---------- Un seul element : head et tail identiques, toutes les extractions ---------- */
static void test_un_element(void) {
    int a = 1;
    LinkedList* list = LinkedList_CreateEmpty();

    /* ExtractHead */
    LinkedList_PutTail(list, &a);
    assert(list->head == list->tail);
    assert(LinkedList_ExtractHead(list) == &a);
    assert(LinkedList_IsEmpty(list));
    assert(list->head == NULL && list->tail == NULL);

    /* ExtractTail */
    LinkedList_PutHead(list, &a);
    assert(LinkedList_ExtractTail(list) == &a);
    assert(LinkedList_IsEmpty(list));
    assert(list->head == NULL && list->tail == NULL);

    /* ExtractAt(0) */
    LinkedList_PutHead(list, &a);
    assert(LinkedList_ExtractAt(list, 0) == &a);
    assert(LinkedList_IsEmpty(list));
    assert(list->head == NULL && list->tail == NULL);

    /* RemoveAt(0) */
    LinkedList_PutHead(list, &a);
    LinkedList_RemoveAt(list, 0);
    assert(LinkedList_IsEmpty(list));
    assert(list->head == NULL && list->tail == NULL);

    /* PutAt(0) sur liste vide */
    LinkedList_PutAt(list, &a, 0);
    assert(list->size == 1);
    assert(list->head->data == &a);
    assert(list->tail->data == &a);

    LinkedList_Destroy(list);
}

/* ---------- PutAt : insertion en debut, milieu et fin ---------- */
static void test_putat_positions(void) {
    int v[5] = {0, 1, 2, 3, 4};
    LinkedList* list = LinkedList_CreateEmpty();

    LinkedList_PutAt(list, &v[0], 0);               /* [0]          */
    LinkedList_PutAt(list, &v[4], list->size);      /* [0, 4]       */
    LinkedList_PutAt(list, &v[2], 1);               /* [0, 2, 4]    */
    LinkedList_PutAt(list, &v[1], 1);               /* [0, 1, 2, 4] */
    LinkedList_PutAt(list, &v[3], 3);               /* [0, 1, 2, 3, 4] */

    assert(list->size == 5);
    assert(list->head->data == &v[0]);
    assert(list->tail->data == &v[4]);

    for (int i = 0; i < 5; i++) {
        assert(LinkedList_ExtractAt(list, 0) == &v[i]);
    }
    assert(LinkedList_IsEmpty(list));

    LinkedList_Destroy(list);
}

/* ---------- ExtractAt : milieu, dernier element ---------- */
static void test_extractat_positions(void) {
    int v[6] = {0, 1, 2, 3, 4, 5};
    LinkedList* list = LinkedList_CreateEmpty();

    for (int i = 0; i < 6; i++) {
        LinkedList_PutTail(list, &v[i]);
    }

    /* Milieu */
    assert(LinkedList_ExtractAt(list, 2) == &v[2]);     /* [0,1,3,4,5] */
    assert(list->size == 5);

    /* Dernier : doit mettre a jour tail */
    assert(LinkedList_ExtractAt(list, list->size - 1) == &v[5]);  /* [0,1,3,4] */
    assert(list->size == 4);
    assert(list->tail->data == &v[4]);

    /* Premier : doit mettre a jour head */
    assert(LinkedList_ExtractAt(list, 0) == &v[0]);     /* [1,3,4] */
    assert(list->head->data == &v[1]);

    assert(LinkedList_ExtractHead(list) == &v[1]);
    assert(LinkedList_ExtractHead(list) == &v[3]);
    assert(LinkedList_ExtractHead(list) == &v[4]);
    assert(LinkedList_IsEmpty(list));

    LinkedList_Destroy(list);
}

/* ---------- Indices hors limites : l'index est ramene a la queue (comme PutAt) ---------- */
static void test_indices_hors_limites(void) {
    int v[5] = {0, 1, 2, 3, 4};
    LinkedList* list = LinkedList_CreateEmpty();

    for (int i = 0; i < 5; i++) {
        LinkedList_PutTail(list, &v[i]);
    }

    assert(LinkedList_ExtractAt(list, 100) == &v[4]);   /* [0,1,2,3] */
    assert(list->size == 4);
    assert(list->tail->data == &v[3]);

    LinkedList_RemoveAt(list, 100);                     /* [0,1,2] */
    assert(list->size == 3);
    assert(list->tail->data == &v[2]);

    LinkedList_PutAt(list, &v[4], 100);                 /* [0,1,2,4] */
    assert(list->size == 4);
    assert(list->tail->data == &v[4]);

    LinkedList_Destroy(list);
}

/* ---------- RemoveHead / RemoveTail successifs sur liste partiellement remplie ---------- */
static void test_remove_alternes(void) {
    int v[6] = {0, 1, 2, 3, 4, 5};
    LinkedList* list = LinkedList_CreateEmpty();

    for (int i = 0; i < 6; i++) {
        LinkedList_PutTail(list, &v[i]);
    }

    LinkedList_RemoveHead(list);   /* [1,2,3,4,5] */
    LinkedList_RemoveTail(list);   /* [1,2,3,4]   */
    assert(list->size == 4);
    assert(list->head->data == &v[1]);
    assert(list->tail->data == &v[4]);

    LinkedList_RemoveHead(list);   /* [2,3,4] */
    LinkedList_RemoveTail(list);   /* [2,3]   */
    assert(list->size == 2);
    assert(list->head->data == &v[2]);
    assert(list->tail->data == &v[3]);

    LinkedList_RemoveHead(list);
    LinkedList_RemoveTail(list);
    assert(LinkedList_IsEmpty(list));
    assert(list->head == NULL && list->tail == NULL);

    LinkedList_Destroy(list);
}

/* ---------- Reutilisation de la liste apres l'avoir videe ---------- */
static void test_reutilisation_apres_vidage(void) {
    int a = 1, b = 2, c = 3;
    LinkedList* list = LinkedList_CreateEmpty();

    for (int round = 0; round < 10; round++) {
        LinkedList_PutTail(list, &a);
        LinkedList_PutTail(list, &b);
        LinkedList_PutHead(list, &c);   /* [c, a, b] */
        assert(list->size == 3);
        assert(LinkedList_ExtractHead(list) == &c);
        assert(LinkedList_ExtractHead(list) == &a);
        assert(LinkedList_ExtractHead(list) == &b);
        assert(LinkedList_IsEmpty(list));
    }

    LinkedList_Destroy(list);
}

/* ---------- Grosse liste ---------- */
static void test_grande_liste(void) {
    enum { N = 10000 };
    static int values[N];
    LinkedList* list = LinkedList_CreateEmpty();

    for (int i = 0; i < N; i++) {
        values[i] = i;
        LinkedList_PutTail(list, &values[i]);
    }
    assert(list->size == N);

    /* Acces par indice au milieu et a la fin */
    assert(LinkedList_ExtractAt(list, N / 2) == &values[N / 2]);
    assert(list->size == N - 1);
    assert(LinkedList_ExtractAt(list, list->size - 1) == &values[N - 1]);
    assert(list->size == N - 2);

    LinkedList_Destroy(list);   /* doit liberer 9998 noeuds (verifier avec valgrind) */
}

/* ---------- Destroy sur liste vide ---------- */
static void test_destroy_liste_vide(void) {
    LinkedList* list = LinkedList_CreateEmpty();
    LinkedList_Destroy(list);
}

int main(const int argc, const char *argv[]) {
    test_basique();
    test_fifo();
    test_lifo();
    test_extract_tail();
    test_un_element();
    test_putat_positions();
    test_extractat_positions();
    test_indices_hors_limites();
    test_remove_alternes();
    test_reutilisation_apres_vidage();
    test_grande_liste();
    test_destroy_liste_vide();

    printf("Tous les tests ont reussi avec succes !\n");

    return EXIT_SUCCESS;
}