#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "linkedList.h"
#include "user_io.h"
#pragma warning(disable : 4996) // Ignore unsafe functions

unsigned int listSize = 0;

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

	getFrameProperties(path, name, &duration, *head);
	if (!duration)
	{
		return; // Duration unchanged => failed to get path & name
	}

	listSize++; // Update counter

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
Input: ptr to list head, frame's name, bool to free memory
Output: void
*/
void removeFrame(FrameNode** head, char* name, bool isDelete)
{
	FrameNode* current = *head;
	FrameNode* temp = NULL;

	// Edge-case: list is empty
	if (!(*head))
	{
		puts("List is already empty!");
		return;
	}

	listSize--; // Update counter

	// Edge-case: remove head
	if (!strcmp((*head)->frame->name, name))
	{
		temp = (*head)->next;
		if (isDelete)
		{
			free((*head)->frame);
			free(*head);
		}
		*head = temp;
		return;
	}

	while (current->next)
	{
		if (!strcmp(current->next->frame->name, name))
		{
			temp = current->next->next;
			if (isDelete)
			{
				free(current->next->frame);
				free(current->next);
			}
			current->next = temp;
			return; // Deleted successfully
		}
		current = current->next;
	}

	// Finished loop without returning, failed
	puts("Frame not found!");
}


/*
Changes the name of a frame
Input: head of list, frame name to rename
Output: void
*/
void renameFrame(FrameNode* head, char* name)
{
	FrameNode* toRename = findFrameByName(head, name);
	if (!toRename)
	{
		puts("Frame not found!");
		return;
	}

	puts("Enter new name for frame:");
	myFgets(name); // Re-use variable
	strcpy(toRename->frame->name, name);
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
	toChange->frame->duration = getUserInput(1, (unsigned int)UINT_MAX);;
}


/*
Changes the duration of each frame to 1 value
according to user's input
Input: head
Output: void
*/
void changeAllDuration(FrameNode* head)
{
	unsigned int newDuration = 0;

	// Change only if there are frames
	if (!head)
	{
		puts("No frames in GIF");
		return;
	}

	puts("Enter new duration for all frames:");
	newDuration = getUserInput(1, (unsigned int)UINT_MAX);

	while (head)
	{
		head->frame->duration = newDuration;
		head = head->next;
	}
}


/*
Moves a frame by its name to a new position (user input),
note that position starts from 1 & is in range of size
Input: ptr to head of list, name to move
Output: void
*/
void changeFramePosition(FrameNode** head, char* name)
{
	int newPosition = 0;
	FrameNode* toMove = NULL;
	FrameNode* current = NULL;
	FrameNode* temp = NULL;

	if (!(*head))
	{
		puts("List is empty!");
		return;
	}

	toMove = findFrameByName(*head, name);
	if (!toMove)
	{
		puts("Frame not found!");
		return;
	}
	removeFrame(head, name, false); // Remove the frame from old position
	listSize++; // Since it was decreased in removeFrame

	puts("Enter the new position (from 1) in the movie you wish to place the frame:");
	newPosition = getUserInput(1, listSize);
	newPosition--; // Normalize to index from 0

	// Edge-case: change head
	if (newPosition == 0)
	{
		toMove->next = *head;
		*head = toMove;
		return;
	}

	// Reach position to insert to
	current = *head;
	while (newPosition > 1)
	{
		current = current->next;
		newPosition--;
	}

	// Insert the frame
	temp = current->next;
	current->next = toMove;
	toMove->next = temp;
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
Reverses a linked list, iteratively
Input: head of list & ptr to reversed head
Output: void - changing by-reference
*/
void reverseList(FrameNode* head, FrameNode** reversedHead)
{
	FrameNode* current = head;
	FrameNode* temp = NULL;
	FrameNode* prev = NULL;
	FrameNode** returnNode = NULL;

	while (current)
	{
		temp = current->next;
		current->next = prev;
		
		prev = current;
		current = temp;
	}

	*reversedHead = prev;
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
	listSize = 0;
}
