/*
    linklist.c
*/
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "linklist.h"

//int Head = 0xFF; // Physical index of the first node in the linked list.
//int Tail = 0xFF; // Physical index of the last node in the linked list.

struct Node_t LL[LL_NUM];
struct Node_t *Head = NULL;
struct Node_t *Tail = NULL;


void link_list_init(void){
    int i=0;
    for(i=0; i<LL_NUM; i++){
        LL[i].Deleted   = true;
        LL[i].Prev      = NULL;
        LL[i].Next      = NULL;
        LL[i].Number    = 0;
    }
    Head = NULL;
    Tail = NULL;
}

struct Node_t *empty_node(void){
    struct Node_t *node = NULL;
    int i=0; 
    for(i=0; i<LL_NUM; i++){
        if (LL[i].Deleted){
            node = &(LL[i]);
            break;
        }
    }
    return node;
}

void link_list_add(int number){
    struct Node_t *node = NULL;
    if (Head == NULL){ //-------------------------- Link list is empty.
        Head = &(LL[0]);
        Tail = &(LL[0]);
        node = Head;
        printf("The first, node = 0x%x\n", node);
    }else{
        node = empty_node();
        if (node == NULL){ //--------------------- Link list is full! Overwrite the Head.
            node = Head;
            Head = node->Next;
            Head->Prev = NULL;
            node->Prev = Tail;
            node->Next = NULL;
            Tail->Next = node;
            Tail = node;
            printf("Link list is full, node = 0x%x\n", node);
        }else{ //--------------------------------- An empty slot is found! Add new data into it.
            Tail->Next = node;
            node->Prev = Tail;
            node->Next = NULL;
            Tail = node;
            printf("Node = 0x%x\n", node);
        }
    }
    node->Number = number;
    node->Deleted = false;
}

bool link_list_get(int *pNumber, int index){
    int    i            = 0;
    bool   isOk         = false;
    struct Node_t *node = Head;
    if (Head == NULL){
        printf("No data!\n");
    }else if (index >= LL_NUM){
        printf("Invalid index!\n");
    }else{
        while(node != NULL){
            if (i++ == index){
                *pNumber = node->Number;
                isOk = true;
                break;
            }
            node = node->Next;
        }
    }
    return isOk;    
}

struct Node_t *link_list_search(int number){
    int i    = 0;
    struct Node_t *node = Head;
    struct Node_t *result = NULL;
    while(node != NULL){
        if (node->Number == number){
            result = node;
            break;
        }
        node = node->Next;
    }
    return result;
}

void link_list_remove_node(struct Node_t *pNode){
    struct Node_t *prev = pNode->Prev;
    struct Node_t *next = pNode->Next;
    if (Head == NULL){
        printf("No Data!\n");
    }else if (pNode == NULL || pNode->Deleted || (pNode->Prev == NULL && pNode->Next == NULL)){
        printf("Invalid node!\n");
    }else{
        pNode->Deleted = true;
        pNode->Prev = NULL;
        pNode->Next = NULL;
        if (prev == NULL){ Head = next; }else{ prev->Next = next; }
        if (next == NULL){ Tail = prev; }else{ next->Prev = prev; }
    }
}

void link_list_remove_number(int number){
    struct Node_t *node = NULL;
    while(1){
        node = link_list_search(number);
        printf("Node: 0x%x\n", node);
        if (node == NULL){
            printf("Done!\n");
            break;
        }else{
            link_list_remove_node(node);
        }
    }
}

void link_list_clear(void){
    link_list_init();
}

void link_list_dump(void){
    struct Node_t *node = Head;
    if (Head == NULL){
        printf("No Data!\n");
    }else{
        while(node != NULL){
            printf("0x%08X: [Prev: 0x%08X] %08d [Next: 0x%08X]\n", node, node->Prev, node->Number, node->Next);
            node = node->Next;
        }
    }
}

void link_list_dump_raw(void){
    int i=0; 
    for(i=0; i<LL_NUM; i++){
        printf("0x%08X: [Prev: 0x%08X] %08d [Next: 0x%08X]\n",\
                &(LL[i]), LL[i].Prev, LL[i].Number, LL[i].Next);
    }
}


