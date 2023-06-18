#ifndef USER_IO
#define USER_IO
#define STR_LEN 100

enum COMMANDS {
	EXIT, ADD, REMOVE, CHANGE_INDEX, CHANGE_DURATION,
	CHANGE_DURATION_ALL, LIST, PLAY, SAVE
};

void printMenu();
int getUserInput(const unsigned int MIN, const unsigned int MAX);
void clearBuffer();
void myFgets(char* str);
bool isFileExists(char* path);

#endif
