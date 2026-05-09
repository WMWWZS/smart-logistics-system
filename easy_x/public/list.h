#ifndef LIST_H
#define LIST_H

typedef struct node
{
    void* data;
    struct node* next;
} LNode;

LNode* initList();
LNode* createNode(void * data);
void insertAtTail(LNode* head, void * data);
void insertAtPosition(LNode* head, void * data, int position);
void deleteNode(LNode* head, int position);
void* findNode(LNode* head, int position);
void freeList(LNode* head);
int getListNodeCount(LNode* head);
void printList(LNode* head, void (*fun)(void* p));

#endif
