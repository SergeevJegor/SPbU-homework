#include <stdio.h>
#include <stdlib.h>

struct List{
    int value;
    struct List* pointer;
};

struct List* listCreate(int a);
struct List* listAddHead(struct List* curList, int val);
void listAddTail(struct List* curList, int val);
int listAddAfter(struct List* curList, int pos, int val);// 0 -- successful insertion; -1 -- error (pos > list length)
//int listDel(struct List* curList, int pos);// 0 -- successful deletion; -1 -- error (pos > list length)
void listDelCondition(struct List* curList, int val);
void listPrint(struct List* curList);
void listClear(struct List* curList);

int main() {

    system("pause");
    return 0;
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
    if ((tmp->pointer == NULL)&&(tmp->value == val)){
        tmp = NULL;
        return;
    }
    while (tmp->pointer != NULL){
        if (tmp->pointer->value == val){
            tmp->pointer = tmp->pointer->pointer;
        }
        tmp = tmp->pointer;
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