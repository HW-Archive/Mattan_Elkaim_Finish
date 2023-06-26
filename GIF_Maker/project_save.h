#ifndef PROJECT_SAVE
#define PROJECT_SAVE

#include "linkedList.h"
#define FIELDS_DELIMITER "|"
#define FRAMES_DELIMITER "\n"
#define DEFAULT_SAVE_FILE "backup.txt"

void saveProject(FrameNode* head, char* saveFilePath);
FrameNode* loadProject(char* saveFilePath);
bool getNextField(FILE* file, char* field);

#endif
