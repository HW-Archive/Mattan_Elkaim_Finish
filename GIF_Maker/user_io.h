#ifndef USER_IO
#define USER_IO

#include <stdbool.h>
#include "linkedList.h"
#define STR_LEN 200

// Added RENAME, PLAY_REVERSED
enum COMMANDS
{
	EXIT, ADD, REMOVE, CHANGE_INDEX, RENAME, CHANGE_DURATION,
	CHANGE_DURATION_ALL, LIST, PLAY, PLAY_REVERSED, SAVE
};

void printMenu();
int getUserInput(const int MIN, const int MAX);
void clearBuffer();
void myFgets(char* str);
void getFrameProperties(char* path, char* name, unsigned int* duration, FrameNode* head);
bool isFileExists(char* path);

#endif
