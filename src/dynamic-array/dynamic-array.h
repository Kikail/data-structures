//
// Created by killi on 30/10/2026.
//

#ifndef DATA_STRUCTURES_DYNAMIC_ARRAY_H
#define DATA_STRUCTURES_DYNAMIC_ARRAY_H

#define DYNAMIC_ARRAY_DEFAULT_CAPACITY 16

/**
 * @brief Structure de donnee permettant de ranger les valeurs dans un tableau a taille variable
 */
struct DynamicArray {
    unsigned int capacity;
    unsigned int size;
    void **array;
};
typedef struct DynamicArray DynamicArray;

/**
 * @brief Fonction qui creer un tableau dynamique de taille par defaut 16
 *
 * @return tableau dynamique
 */
DynamicArray* DynamicArray_CreateEmpty();

/**
 * @brief Fonction qui creer un tablau dynamique avec un taille choisie
 *
 * @param capacity capacite initiale
 * @return tableau dynamique
 */
DynamicArray* DynamicArray_CreateEmptyWithCapacity(unsigned int capacity);

/**
 * @brief Fonction qui double la capacite du tableau
 *
 * @param array tableau dynamique
 */
void DynamicArray_DoubleCapacity(DynamicArray* array);

/**
 * @brief Fonction qui augmente la capacite du tableau
 *
 * @param capacity capacite voulue
 * @param array tableau dynamique
 */
void DynamicArray_SetCapacity(DynamicArray* array, unsigned int capacity);

/**
 * @brief Fonction qui ajoute la valeur dans la premiere case vide
 *
 * @param array tableau dynamique
 * @param value valeur a ajouter
 */
void DynamicArray_Put(DynamicArray* array, void* value);

/**
 * @brief Fonction qui ajoute la valeur dans la premiere case vide
 *
 * @param array tableau dynamique
 * @param index position dans le tableau
 * @param value valeur a ajouter
 */
void DynamicArray_PutAt(DynamicArray* array, unsigned int index, void* value);

/**
 * @brief Fonction qui enleve la valeur dans la premiere case vide
 *
 * @param array tableau dynamique
 * @param index position dans le tableau
 */
void DynamicArray_RemoveAt(DynamicArray* array, unsigned int index);

/**
 * @brief Fonction renvoit un element a une position dans le tableau
 *
 * @param array tableau dynamique
 * @param index position dans le tableau
 * @return valeur trouvee ou NULL
 */
void* DynamicArray_Get(DynamicArray* array, unsigned int index);

/**
 * @brief Fonction libere la memoire du tableau
 *
 * @param array tableau dynamique
 */
void DynamicArray_Destroy(DynamicArray *array);

/**
 * @brief Fonction qui affiche tout le contenu du tableau
 *
 * @param array tableau dynamique
 */
void DynamicArray_Print(DynamicArray *array);


#endif //DATA_STRUCTURES_DYNAMIC_ARRAY_H
