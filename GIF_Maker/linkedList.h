#ifndef LINKEDLISTH
#define LINKEDLISTH

#include <stdbool.h>
#define STR_LEN 200 // Also defined in user_io.h

// Frame struct
typedef struct Frame
{
	char name[STR_LEN];
	unsigned int duration; // In milliseconds
	char path[STR_LEN];
} Frame;


// Link (node) struct
typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;

Frame* initFrame(char* name, unsigned int duration, char* path);
FrameNode* initNode(char* name, unsigned int duration, char* path);
FrameNode* findFrameByName(FrameNode* head, char* name);
void addFrame(FrameNode** head);
void removeFrame(FrameNode** head, char* name, bool isDelete);
void renameFrame(FrameNode* head, char* name);
void changeFrameDuration(FrameNode* head, char* name);
void changeAllDuration(FrameNode* head);
void changeFramePosition(FrameNode** head, char* name);
void listFrames(FrameNode* head);
void reverseList(FrameNode** head);
void freeList(FrameNode* head);
void deleteVideo(FrameNode** head);


#endif
