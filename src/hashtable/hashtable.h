//
// Created by killian on 10/30/26.
//

#ifndef DATA_STRUCTURES_HASHTABLE_H
#define DATA_STRUCTURES_HASHTABLE_H

#include <string.h>
#include <stdbool.h>

#define HASHTABLE_DEFAULT_CAPACITY 16

/**
 * @brief Structure de donnee permettant de ranger les valeurs grace a des chaines de caractere
 */
struct HashtableNode {
    const char* key;                  /**< Cle pour retrouver/ranger la valeur */
    void* value;                /**< Valeur stockee */
    struct HashtableNode* next; /**< Liste chainee en cas de collision entre deux cles */
};

/**
 * @brief Structure de donnee permettant de ranger des valeurs grace a une chaine de caractere
 */
struct Hashtable {
    struct HashtableNode* table;
    unsigned int capacity;
};
typedef struct Hashtable Hashtable;

/**
 * @brief Fonction qui permet de creer une nouvelle hashtable
 *
 * Cette fonction va creer une hashtable de capacite 16 par defaut
 *
 * @return hashtable vide
 */
Hashtable* Hashtable_CreateEmpty();

/**
 * @brief Fonction qui permet de creer une nouvelle hashtable
 *
 * @param capacity Capacite par defaut de la hashtable
 *
 * @return hashtable vide
 */
Hashtable* Hashtable_CreateEmptyWithCapacity(const int capacity);

/**
 * @brief fonction qui va hacher une cle pour retourner un entier non signe
 *
 * @param key cle a hacher
 * @return cle hachee
 */
unsigned int hash(const char* key);

/**
 * @brief Fonction permettant de ranger une valeur dans la hashtable grace a une cle
 *
 * @param hashtable pointeur vers la hashtable voulue
 * @param key cle de rangement
 * @param value valeur a ranger
 */
void Hashtable_Put(Hashtable* hashtable, const char* key, void* value);

/**
 * @brief Fonction permettant d'obtenir une valeur de la hashtable selon une cle
 *
 * @param hashtable pointeur vers la hashtable voulue
 * @param key cle de la valeur
 * @return Pointeur vers la ressource ou NULL
 */
void* Hashtable_Get(Hashtable* hashtable, const char* key);

/**
 * @brief Fonction qui permet de liberer la memoire de la hashtable
 *
 * La hashtable ainsi que ses champs ne seront plus accessible
 *
 * @param hashtable hashtable a nettoyer
 */
void Hashtable_Destroy(Hashtable* hashtable);

/**
 * @brief Fonction permettant d'afficher tout le contenu d'une hashtable
 *
 * @param hashtable pointeur vers la hashtable voulue
 */
void Hashtable_Print(Hashtable* hashtable);

#endif //DATA_STRUCTURES_HASHTABLE_H
