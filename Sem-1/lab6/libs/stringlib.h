#ifndef LIST_H
#define LIST_H

typedef struct Node {
  char symbol;
  struct Node *next;
} node;
typedef struct String {
  node *head;
} String;
String *initString();
void append(String *s, char val);
void print(String *s);
void freeString(String **s);
int scanString(String *s);

#endif
