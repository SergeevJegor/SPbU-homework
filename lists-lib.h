struct List;

struct List* listCreate(int a);
struct List* listAddHead(struct List* curList, int val);
void listAddTail(struct List* curList, int val);
int listAddAfter(struct List* curList, int pos, int val);
void listDelCondition(struct List* curList, int val);
void listPrint(struct List* curList);
void listClear(struct List* curList);