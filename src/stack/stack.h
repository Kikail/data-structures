//
// Created by killi on 31/10/2026.
//

#ifndef DATA_STRUCTURES_STACK_H
#define DATA_STRUCTURES_STACK_H

#include <stdbool.h>

#define STACK_DEFAULT_CAPACITY 16

/**
 * @brief Structure de donnee permettant de ranger les valeurs selon le principe LIFO (Last In, First Out)
 */
struct Stack {
    unsigned int capacity; /**< Capacite maximale de la pile */
    void** stack;          /**< Tableau de pointeurs stockant les elements */
    unsigned int top;      /**< Indice du sommet de la pile */
};
typedef struct Stack Stack;

/**
 * @brief Fonction qui permet de creer une nouvelle pile vide de taille par defaut (16)
 *
 * @return Pile vide
 */
Stack* Stack_CreateEmpty();

/**
 * @brief Fonction qui permet de creer une nouvelle pile vide avec une capacite donnee
 *
 * @param capacity Capacite initiale de la pile
 * @return Pile vide
 */
Stack* Stack_CreateEmptyWithCapacity(unsigned int capacity);

/**
 * @brief Fonction qui permet de verifier si la pile est vide
 *
 * @param stack Pointeur vers la pile voulue
 * @return true si la pile est vide, false sinon
 */
bool Stack_IsEmpty(Stack* stack);

/**
 * @brief Fonction qui permet de verifier si la pile est pleine
 *
 * @param stack Pointeur vers la pile voulue
 * @return true si la pile est pleine, false sinon
 */
bool Stack_IsFull(Stack* stack);

/**
 * @brief Fonction permettant d'ajouter un element au sommet de la pile
 *
 * @param stack Pointeur vers la pile voulue
 * @param data Valeur a ajouter
 * @return true en cas de succes, false sinon
 */
bool Stack_Push(Stack* stack, void* data);

/**
 * @brief Fonction permettant de retirer et de retourner l'element au sommet de la pile
 *
 * @param stack Pointeur vers la pile voulue
 * @return Pointeur vers la ressource retiree ou NULL
 */
void* Stack_Pop(Stack* stack);

/**
 * @brief Fonction qui permet de liberer la memoire de la pile
 *
 * La pile ainsi que ses elements ne seront plus accessibles
 *
 * @param stack Pile a nettoyer
 */
void Stack_Destroy(Stack* stack);

/**
 * @brief Fonction permettant d'afficher tout le contenu d'une pile
 *
 * @param stack Pointeur vers la pile voulue
 */
void Stack_Print(Stack* stack);

#endif //DATA_STRUCTURES_STACK_H