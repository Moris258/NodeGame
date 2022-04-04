#ifndef LINKED_LIST_H
#define LINKED_LIST_h
#include "NodeActualy.h"



typedef struct NodeList_E{
    struct NodeList_E* next;
    Node* node;
}NodeList_E;

typedef struct NodeList{
    NodeList_E* first;

}NodeList;

NodeList* NodeList_Init();
void NodeList_AddItem(Node* item, NodeList* list);
void NodeList_Destroy(NodeList* list);
int NodeList_Search(NodeList* list, Node* item);

#endif