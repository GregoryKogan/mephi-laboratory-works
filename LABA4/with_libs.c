#include <stdio.h>
#include <strings.h>
#include <readline/readline.h>
#include <stdlib.h>
#define DELIMETERS "\t "
#define ERROR_CHAR ' '
#define PROMPT "\x1b[31m❱\x1b[0m\x1b[32m❱\x1b[0m\x1b[34m❱\x1b[0m "


char* process(const char* line);
char getFirstLetterOfTheLastWord(const char* line);
char* moveWords(const char* line, char letter);


int main(){
	printf("This program USES string.h, readline.h libs!\n");
	char* line = readline(PROMPT);
	while (line != NULL) {
		char* processed = process(line);
		printf("Input:   \x1b[32m\"%s\"\x1b[0m\n", line);
                printf("Output:  \x1b[32m\"%s\"\x1b[0m\n", processed);
		free(line);
		if (strlen(processed)) free(processed);
		line = readline(PROMPT);
	}
	return 0;
}


char* process(const char* line) {
	char* lCopy = strdup(line);
	char letter = getFirstLetterOfTheLastWord(lCopy);
	char* result = "";
	if (letter != ERROR_CHAR)
		result = moveWords(lCopy, letter);
	free(lCopy);
	return result;
}


char getFirstLetterOfTheLastWord(const char* line) {
	char* lCopy = strdup(line);

	char curLetter = ERROR_CHAR;
	char* subStr = strtok(lCopy, DELIMETERS);
	while (subStr != NULL) {
		curLetter = subStr[0];
		subStr = strtok(NULL, DELIMETERS);
	}

	free(lCopy);
	return curLetter;
}


char* moveWords(const char* line, char letter) {
	char* lCopy = strdup(line);
	char* head = calloc(strlen(line) + 2, sizeof(char));
	char* tail = calloc(strlen(line) + 2, sizeof(char));
	size_t headLen = 0;
	size_t tailLen = 0;

	char* subStr = strtok(lCopy, DELIMETERS);
        while (subStr != NULL) {
                char lastLetter = subStr[strlen(subStr) - 1];
		if (lastLetter == letter) {
			memcpy(head + headLen, subStr, (strlen(subStr) + 1) * sizeof(char));
			headLen += strlen(subStr) + 1;
			head[headLen - 1] = ' ';
		} else {
			memcpy(tail + tailLen, subStr, (strlen(subStr) + 1) * sizeof(char));
                	tailLen += strlen(subStr) + 1;
			tail[tailLen - 1] = ' ';
		}

		subStr = strtok(NULL, DELIMETERS);
        }

	memcpy(head + headLen, tail, (strlen(tail) + 1) * sizeof(char));
	headLen += strlen(tail);
	head[headLen - 1] = '\0';

	head = realloc(head, (strlen(head) + 1) * sizeof(char));

	free(lCopy);
	free(tail);
	return head;
}
