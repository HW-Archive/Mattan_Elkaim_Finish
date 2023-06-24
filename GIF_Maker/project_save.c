#include <stdio.h>
#include <stdlib.h>
#include "project_save.h"
#include "user_io.h"
#pragma warning(disable : 4996) // Ignore unsafe functions

extern unsigned int listSize; // To change in loadProject

/*
Saves frames info to a txt file
Input: first frame & save file path
Output: void
*/
void saveProject(FrameNode* head, char* saveFilePath)
{
	FILE* saveFile = fopen(saveFilePath, "w");
	if (!saveFile)
	{
		puts("Error with save file!");
		return;
	}

	while (head)
	{
		fprintf(saveFile, "%s|%u|%s\n", head->frame->name, head->frame->duration, head->frame->path);
		head = head->next;
	}

	puts("Saved project successfully!");
	fclose(saveFile);
}


/*
Builds a movie from a save file.
CHANGES listSize COUNTER!
Input: save file path
Output: head of movie list
*/
FrameNode* loadProject(char* saveFilePath)
{
	FrameNode* head = NULL;
	FrameNode* current = NULL;
	char name[STR_LEN] = { 0 };
	char path[STR_LEN] = { 0 };
	char duration[STR_LEN] = { 0 }; // Later converted to int
	FILE* saveFile = fopen(saveFilePath, "r");

	if (!saveFile)
	{
		puts("Save file not found! Started a new project");
		return NULL;
	}

	listSize = 0; // Reset, start to load frames

	while (true)
	{
		// Extract fields, break once finished
		if (!getNextField(saveFile, name) ||
			!getNextField(saveFile, duration) ||
			!getNextField(saveFile, path))
		{
			break;
		}

		// Check fields validity
		if (findFrameByName(head, name))
		{
			printf("Warning: found multiple occurrences of '%s'. Only first occurrence will be added\n", name);
			continue;
		}
		if (!isFileExists(path))
		{
			printf("Warning: path of frame '%s' not found. It won't be added\n", name);
			continue;
		}

		// Create head if NULL, else append new node
		if (!head)
		{
			head = initNode(name, atoi(duration), path);
			current = head;
		}
		else
		{
			current->next = initNode(name, atoi(duration), path);
			current = current->next;
		}
		listSize++; // Count added frame
	}

	puts("Project loaded successfully");
	fclose(saveFile);
	return head;
}


/*
Gets the next field of frame in a save file,
Input: file ptr, field buffer to save to
Output: bool - is successful (not reached EOF & no errors)
*/
bool getNextField(FILE* file, char* field)
{
	int i = 0;
	char ch = ' ';

	while ((ch = (char)fgetc(file)) != EOF)
	{
		// Reached end of field
		if (ch == FIELDS_DELIMITER || ch == FRAMES_DELIMITER)
		{
			field[i] = 0; // Make sure str ends with NULL
			return true;
		}

		// Edge-case (== to include NULL)
		if (i >= STR_LEN)
		{
			puts("Field exceeded max length!");
			return false;
		}

		field[i] = ch;
		++i;
	}

	return false;
}
