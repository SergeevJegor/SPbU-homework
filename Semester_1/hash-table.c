#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Node {
    char *key;
    int value;
    struct Node *next;
};

struct LinkedList {
    struct Node *head;
    int length;
};

int hashFunction(char *key, int tableSize);
//s -- string. h(s) = (s[0] + s[1] * p + s[2] * p^2 + ... + s[i] * p^i) % tableSize; p -- prime number

struct LinkedList *createTable(int size);

void clearTable(struct LinkedList *table, int tableSize);

void addToTable(struct LinkedList *table, char *key, int keyLength, int tableSize);

void getValueByKey(struct LinkedList *table, int tableSize, char *key);

void statistic(struct LinkedList *table, int tableSize);

void fillTable(struct LinkedList *table, int tableSize, FILE *file);

int main() {
    int tableSize;
    printf("Enter size of hash table:\n");
    scanf("%i", &tableSize);
    clock_t start = clock();
    struct LinkedList *table = createTable(tableSize);
    FILE *file = fopen("/home/drundolet/homeworks-course1/book.txt", "r");
    if (!file) {
        printf("Can't open file to read");
        exit(2);
    }
    fillTable(table, tableSize, file);
    statistic(table, tableSize);
    clearTable(table, tableSize);
    fclose(file);
    clock_t end = clock();
    printf("Work time: %f", (float) (end - start) / CLOCKS_PER_SEC);
    return 0;
};

int hashFunction(char *key, int tableSize) {
    unsigned int p = 1;
    int total = 0;
    int i = 0;
    while (key[i] != '\0') {
        total += (((int) key[i]) * p);
        p = (p * 23) % 997;
        i++;
    }
    return total % tableSize;
}

struct LinkedList *createTable(int size) {
    struct LinkedList *table = malloc(size * sizeof(struct LinkedList));
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

void addToTable(struct LinkedList *table, char *key, int keyLength, int tableSize) {
    int hash = hashFunction(key, tableSize);
    struct Node *last = table[hash].head;
    if (!table[hash].head) {//no words with such hash
        table[hash].head = copyKey(key, keyLength);
        table[hash].length++;
        return;
    } else
        while (last->next && strcmp(last->key, key)) last = last->next;

    if (!strcmp(last->key, key)) last->value++;
    else {
        last->next = copyKey(key, keyLength);
        table[hash].length++;
    }
}

void getValueByKey(struct LinkedList *table, int tableSize, char *key) {
    int hash = hashFunction(key, tableSize);
    struct Node *temp = table[hash].head;
    while (temp) {
        if (!strcmp(temp->key, key)) {
            printf("%s %d\n", key, temp->value);
            return;
        }
        temp = temp->next;
    }
    printf("Key wasn't found\n");
}

void statistic(struct LinkedList *table, int tableSize) {
    int totalWords = 0;
    int totalUnicWords = 0;
    int emptyLists = 0;
    char *mostPopularWord = "";
    int mostPopularWordVal = 0;
    int minListLength = table[0].length;
    int maxListLength = 0;

    for (int i = 0; i < tableSize; i++) {
        int len = table[i].length;
        if (!len)
            emptyLists++;
        totalUnicWords += len;
        if (maxListLength < len) maxListLength = len;
        if (minListLength > len) minListLength = len;
    }
    for (int i = 0; i < tableSize; i++) {
        struct Node *temp = table[i].head;
        while (temp) {
            if (temp->value > mostPopularWordVal) {
                mostPopularWordVal = temp->value;
                mostPopularWord = temp->key;
            }
            totalWords += temp->value;
            temp = temp->next;
        }
    }
    printf("Uncial words: %i\n", totalUnicWords);
    printf("Total words: %i\n", totalWords);
    printf("Longest list length: %i\n", maxListLength);
    printf("Shortest list length: %i\n", minListLength);
    printf("Average list length: %f\n", (float) totalUnicWords / tableSize);
    printf("Most popular word: %s\n", mostPopularWord);
    printf("Most popular word frequency: %f\n", (float) mostPopularWordVal / totalWords);
    printf("Percent of empty lists: %f\n", (float) 100 * emptyLists / tableSize);
}

void fillTable(struct LinkedList *table, int tableSize, FILE *file) {
    char word[50] = "";
    while (fscanf(file, "%s", word) == 1) {
        if (!strcmp(word, "–")) continue;
        int len = (int) strlen(word);
        char finalWord[50];
        for (int i = 0; i < 50; i++) finalWord[i] = 0;
        for (int i = 0; i < len; i++) {
            if (word[i] == '.' || word[i] == ',' || word[i] == '!' || word[i] == '?' || word[i] == ':' ||
                word[i] == ';' || word[i] == '-')
                continue;
            char symbol[2];
            symbol[0] = word[i];
            symbol[1] = '\0';
            strcat(finalWord, symbol);
        }
        if (strlen(finalWord) != 0) {
            addToTable(table, finalWord, (int) strlen(finalWord), tableSize);
        }
    }
}

void clearTable(struct LinkedList *table, int tableSize) {
    for (int i = 0; i < tableSize; i++) {
        struct Node *temp = table[i].head;
        int j = 0;
        while (table[i].head) {
            table[i].head = temp->next;
            free(temp->key);
            free(temp);
            temp = table[i].head;
        }
        table[i].length = 0;
        free(table[i].head);
    }
    free(table);
}