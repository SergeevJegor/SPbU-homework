#include <stdio.h>
#include <stdlib.h>
#include "lists-lib.h"

int listCreated = 0;

struct List{
    int value;
    struct List* pointer;
};

struct List* action(struct List* list, int funcN);

int main() {
    struct List* list;
    while (1){
        int n;
        printf("Menu:\n"
                       " 1. Print list\n"
                       " 2. Create list\n"
                       " 3. Add new head to list\n"
                       " 4. Add new tail to list\n"
                       " 5. Add new cell\n"
                       " 6. Delete cells\n"
                       " 7. Reverse list\n"
                       " 8. Delete list\n"
                       " 9. Exit\n"
        );
        scanf("%d", &n);
        list = action(list, n);
    }
    return 0;
}

struct List* action(struct List* list, int n){
    int val, pos;
    char c;
    switch (n){
        case 1 ://print list
            listPrint(list);
            printf("\n");
            break;
        case 2 ://create list
            printf("Enter list's head value:");
            scanf("%d", &val);
            list = listCreate(val);
            listCreated = 1;
            printf("\n");
            break;
        case 3 ://add new head
            if (!listCreated){
                printf("Create list first\n");
                break;
            }
            printf("Enter list's new head value:");
            scanf("%d", &val);
            list = listAddHead(list, val);
            printf("\n");
            break;
        case 4 ://add new tail
            if (!listCreated){
                printf("Create list first\n");
                break;
            }
            printf("Enter list's new tail value:");
            scanf("%d", &val);
            listAddTail(list, val);
            printf("\n");
            break;
        case 5 :// insert element
            if (!listCreated){
                printf("Create list first\n");
                break;
            }
            printf("Enter position of the previous element and value of new list's element:");
            scanf("%d %d", &pos, &val);
            listAddAfter(list, pos, val);
            printf("\n");
            break;
        case 6 ://delete elements equals to entered number
            if (!listCreated){
                printf("Create list first\n");
                break;
            }
            printf("Enter value of elements that should be deleted:");
            scanf("%d", &val);
            listDelCondition(list, val);
            printf("\n");
            break;
        case 7 ://reverse list
            if (!listCreated){
                printf("Create list first\n");
                break;
            }
            list = listReverse(list);
            printf("List was successfully reversed");
            printf("\n");
            break;
        case 8 ://delete list
            if (!listCreated){
                printf("There is nothing to delete. Create list first\n");
                break;
            }
            printf("List will be deleted. Continue? (y = yes, n = no)");
            scanf(&c);
            if (c == 'y'){
                listClear(list);
            }
            printf("\n");
            break;
        default :
            exit(0);
    }
    return list;
}

struct List* listCreate(int a){
    struct List* newHead;
    newHead = (struct List*) malloc(sizeof(struct List));
    if (!newHead){
        printf("Cant allocate memory");
        return NULL;
    }
    newHead->value = a;
    newHead->pointer = NULL;
    return newHead;
}

struct List* listAddHead(struct List* curList, int val){
    struct List* newHead = (struct List*) malloc(sizeof(struct List));
    if (!newHead){
        printf("Cant allocate memory");
        return NULL;
    }
    newHead->pointer = curList;
    newHead->value = val;
    return newHead;
}

void listAddTail(struct List* curList, int val){
    struct List* newTail = (struct List*) malloc(sizeof(struct List));
    if (!newTail){
        printf("Cant allocate memory");
        return;
    }
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
    if (!newCell){
        printf("Cant allocate memory");
        return 0;
    }
    for (int i = 0; i < pos - 1; i++){
        if (tmp->pointer == NULL) return -1;
        tmp = tmp->pointer;
    }
    newCell->pointer = tmp->pointer;
    newCell->value = val;
    tmp->pointer = newCell;
    return 0;
}

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
    struct List* prev = curList;
    while (curList){
        prev = curList;
        curList = curList->pointer;
        free(prev);
    }
}

void listReverseRecurtion(struct List* newList, struct List* prev){
    if (newList->pointer == NULL){
        newList->pointer = prev;
        return;
    }
    listReverseRecurtion(newList->pointer, newList);
    newList->pointer = prev;
}

struct List* listReverse(struct List* list){
    struct List* listReverseRecurtion(struct List* newList, struct List* prev){
        if (newList->pointer == NULL){
            newList->pointer = prev;
            return newList;
        }
        struct List* next = newList->pointer;
        newList->pointer = prev;
        return listReverseRecurtion(next, newList);
    }
    return listReverseRecurtion(list, NULL);
}

int listIsCycled(struct List* list){

}
