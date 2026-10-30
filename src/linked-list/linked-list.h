//
// Created by killi on 30/10/2026.
//

#ifndef DATA_STRUCTURES_LINKED_LIST_H
#define DATA_STRUCTURES_LINKED_LIST_H

#include <stdbool.h>

/**
 * @brief Structure de donnee representant un noeud d'une liste doublement chainee
 */
struct LinkedListNode {
    void* data;                      /**< Valeur stockee dans le noeud */
    struct LinkedListNode* next;     /**< Pointeur vers le noeud suivant */
    struct LinkedListNode* previous; /**< Pointeur vers le noeud precedent */
};

/**
 * @brief Fonction qui permet de creer un nouveau noeud pour la liste chainee
 *
 * @param data Valeur a stocker dans le noeud
 * @return Nouveau noeud cree
 */
struct LinkedListNode* LinkedListNode_Create(void* data);

/**
 * @brief Structure de donnee permettant de ranger les valeurs dans une liste doublement chainee
 */
struct LinkedList {
    struct LinkedListNode* head;     /**< Premier noeud de la liste */
    struct LinkedListNode* tail;     /**< Dernier noeud de la liste */
    unsigned int size;               /**< Nombre d'elements dans la liste */
};
typedef struct LinkedList LinkedList;

/**
 * @brief Fonction qui permet de creer une nouvelle liste chainee vide
 *
 * @return Liste chainee vide
 */
LinkedList* LinkedList_CreateEmpty();

/**
 * @brief Fonction qui permet de verifier si la liste chainee est vide
 *
 * @param list Pointeur vers la liste chainee voulue
 * @return true si la liste est vide, false sinon
 */
bool LinkedList_IsEmpty(LinkedList* list);

/**
 * @brief Fonction permettant d'ajouter une valeur en tete de la liste chainee
 *
 * @param list Pointeur vers la liste chainee voulue
 * @param data Valeur a ajouter
 */
void LinkedList_PutHead(LinkedList* list, void* data);

/**
 * @brief Fonction permettant d'ajouter une valeur en queue de la liste chainee
 *
 * @param list Pointeur vers la liste chainee voulue
 * @param data Valeur a ajouter
 */
void LinkedList_PutTail(LinkedList* list, void* data);

/**
 * @brief Fonction permettant d'ajouter une valeur a une position precise dans la liste chainee
 *
 * @param list Pointeur vers la liste chainee voulue
 * @param data Valeur a ajouter
 * @param index Position ou inserer la valeur
 */
void LinkedList_PutAt(LinkedList* list, void* data, unsigned int index);

/**
 * @brief Fonction permettant de supprimer l'element en tete de la liste chainee
 *
 * @param list Pointeur vers la liste chainee voulue
 */
void LinkedList_RemoveHead(LinkedList* list);

/**
 * @brief Fonction permettant de supprimer l'element en queue de la liste chainee
 *
 * @param list Pointeur vers la liste chainee voulue
 */
void LinkedList_RemoveTail(LinkedList* list);

/**
 * @brief Fonction permettant de supprimer un element a une position precise dans la liste chainee
 *
 * @param list Pointeur vers la liste chainee voulue
 * @param index Position de l'element a supprimer
 */
void LinkedList_RemoveAt(LinkedList* list, unsigned int index);

/**
 * @brief Fonction permettant d'extraire et de retourner la valeur en tete de la liste chainee
 *
 * @param list Pointeur vers la liste chainee voulue
 * @return Pointeur vers la ressource retiree ou NULL
 */
void* LinkedList_ExtractHead(LinkedList* list);

/**
 * @brief Fonction permettant d'extraire et de retourner la valeur en queue de la liste chainee
 *
 * @param list Pointeur vers la liste chainee voulue
 * @return Pointeur vers la ressource retiree ou NULL
 */
void* LinkedList_ExtractTail(LinkedList* list);

/**
 * @brief Fonction permettant d'extraire et de retourner la valeur a une position precise dans la liste chainee
 *
 * @param list Pointeur vers la liste chainee voulue
 * @param index Position de l'element a extraire
 * @return Pointeur vers la ressource retiree ou NULL
 */
void* LinkedList_ExtractAt(LinkedList* list, unsigned int index);

/**
 * @brief Fonction qui permet de liberer la memoire de la liste chainee
 *
 * La liste ainsi que ses noeuds ne seront plus accessibles
 *
 * @param list Liste chainee a nettoyer
 */
void LinkedList_Destroy(LinkedList* list);

/**
 * @brief Fonction permettant d'afficher tout le contenu d'une liste chainee
 *
 * @param list Pointeur vers la liste chainee voulue
 */
void LinkedList_Print(LinkedList* list);

#endif //DATA_STRUCTURES_LINKED_LIST_H