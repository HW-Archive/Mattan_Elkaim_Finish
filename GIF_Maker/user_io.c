#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include "user_io.h"
#include "project_save.h"
#pragma warning(disable : 4996) // Ignore unsafe functions


/*
Prints the commands options for the user
Input: void
Output: void
*/
void printMenu()
{
	puts("\nWhat would you like to do?");
	printf(" [%u] Exit\n", EXIT);
	printf(" [%u] Add new Frame\n", ADD);
	printf(" [%u] Remove a Frame\n", REMOVE);
	printf(" [%u] Change frame index\n", CHANGE_INDEX);
	printf(" [%u] Rename a Frame\n", RENAME);
	printf(" [%u] Change frame duration\n", CHANGE_DURATION);
	printf(" [%u] Change duration for all frames\n", CHANGE_DURATION_ALL);
	printf(" [%u] List frames\n", LIST);
	printf(" [%u] Play GIF!\n", PLAY);
	printf(" [%u] Play reversed GIF\n", PLAY_REVERSED);
	printf(" [%u] Save project\n", SAVE);
}


/*
Gets a valid user input
Input: min & max of valid input (inclusive)
Output: a valid int
*/
int getUserInput(const int MIN, const int MAX)
{
	int input = 0, result = 0;
	char ch = ' ';

	do
	{
		result = scanf("%d%c", &input, &ch);
		if (result == 2 && ch == '\n')
		{
			// Check further
			if (input >= MIN && input <= MAX)
			{
				return input;
			}
		}
		// Invalid
		else
		{
			clearBuffer();
		}
		printf("Invalid choice. Try again: ");
	} while (true);
}


/*
Simply clears the whole buffer
Input: void
Output: void
*/
void clearBuffer()
{
	int scanfResult = getchar();

	while (scanfResult != '\n' && scanfResult != EOF)
	{
		scanfResult = getchar();
	}
}


/*
Gets a valid string from user.
Also known as "my faggots"
Input: string pointer
Output: void
*/
void myFgets(char* str)
{
	fgets(str, STR_LEN, stdin);
	str[strcspn(str, "\n")] = 0;
}


/*
Gets from user & assigns by-reference
all properties of a frame
Input: path, name and ptr to duration, also head to check
Output: void
*/
void getFrameProperties(char* path, char* name, unsigned int* duration, FrameNode* head)
{
	size_t pathLen = 0, nameLen = 0;
	puts("*** Creating new frame ***");
	puts("Please insert frame path:");
	
	do
	{
		myFgets(path);
		pathLen = strlen(path);

		if (strcspn(path, FIELDS_DELIMITER) == pathLen)
		{
			break;
		}
		// Error, continue
		printf("Path can't contain '%s'! Try again:\n", FIELDS_DELIMITER);
	} while (true);
	
	// Handle case where path is invalid
	if (!isFileExists(path))
	{
		puts("Can't find file!");
		return;
	}

	puts("Please insert frame duration (in milliseconds):");
	*duration = getUserInput(1, INT_MAX);
	puts("Please choose a name for that frame:");

	do
	{
		myFgets(name);
		nameLen = strlen(name);

		if (strcspn(name, FIELDS_DELIMITER) != nameLen)
		{
			printf("Name can't contain '%s'! Try again:\n", FIELDS_DELIMITER);
			continue;
		}
		if (findFrameByName(head, name))
		{
			puts("This name is already taken, please choose another name:");
			continue;
		}

		// No errors
		break;
	} while (true);
}


/*
Checks whether a file exists in a given path
Input: path to check
Output: bool - whether file exists
*/
bool isFileExists(char* path)
{
	FILE* file = fopen(path, "r");

	if (file)
	{
		fclose(file);
		return true;
	}
	return false;
}
