struct List {
    int value;
    struct List *pointer;
};
struct List* listCreate(int a);
struct List* listAddHead(struct List* curList, int val);
void listAddTail(struct List* curList, int val);
int listAddAfter(struct List* curList, int pos, int val);
void listDelCondition(struct List* curList, int val);
void listPrint(struct List* curList);
void listClear(struct List* curList);
struct List* listReverse(struct List* list);
int listIsCycled(struct List* list);
struct List* listCreateCycle(struct List* list, int n);