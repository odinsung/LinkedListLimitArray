/*
    linklist.h
*/
#ifndef _LINKLIST_H
#define _LINKLIST_H

struct Node_t{
    struct Node_t *Prev;
    struct Node_t *Next;
    bool   Deleted;
    int    Number;
};

#define LL_NUM   10

void            link_list_init          (void);
struct Node_t * empty_node              (void);
void            link_list_add           (int number);
bool            link_list_get           (int *pNumber, int index);
struct Node_t * link_list_search        (int number);
void            link_list_remove_node   (struct Node_t *pNode);
void            link_list_remove_number (int number);
void            link_list_clear         (void);
void            link_list_dump          (void);
void            link_list_dump_raw      (void);



#endif    
