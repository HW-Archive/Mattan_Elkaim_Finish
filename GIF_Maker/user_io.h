#ifndef USER_IO
#define USER_IO

#include <stdbool.h>
#include "linkedList.h"
#define STR_LEN 100


enum COMMANDS {
	EXIT, ADD, REMOVE, CHANGE_INDEX, CHANGE_DURATION,
	CHANGE_DURATION_ALL, LIST, PLAY, SAVE
};

void printMenu();
int getUserInput(const unsigned int MIN, const unsigned int MAX);
void clearBuffer();
void myFgets(char* str);
void getFrameProperties(char** path, char** name, unsigned int *duration, FrameNode* head);
bool isFileExists(char* path);

#endif
