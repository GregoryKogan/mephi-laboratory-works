#include <stdio.h>
#include <stdlib.h>


size_t myStrlen(const char* str) {
	if (str[0] == '\0')
		return 0;

	size_t length = 0;
	while (str[length] != '\0')
		length++;
	return length;
}


void myMemcpy(char* dest, const char* src, size_t len) {
	for (size_t i = 0; i < len; ++i)
		dest[i] = src[i];
}


char* myReadline(const char* prompt) {
	printf("%s", prompt);

	char buffer[81] = "";
	char* line = NULL;
	size_t length = 0;
	int status;

	do {
		status = scanf("%80[^\n]", buffer);
		if (status < 0 || buffer[0] == '\0') return NULL;
		if (status == 0) {
			scanf("%*c");
			continue;
		}

		size_t buffLen = myStrlen(buffer);
		size_t newLen = length + buffLen;
		line = realloc(line, (newLen + 1) * sizeof(char));
		myMemcpy(line + length, buffer, buffLen);
		length = newLen;
	} while (status > 0);

	if (length)
		line[length] = '\0';
	else
		line = calloc(1, sizeof(char));

	return line;
}


char* myStrdup(const char* str) {
	char* duplicate = calloc(myStrlen(str) + 1, sizeof(char));
	myMemcpy(duplicate, str, myStrlen(str) + 1);
	return duplicate;
}


int has(const char* str, char s) {
	size_t ind = 0;
	while (str[ind] != '\0') {
		if (str[ind] == s)
			return 1;
		ind++;
	}
	return 0;
}


char* myStrtok(char* inputStr, char* dels) {
	static char* str;
	if (inputStr != NULL)
		str = inputStr;

	if (str == NULL) return NULL;

	char* start = str;
	char* end;
	while (has(dels, start[0])) start++;
	end = start;
	while (!has(dels, end[0]) && end[0] != '\0') end++;
	if (end[0] == '\0')
		str = NULL;
	else {
       		end[0] = '\0';
		str = end + 1;
	}
	if (start == end) return NULL;
	return start;
}
