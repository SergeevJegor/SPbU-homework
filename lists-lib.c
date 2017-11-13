#include <stdio.h>
#include <stdlib.h>
#include "lists-lib.h"

int listCreated = 0;

struct List{
    int value;
    struct List* pointer;
};

/*struct List* listCreate(int a);
struct List* listAddHead(struct List* curList, int val);
void listAddTail(struct List* curList, int val);
int listAddAfter(struct List* curList, int pos, int val);// 0 -- successful insertion; -1 -- error (pos > list length)
//int listDel(struct List* curList, int pos);// 0 -- successful deletion; -1 -- error (pos > list length)
void listDelCondition(struct List* curList, int val);
void listPrint(struct List* curList);
void listClear(struct List* curList);*/
struct List* action(struct List* list, int funcN);

int main() {

    struct List* list;
    /*listAddTail(list, 4);
    list = listAddHead(list, 1);
    listAddAfter(list, 2, 3);
    listDelCondition(list, 4);
    listClear(list);
    listPrint(list);*/
    while (1){
        int n;
        printf("Menu:\n"
                       " 1. Print list\n"
                       " 2. Create list\n"
                       " 3. Add new head to list\n"
                       " 4. Add new tail to list\n"
                       " 5. Add new cell\n"
                       " 6. Delete cells\n"
                       " 7. Delete list\n"
                       " 8. Exit\n"
        );
        scanf("%d", &n);
        list = action(list, n);
    }
    list = listCreate(2);
    listPrint(list);

    system("pause");
    return 0;
}

struct List* action(struct List* list, int n){
    int val, pos;
    char c;
    switch (n){
        case 1 :
            listPrint(list);
            printf("\n");
            break;
        case 2 :
            printf("Enter list's head value:");
            scanf("%d", &val);
            list = listCreate(val);
            listCreated = 1;
            break;
        case 3 :
            if (!listCreated){
                printf("Create list first\n");
                break;
            }
            printf("Enter list's new head value:");
            scanf("%d", &val);
            list = listAddHead(list, val);
            break;
        case 4 :
            if (!listCreated){
                printf("Create list first\n");
                break;
            }
            printf("Enter list's new tail value:");
            scanf("%d", &val);
            listAddTail(list, val);
            break;
        case 5 :
            if (!listCreated){
                printf("Create list first\n");
                break;
            }
            printf("Enter position of the previous cell and value of new list's cell:");
            scanf("%d %d", &pos, &val);
            listAddAfter(list, pos, val);
            break;
        case 6 :
            if (!listCreated){
                printf("Create list first\n");
                break;
            }
            printf("Enter value of cells that should be deleted:");
            scanf("%d", &val);
            listDelCondition(list, val);
            break;
        case 7 :
            if (!listCreated){
                printf("There is nothing to delete. Create list first\n");
                break;
            }
            printf("List will be deleted. Continue? (y = yes, n = no)");
            scanf(&c);
            if (c == 'y'){
                listClear(list);
            }
            break;
        default :
            exit(0);
    }
    return list;
}

struct List* listCreate(int a){
    struct List* newHead;
    newHead = (struct List*) malloc(sizeof(struct List));
    newHead->value = a;
    newHead->pointer = NULL;
    return newHead;
}

struct List* listAddHead(struct List* curList, int val){
    struct List* newHead = (struct List*) malloc(sizeof(struct List));
    newHead->pointer = curList;
    newHead->value = val;
    return newHead;
}

void listAddTail(struct List* curList, int val){
    struct List* newTail = (struct List*) malloc(sizeof(struct List));
    struct List* tmp;
    newTail->value = val;
    newTail->pointer = NULL;
    tmp = curList;
    while (tmp->pointer != NULL){
        tmp = tmp->pointer;
    }
    tmp->pointer = newTail;
}

int listAddAfter(struct List* curList, int pos, int val){
    struct List* tmp = curList;
    struct List* newCell = (struct List*) malloc(sizeof(struct List));
    for (int i = 0; i < pos - 1; i++){
        if (tmp->pointer == NULL) return -1;
        tmp = tmp->pointer;
    }
    newCell->pointer = tmp->pointer;
    newCell->value = val;
    tmp->pointer = newCell;
    return 0;
}

/*int listDel(struct List* curList, int pos){
    struct List* tmp = curList;
    for (int i = 0; i < pos - 1; i++){
        if (tmp->pointer == NULL) return -1;
        tmp = tmp->pointer;
    }
    tmp->pointer = tmp->pointer->pointer;
    return 0;
}*/

void listDelCondition(struct List* curList, int val){
    struct List* tmp = curList;
    struct List* p;
    if ((tmp->pointer == NULL)&&(tmp->value == val)){
        listClear(curList);
        return;
    }
    if (tmp->value == val){
        tmp->value = tmp->pointer->value;
        p = tmp->pointer->pointer;
        free(tmp->pointer);
        tmp->pointer = p;
    }
    while (tmp->pointer != NULL){
        if (tmp->pointer->value == val){
            tmp->pointer = tmp->pointer->pointer;
        } else tmp = tmp->pointer;
    }
}

void listPrint(struct List* curList){
    struct List* tmp = curList;
    while (tmp != NULL){
        printf("%i ", tmp->value);
        tmp = tmp->pointer;
    }
}

void listClear(struct List* curList){
    if (curList->pointer != NULL){
        listClear(curList->pointer);
    }
    free(curList);
}