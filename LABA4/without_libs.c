#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "my_strings.h"
#define DELIMETERS "\t "
#define ERROR_CHAR ' '
#define PROMPT "\x1b[31m❱\x1b[0m\x1b[32m❱\x1b[0m\x1b[34m❱\x1b[0m "


char* process(const char* line);
char getFirstLetterOfTheLastWord(const char* line);
char* moveWords(const char* line, char letter);


int main(){
	printf("This program DOESN'T USE any libs!\n");
	char* line = myReadline(PROMPT);
	while (line != NULL) {
		clock_t start, end;
		double cpu_time_used;
		start = clock();
		char* processed = process(line);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("Input:   \x1b[32m\"%s\"\x1b[0m\n", line);
                printf("Output:  \x1b[32m\"%s\"\x1b[0m\n", processed);
		printf("\x1b[33mtook %f seconds\x1b[0m\n", cpu_time_used);
		free(line);
		if (myStrlen(processed)) free(processed);
		line = myReadline(PROMPT);
	}
	return 0;
}


char* process(const char* line) {
	char* lCopy = myStrdup(line);
	char letter = getFirstLetterOfTheLastWord(lCopy);
	char* result = "";
	if (letter != ERROR_CHAR)
		result = moveWords(lCopy, letter);
	free(lCopy);
	return result;
}


char getFirstLetterOfTheLastWord(const char* line) {
	char* lCopy = myStrdup(line);

	char curLetter = ERROR_CHAR;
	char* subStr = myStrtok(lCopy, DELIMETERS);
	while (subStr != NULL) {
		curLetter = subStr[0];
		subStr = myStrtok(NULL, DELIMETERS);
	}

	free(lCopy);
	return curLetter;
}


char* moveWords(const char* line, char letter) {
	char* lCopy = myStrdup(line);
	char* head = calloc(myStrlen(line) + 2, sizeof(char));
	char* tail = calloc(myStrlen(line) + 2, sizeof(char));
	size_t headLen = 0;
	size_t tailLen = 0;

	char* subStr = myStrtok(lCopy, DELIMETERS);
        while (subStr != NULL) {
                char lastLetter = subStr[myStrlen(subStr) - 1];
		if (lastLetter == letter) {
			myMemcpy(head + headLen, subStr, (myStrlen(subStr) + 1) * sizeof(char));
			headLen += myStrlen(subStr) + 1;
			head[headLen - 1] = ' ';
		} else {
			myMemcpy(tail + tailLen, subStr, (myStrlen(subStr) + 1) * sizeof(char));
                	tailLen += myStrlen(subStr) + 1;
			tail[tailLen - 1] = ' ';
		}

		subStr = myStrtok(NULL, DELIMETERS);
        }

	myMemcpy(head + headLen, tail, (myStrlen(tail) + 1) * sizeof(char));
	headLen += myStrlen(tail);
	head[headLen - 1] = '\0';

	head = realloc(head, (myStrlen(head) + 1) * sizeof(char));

	free(lCopy);
	free(tail);
	return head;
}
