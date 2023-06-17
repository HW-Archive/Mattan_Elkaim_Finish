#ifndef LINKEDLISTH
#define LINKEDLISTH
#include "user_io.h"

// Frame struct
typedef struct Frame
{
	char name[STR_LEN];
	unsigned int duration; // Milliseconds
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
void addFrame(FrameNode** head);
void listFrames(FrameNode* head);
void freeList(FrameNode* head);
void deleteVideo(FrameNode** head);


#endif
