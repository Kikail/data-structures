#include <assert.h>

#include "../src/linked-list/linked-list.h"
#include <stdio.h>
#include <stdlib.h>


struct NPC {
    char name[32];
    unsigned int health;
};
typedef struct NPC NPC;

void NPC_Afficher(NPC npc) {
    printf("{%s %u}\n",npc.name, npc.health);
}

int main(const int argc, const char *argv[]) {
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

    printf("--- Liste initiale ---\n");
    LinkedList_Print(list);
    assert(list->size == 3);
    assert(list->head->data == &zelda);
    assert(list->tail->data == &ganon);


    LinkedList_PutAt(list, &chicken, 0);
    assert(list->head->data == &chicken);

    LinkedList_PutAt(list, &epona, list->size);
    assert(list->tail->data == &epona);

    LinkedList_PutAt(list, &navi, 2);

    printf("--- Apres insertions PutAt ---\n");
    LinkedList_Print(list);
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

    printf("--- Apres extractions ---\n");
    LinkedList_Print(list);

    LinkedList_RemoveAt(list, 0);
    printf("--- Apres suppression index 0 ---\n");
    LinkedList_Print(list);

    LinkedList_RemoveAt(list, list->size - 1);
    printf("--- Apres suppression dernier index ---\n");
    LinkedList_Print(list);

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

    printf("Tous les tests ont reussi avec succes !\n");

    return EXIT_SUCCESS;
}
