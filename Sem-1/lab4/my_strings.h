#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED


size_t myStrlen(const char* str);
void myMemcpy(char* dest, const char* src, size_t len);
char* myReadline(const char* prompt);
char* myStrdup(const char* str);
char* myStrtok(char* inputStr, char* dels);

#endif
