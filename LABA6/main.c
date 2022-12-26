#include "libs/stringlib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


bool isDelimiter(char c);
bool isLetter(char c);
bool isCapital(char c);
char toCapital(char c);
char toLower(char c);
void switchCase(String *s);
void manageSpacing(String *s);


int main() {
    String* s = initString();
    int status;
    status = scanString(s);
    while (status != EOF) {
        printf("Input:  ");
        print(s);
        switchCase(s);
        manageSpacing(s);
        printf("Output: ");
        print(s);

        freeString(&s);
        s = initString();
        status = scanString(s);
    }
    return 0;
}


void switchCase(String *s) {
    node* curNode = s->head;
    while(curNode != NULL) {
        if (isLetter(curNode->symbol)) {
            if (isCapital(curNode->symbol))
                curNode->symbol = toLower(curNode->symbol);
            else
                curNode->symbol = toCapital(curNode->symbol);
        }
        curNode = curNode->next;
    }
}


void manageSpacing(String *s) {
    while (isDelimiter(s->head->symbol)) {
        node* newHead = s->head->next;
        free(s->head);
        s->head = newHead;
    }

    node* curNode = s->head;
    while(curNode->next != NULL) {
        if (!isDelimiter(curNode->symbol)) {
            curNode = curNode->next;
            continue;
        }

        if (isDelimiter(curNode->next->symbol)) {
            node* nextNode = curNode->next->next;
            free(curNode->next);
            curNode->next = nextNode;
        } else {
            curNode = curNode->next;
        }
    }

    curNode = s->head;
    while(curNode->next != NULL) {
        if (isDelimiter(curNode->next->symbol) && curNode->next->next == NULL) {
            free(curNode->next);
            curNode->next = NULL;
        } else {
            curNode = curNode->next;
        }
    }
}


bool isDelimiter(char c) {
    return c == ' ' || c == '\t';
}


bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}


bool isCapital(char c) {
    return c >= 'A' && c <= 'Z';
}


char toCapital(char c) {
    int offset = c - 'a';
    return 'A' + offset;
}


char toLower(char c) {
    int offset = c - 'A';
    return 'a' + offset;
}
