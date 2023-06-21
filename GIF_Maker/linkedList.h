#ifndef LINKEDLISTH
#define LINKEDLISTH

// size_t listSize = 0; // NOT USED YET

#define STR_LEN 100 // Also defined in user_io.h

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
FrameNode* findFrameByName(FrameNode* head, char* name);
void addFrame(FrameNode** head);
void removeFrame(FrameNode** head, char* name);
void changeFrameDuration(FrameNode* head, char* name);
void changeAllDuration(FrameNode* head);
void listFrames(FrameNode* head);
void freeList(FrameNode* head);
void deleteVideo(FrameNode** head);


#endif
