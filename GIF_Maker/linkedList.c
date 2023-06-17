#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "linkedList.h"
#include "user_io.h"
#pragma warning(disable : 4996) // Ignore unsafe functions


/*
Inits a new frame struct with given params
Input: frame's name, duration & path
Output: ptr to new frame struct
*/
Frame* initFrame(char* name, unsigned int duration, char* path)
{
	Frame* newFrame = (Frame*)malloc(sizeof(Frame));
	if (!newFrame)
	{
		printf("Error with memory allocation!\n");
		return NULL;
	}
	strcpy(newFrame->name, name);
	strcpy(newFrame->path, path);
	newFrame->duration = duration;
	return newFrame;
}


/*
Inits a new node for a linked list,
with Frame struct inside
Input: params for the inner Frame struct
Output: ptr to new node
*/
FrameNode* initNode(char* name, unsigned int duration, char* path)
{
	FrameNode* newNode = (FrameNode*)malloc(sizeof(FrameNode));
	if (!newNode)
	{
		printf("Error with memory allocation!\n");
		return NULL;
	}
	newNode->frame = initFrame(name, duration, path);
	newNode->next = NULL;
	return newNode;
}


/*
Appends a new frame node to the end of the list
Input: ptr to first frame & new frame to append
*/
void addFrame(FrameNode** head)
{
	char path[STR_LEN] = { 0 };
	char name[STR_LEN] = { 0 };
	unsigned int duration = 0;
	FrameNode* temp = NULL;

	printf("*** Creating new frame ***\n");
	printf("Please insert frame path:\n");
	myFgets(path);
	printf("Please insert frame duration (in miliseconds):\n");
	getUserInput(0, (unsigned int)UINT_MAX);
	printf("Please choose a name for that frame:\n");
	myFgets(name);

	// Handle edge-case
	if (!(*head))
	{
		*head = initNode(name, duration, path);
		return;
	}

	temp = *head;
	// Reach end of list
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = initNode(name, duration, path);
}


/*
Simply prints all nodes' properties
Input: head of list
Output: void
*/
void listFrames(FrameNode* head)
{
	char textDuration[STR_LEN] = { 0 }; // To format

	printf("\tName            Duration        Path\n");
	while (head)
	{
		sprintf(textDuration, "%u ms", head->frame->duration); // Easier to format as one
		printf("\t%-16s%-16s%s\n", head->frame->name, textDuration, head->frame->path);
		head = head->next;
	}
}


/*
Frees all dynamically-allocated nodes in a list
Input: head of list
Output: void
*/
void freeList(FrameNode* head)
{
	FrameNode* temp = NULL;

	while (head)
	{
		temp = head->next;
		free(head->frame);
		free(head);
		head = temp;
	}
}


/*
Frees the video frames & resets head by-reference
Input: ptr to first frame
Output: void
*/
void deleteVideo(FrameNode** head)
{
	freeList(*head);
	*head = NULL;
}
