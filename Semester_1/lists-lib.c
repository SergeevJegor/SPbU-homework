#include <stdio.h>
#include <stdlib.h>
#include "lists-lib.h"

#define PRINT_LIST 1:;
#define CREATE_LIST 2:;
#define ADD_HEAD 3:;
#define ADD_TAIL 4:;
#define ADD_CELL 5:;
#define DELETE_CELLS 6:;
#define REVERSE_LIST 7:;
#define CYCLE_CHECK 8:;
#define CREATE_CYCLE 9:;
#define DELETE_LIST 10:;


int listCreated = 0;

struct List *action(struct List *list, int n);

int main() {
    struct List *list;
    while (1) {
        int n;
        printf("Menu:\n"
                       " 1. Print list\n"
                       " 2. Create list\n"
                       " 3. Add new head to list\n"
                       " 4. Add new tail to list\n"
                       " 5. Add new cell\n"
                       " 6. Delete cells\n"
                       " 7. Reverse list\n"
                       " 8. Check if list is cycled\n"
                       " 9. Create cycle in list\n"
                       " 10. Delete list\n"
                       " 11. Exit\n"
        );
        scanf("%d", &n);
        list = action(list, n);
    }
}

struct List *action(struct List *list, int n) {
    int val, pos;
    char c;
    switch (n) {
        case PRINT_LIST
            listPrint(list);
            printf("\n");
            break;
        case CREATE_LIST
            printf("Enter list's head value:");
            scanf("%d", &val);
            list = listCreate(val);
            listCreated = 1;
            printf("\n");
            break;
        case ADD_HEAD
            if (!listCreated) {
                printf("Create list first\n");
                break;
            }
            printf("Enter list's new head value:");
            scanf("%d", &val);
            list = listAddHead(list, val);
            printf("\n");
            break;
        case ADD_TAIL
            if (!listCreated) {
                printf("Create list first\n");
                break;
            }
            printf("Enter list's new tail value:");
            scanf("%d", &val);
            listAddTail(list, val);
            printf("\n");
            break;
        case ADD_CELL
            if (!listCreated) {
                printf("Create list first\n");
                break;
            }
            printf("Enter position of the previous element and value of new list's element:");
            scanf("%d %d", &pos, &val);
            listAddAfter(list, pos, val);
            printf("\n");
            break;
        case DELETE_CELLS
            if (!listCreated) {
                printf("Create list first\n");
                break;
            }
            printf("Enter value of elements that should be deleted:");
            scanf("%d", &val);
            listDelCondition(list, val);
            printf("\n");
            break;
        case REVERSE_LIST
            if (!listCreated) {
                printf("Create list first\n");
                break;
            }
            list = listReverse(list);
            printf("List was successfully reversed\n");
            break;
        case CYCLE_CHECK
            if (!listCreated) {
                printf("There is nothing to delete. Create list first\n");
                break;
            }
            if (listIsCycled(list)) {
                printf("There is cycle in list\n");
            } else {
                printf("There is no cycle in list\n");
            }
            break;
        case CREATE_CYCLE
            if (!listCreated) {
                printf("There is nothing to delete. Create list first\n");
                break;
            }
            printf("Enter number of element to make cycle:");
            scanf("%d", &pos);
            printf("\n");
            listCreateCycle(list, pos - 1);
            break;
        case DELETE_LIST
            if (!listCreated) {
                printf("There is nothing to delete. Create list first\n");
                break;
            }
            printf("List will be deleted. Continue? (y = yes, n = no)\n");
            scanf(&c);
            if (c == 'y') {
                listClear(list);
            }
            printf("\n");
            break;

        default :
            exit(0);
    }
    return list;
}

struct List *listCreate(int a) {
    struct List *newHead;
    newHead = (struct List *) malloc(sizeof(struct List));
    if (!newHead) {
        printf("Can't allocate memory");
        return NULL;
    }
    newHead->value = a;
    newHead->pointer = NULL;
    return newHead;
}

struct List *listAddHead(struct List *curList, int val) {
    struct List *newHead = (struct List *) malloc(sizeof(struct List));
    if (!newHead) {
        printf("Can't allocate memory");
        return NULL;
    }
    newHead->pointer = curList;
    newHead->value = val;
    return newHead;
}

void listAddTail(struct List *curList, int val) {
    struct List *newTail = (struct List *) malloc(sizeof(struct List));
    if (!newTail) {
        printf("Can't allocate memory");
        return;
    }
    struct List *tmp;
    newTail->value = val;
    newTail->pointer = NULL;
    tmp = curList;
    while (tmp->pointer != NULL) {
        tmp = tmp->pointer;
    }
    tmp->pointer = newTail;
}

int listAddAfter(struct List *curList, int pos, int val) {
    struct List *tmp = curList;
    struct List *newCell = (struct List *) malloc(sizeof(struct List));
    if (!newCell) {
        printf("Can't allocate memory");
        return 0;
    }
    for (int i = 0; i < pos - 1; i++) {
        if (tmp->pointer == NULL) return -1;
        tmp = tmp->pointer;
    }
    newCell->pointer = tmp->pointer;
    newCell->value = val;
    tmp->pointer = newCell;
    return 0;
}

void listDelCondition(struct List *curList, int val) {
    struct List *tmp = curList;
    struct List *p;
    if ((tmp->pointer == NULL) && (tmp->value == val)) {
        listClear(curList);
        return;
    }
    if (tmp->value == val) {
        tmp->value = tmp->pointer->value;
        p = tmp->pointer->pointer;
        free(tmp->pointer);
        tmp->pointer = p;
    }
    while (tmp->pointer != NULL) {
        if (tmp->pointer->value == val) {
            tmp->pointer = tmp->pointer->pointer;
        } else tmp = tmp->pointer;
    }
}

void listPrint(struct List *curList) {
    struct List *tmp = curList;
    while (tmp != NULL) {
        printf("%i ", tmp->value);
        tmp = tmp->pointer;
    }
}

void listClear(struct List *curList) {
    struct List *prev = curList;
    while (curList) {
        prev = curList;
        curList = curList->pointer;
        free(prev);
    }
}

struct List *listReverse(struct List *list) {
    struct List *next, *prev;
    struct List *newList = list;
    next = newList->pointer;
    prev = NULL;
    while (next->pointer){
        newList->pointer = prev;
        prev = newList;
        newList = next;
        next = next->pointer;
    }
    newList->pointer = prev;
    next->pointer = newList;
    return next;
}

int listIsCycled(struct List *list) {
    struct List *oneStep = list;
    struct List *twoSteps = list;
    int i = 0;
    while (oneStep && twoSteps && twoSteps->pointer) {
        oneStep = oneStep->pointer;
        i++;
        twoSteps = twoSteps->pointer->pointer;

        if (oneStep == twoSteps) {
            return i;//cycle detected
        }
    }

    return 0;//no cycle in list
}

struct List *listCreateCycle(struct List *list, int n) {
    struct List *newList = list;
    for (int i = 0; i < n; i++) {
        if (!newList) {
            printf("Entered number is bigger than list's length");
            return list;
        }
        newList = newList->pointer;
    }
    struct List *tailElem = list;
    while (tailElem->pointer) tailElem = tailElem->pointer;
    tailElem->pointer = newList;
    if (!listIsCycled(list)) {
        printf("Something went wrong");
    }
    return list;
}
