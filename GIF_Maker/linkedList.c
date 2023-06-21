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
		puts("Error with memory allocation!");
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
		puts("Error with memory allocation!");
		return NULL;
	}
	newNode->frame = initFrame(name, duration, path);
	newNode->next = NULL;
	return newNode;
}


/*
Finds the target frame by its name
Input: head of list, str name to match
Output: ptr to frame | NULL if not found
*/
FrameNode* findFrameByName(FrameNode* head, char* name)
{
	while (head)
	{
		if (!strcmp(head->frame->name, name))
		{
			break; // Name found
		}
		head = head->next;
	}

	return head; // Frame with matched name
}


/*
Appends a new frame node to the end of the list
Input: ptr to first frame & new frame to append
Output: void
*/
void addFrame(FrameNode** head)
{
	char path[STR_LEN] = { 0 };
	char name[STR_LEN] = { 0 };
	unsigned int duration = 0;
	FrameNode* temp = NULL;

	getFrameProperties(&path, &name, &duration, *head);

	// Handle case where path is invalid
	if (!isFileExists(path))
	{
		puts("Can't find file! Frame will not be added");
		return;
	}

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
Removes a frame node from the list
Input: ptr to head of list, name of frame to remove
Output: void
*/
void removeFrame(FrameNode** head, char* name)
{
	FrameNode* current = *head;
	FrameNode* temp = NULL;

	// Edge-case: list is empty
	if (!(*head))
	{
		puts("List is already empty!");
		return;
	}

	// Edge-case: remove head
	if (!strcmp((*head)->frame->name, name))
	{
		free((*head)->frame);
		free(*head);
		*head = NULL;
		return;
	}

	while (current->next)
	{
		if (!strcmp(current->next->frame->name, name))
		{
			temp = current->next->next;
			free(current->next->frame);
			free(current->next);
			current->next = temp;
			return; // Deleted successfully
		}
	}

	// Finished loop without returning, failed
	puts("Frame not found!");
}


/*
Changes the duration of a given frame
name according to user's input
Input: head of list, frame name to change
Output: void
*/
void changeFrameDuration(FrameNode* head, char* name)
{
	FrameNode* toChange = findFrameByName(head, name);
	if (!toChange)
	{
		puts("Frame not found!");
		return;
	}

	printf("Enter new duration: ");
	toChange->frame->duration = getUserInput(0, (unsigned int)UINT_MAX);;
}


/*
Changes the duration of each frame to 1 value
according to user's input
Input: head
Output: void
*/
void changeAllDuration(FrameNode* head)
{
	unsigned int newDuration = getUserInput(0, (unsigned int)UINT_MAX);

	while (head)
	{
		head->frame->duration = newDuration;
		head = head->next;
	}
}


/*
Simply prints all nodes' properties
Input: head of list
Output: void
*/
void listFrames(FrameNode* head)
{
	char textDuration[STR_LEN] = { 0 }; // To format

	puts("\tName            Duration        Path");
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
