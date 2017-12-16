#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char *key;
    int value;
    struct Node *next;
};

struct linkedList {
    struct Node *head;
    int length;
};

int hashFunction(char *key, int tableSize);
//s -- string. h(s) = (s[0] + s[1] * p + s[2] * p^2 + ... + s[i] * p^i) % tableSize; p -- prime number

struct linkedList *createTable(int size);

void clearTable(struct linkedList *table, int tableSize);

void addToTable(struct linkedList *table, char *key, int keyLength, int tableSize);

void parseText(struct linkedList *table, FILE *file);

int main {
    int tableSize;
    printf("Enter size of hash table:\n");
    scanf("%i", &tableSize);
    FILE *file = fopen("book.txt", "r");
    if (!file) {
        printf("Can't open file to read");
        exit(2);
    }

    return 0;
};

int hashFunction(char *key, int tableSize) {
    int p = 1;
    int total = 0;
    int i = 0;
    while (key[i] != "\0") {
        total += key[i] * p;
        p *= 73;
        i++;
    }
    return total % tableSize;
}

struct linkedList *createTable(int size) {
    struct linkedList *table = malloc(size * sizeof(struct linkedList));
    if (!table) {
        printf("Can't allocate memory. Abort");
        exit(1);
    }
    return table;
}

struct Node *copyKey(char *key, int keyLength) {
    struct Node *node = malloc(sizeof(struct Node));
    if (!node) {
        printf("Can't allocate memory. Abort\n");
        exit(1);
    }
    node->value = 1;
    char *temp = malloc(keyLength + 1);
    if (!temp) {
        printf("Can't allocate memory. Abort\n");
        exit(1);
    }
    temp[sizeof(key)] = "\0";
    strcpy(temp, key);
    node->key = temp;
    return node;
}

void addToTable(struct linkedList *table, char *key, int keyLength, int tableSize) {
    int hash = hashFunction(key, tableSize);
    struct Node *last = table[hash].head;
    if (!table[hash].head) {//no words with such hash
        table[hash].head = copyKey(key, keyLength);
        table[hash].length++;
        return;
    } else while (last->next && last->key != key) last = last->next;

    if (last->key == key) last->value++;
    else {
        last->next = copyKey(key, keyLength);
        table[hash].length++;
    }
}

void clearTable(struct linkedList *table, int tableSize) {
    for (int i = 0; i < tableSize; i++) {
        struct Node *temp;
        int j = 0;
        while (table->head != NULL) {
            temp = table->head;
            table->head = table->head->next;
            free(temp);
        }
        free(table + i);
    }
}