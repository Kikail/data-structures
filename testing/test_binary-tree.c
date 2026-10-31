#include "../src/binary-tree/binary-tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

struct NPC {
    char name[32];
    unsigned int health;
};
typedef struct NPC NPC;

int compare_ints(void* a, void* b) {
    int arg1 = *(int*)a;
    int arg2 = *(int*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

/* ---------- Tests de base (originaux) ---------- */
static void test_basique(void) {
    BinaryTree* tree_null = BinaryTree_CreateEmpty(NULL);
    assert(tree_null == NULL);

    BinaryTree* tree = BinaryTree_CreateEmpty(compare_ints);
    assert(tree != NULL);
    assert(tree->root == NULL);
    assert(tree->size == 0);

    NPC zelda   = {"zelda", 100};
    NPC link    = {"link", 200};
    NPC chicken = {"chicken", 10};
    NPC ganon   = {"ganon", 5000};
    NPC navi    = {"navi", 1};

    int key_zelda   = 50;
    int key_link    = 20;
    int key_chicken = 80;
    int key_ganon   = 10;
    int key_navi    = 30;
    int key_missing = 99;

    BinaryTree_Put(tree, &zelda, &key_zelda);
    assert(tree->size == 1);
    assert(tree->root != NULL);
    assert(tree->root->parent == NULL);
    assert(BinaryTree_Get(tree, &key_zelda) == &zelda);

    BinaryTree_Put(tree, &link, &key_link);
    assert(tree->size == 2);
    assert(tree->root->left != NULL);
    assert(tree->root->left->parent == tree->root);
    assert(BinaryTree_Get(tree, &key_link) == &link);

    BinaryTree_Put(tree, &chicken, &key_chicken);
    assert(tree->size == 3);
    assert(tree->root->right != NULL);
    assert(tree->root->right->parent == tree->root);
    assert(BinaryTree_Get(tree, &key_chicken) == &chicken);

    BinaryTree_Put(tree, &ganon, &key_ganon);
    assert(tree->size == 4);
    assert(tree->root->left->left != NULL);
    assert(tree->root->left->left->parent == tree->root->left);
    assert(BinaryTree_Get(tree, &key_ganon) == &ganon);

    BinaryTree_Put(tree, &navi, &key_navi);
    assert(tree->size == 5);
    assert(tree->root->left->right != NULL);
    assert(tree->root->left->right->parent == tree->root->left);
    assert(BinaryTree_Get(tree, &key_navi) == &navi);

    assert(BinaryTree_Get(tree, &key_missing) == NULL);

    BinaryTree_Put(tree, &navi, &key_zelda);
    assert(tree->size == 5);
    assert(BinaryTree_Get(tree, &key_zelda) == &navi);

    BinaryTree_Put(tree, &zelda, &key_zelda);
    assert(tree->size == 5);
    assert(BinaryTree_Get(tree, &key_zelda) == &zelda);

    BinaryTree_Print(tree);
    BinaryTree_Destroy(tree);
}

/* ---------- Arbre vide ---------- */
static void test_arbre_vide(void) {
    BinaryTree* tree = BinaryTree_CreateEmpty(compare_ints);
    int key = 42;
    assert(BinaryTree_Get(tree, &key) == NULL);
    assert(tree->size == 0);
    BinaryTree_Print(tree);   /* ne doit pas planter sur un arbre vide */
    BinaryTree_Destroy(tree);
}

/* ---------- Un seul element ---------- */
static void test_un_seul_element(void) {
    BinaryTree* tree = BinaryTree_CreateEmpty(compare_ints);
    NPC zelda = {"zelda", 100};
    int key = 7;

    BinaryTree_Put(tree, &zelda, &key);
    assert(tree->size == 1);
    assert(tree->root->left == NULL);
    assert(tree->root->right == NULL);
    assert(tree->root->parent == NULL);
    assert(BinaryTree_Get(tree, &key) == &zelda);

    BinaryTree_Destroy(tree);
}

/* ---------- Insertion croissante (arbre degenere en liste a droite) ---------- */
static void test_insertion_croissante(void) {
    enum { N = 200 };
    BinaryTree* tree = BinaryTree_CreateEmpty(compare_ints);
    int keys[N];
    int values[N];

    for (int i = 0; i < N; i++) {
        keys[i] = i;
        values[i] = i * 10;
        BinaryTree_Put(tree, &values[i], &keys[i]);
        assert((int)tree->size == i + 1);
    }

    /* Chaque noeud n'a qu'un enfant droit */
    assert(tree->root->left == NULL);
    assert(tree->root->right != NULL);
    assert(tree->root->right->parent == tree->root);

    for (int i = 0; i < N; i++) {
        assert(BinaryTree_Get(tree, &keys[i]) == &values[i]);
    }

    int missing = N + 1;
    assert(BinaryTree_Get(tree, &missing) == NULL);

    BinaryTree_Destroy(tree);
}

/* ---------- Insertion decroissante (degenere a gauche) ---------- */
static void test_insertion_decroissante(void) {
    enum { N = 200 };
    BinaryTree* tree = BinaryTree_CreateEmpty(compare_ints);
    int keys[N];
    int values[N];

    for (int i = 0; i < N; i++) {
        keys[i] = N - i;
        values[i] = i;
        BinaryTree_Put(tree, &values[i], &keys[i]);
    }

    assert((int)tree->size == N);
    assert(tree->root->right == NULL);
    assert(tree->root->left != NULL);

    for (int i = 0; i < N; i++) {
        assert(BinaryTree_Get(tree, &keys[i]) == &values[i]);
    }

    BinaryTree_Destroy(tree);
}

/* ---------- Insertion pseudo-aleatoire ---------- */
static void test_insertion_aleatoire(void) {
    enum { N = 1000 };
    BinaryTree* tree = BinaryTree_CreateEmpty(compare_ints);
    int keys[N];
    int values[N];

    /* Cles distinctes melangees : (i * 7919) % N est une permutation car pgcd(7919, 1000) = 1 */
    for (int i = 0; i < N; i++) {
        keys[i] = (i * 7919) % N;
        values[i] = i;
        BinaryTree_Put(tree, &values[i], &keys[i]);
    }

    assert((int)tree->size == N);

    for (int i = 0; i < N; i++) {
        assert(BinaryTree_Get(tree, &keys[i]) == &values[i]);
    }

    BinaryTree_Destroy(tree);
}

/* ---------- Cles negatives et zero ---------- */
static void test_cles_negatives(void) {
    BinaryTree* tree = BinaryTree_CreateEmpty(compare_ints);
    int keys[]   = {0, -1, 1, -1000, 1000, INT_MIN, INT_MAX};
    int values[] = {0, 1, 2, 3, 4, 5, 6};
    int n = 7;

    for (int i = 0; i < n; i++) {
        BinaryTree_Put(tree, &values[i], &keys[i]);
    }
    assert((int)tree->size == n);

    for (int i = 0; i < n; i++) {
        assert(BinaryTree_Get(tree, &keys[i]) == &values[i]);
    }

    BinaryTree_Destroy(tree);
}

/* ---------- Ecrasement repete de la meme cle ---------- */
static void test_ecrasement_repete(void) {
    BinaryTree* tree = BinaryTree_CreateEmpty(compare_ints);
    int key = 5;
    int values[50];

    for (int i = 0; i < 50; i++) {
        values[i] = i;
        BinaryTree_Put(tree, &values[i], &key);
        assert(tree->size == 1);
        assert(BinaryTree_Get(tree, &key) == &values[i]);
    }

    BinaryTree_Destroy(tree);
}

/* ---------- Ecrasement d'une cle au milieu de l'arbre ---------- */
static void test_ecrasement_noeud_interne(void) {
    BinaryTree* tree = BinaryTree_CreateEmpty(compare_ints);
    int keys[]   = {50, 30, 70, 20, 40, 60, 80};
    int values[] = {0, 1, 2, 3, 4, 5, 6};
    int n = 7;

    for (int i = 0; i < n; i++) {
        BinaryTree_Put(tree, &values[i], &keys[i]);
    }
    assert(tree->size == 7);

    int nouvelle_valeur = 999;
    BinaryTree_Put(tree, &nouvelle_valeur, &keys[1]);  /* cle 30 : noeud interne */
    assert(tree->size == 7);
    assert(BinaryTree_Get(tree, &keys[1]) == &nouvelle_valeur);

    /* Les autres noeuds ne sont pas touches */
    for (int i = 0; i < n; i++) {
        if (i == 1) continue;
        assert(BinaryTree_Get(tree, &keys[i]) == &values[i]);
    }

    BinaryTree_Destroy(tree);
}

/* ---------- Structure d'un arbre complet de 7 noeuds ---------- */
static void test_structure_arbre_complet(void) {
    BinaryTree* tree = BinaryTree_CreateEmpty(compare_ints);
    int keys[]   = {50, 30, 70, 20, 40, 60, 80};
    int values[] = {0, 1, 2, 3, 4, 5, 6};

    for (int i = 0; i < 7; i++) {
        BinaryTree_Put(tree, &values[i], &keys[i]);
    }

    assert(tree->root->left != NULL && tree->root->right != NULL);
    assert(tree->root->left->left != NULL && tree->root->left->right != NULL);
    assert(tree->root->right->left != NULL && tree->root->right->right != NULL);

    /* Liens parent coherents */
    assert(tree->root->left->parent == tree->root);
    assert(tree->root->right->parent == tree->root);
    assert(tree->root->left->left->parent == tree->root->left);
    assert(tree->root->left->right->parent == tree->root->left);
    assert(tree->root->right->left->parent == tree->root->right);
    assert(tree->root->right->right->parent == tree->root->right);

    /* Les feuilles n'ont pas d'enfants */
    assert(tree->root->left->left->left == NULL);
    assert(tree->root->right->right->right == NULL);

    BinaryTree_Destroy(tree);
}

/* ---------- Plusieurs arbres independants ---------- */
static void test_arbres_independants(void) {
    BinaryTree* a = BinaryTree_CreateEmpty(compare_ints);
    BinaryTree* b = BinaryTree_CreateEmpty(compare_ints);
    int key = 1;
    int va = 10, vb = 20;

    BinaryTree_Put(a, &va, &key);
    assert(a->size == 1);
    assert(b->size == 0);
    assert(BinaryTree_Get(b, &key) == NULL);

    BinaryTree_Put(b, &vb, &key);
    assert(BinaryTree_Get(a, &key) == &va);
    assert(BinaryTree_Get(b, &key) == &vb);

    BinaryTree_Destroy(a);
    BinaryTree_Destroy(b);
}

int main(const int argc, const char *argv[]) {
    test_basique();
    test_arbre_vide();
    test_un_seul_element();
    test_insertion_croissante();
    test_insertion_decroissante();
    test_insertion_aleatoire();
    test_cles_negatives();
    test_ecrasement_repete();
    test_ecrasement_noeud_interne();
    test_structure_arbre_complet();
    test_arbres_independants();

    printf("Tous les tests ont reussi avec succes !\n");

    return EXIT_SUCCESS;
}