#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include "user_io.h"
#pragma warning(disable : 4996) // Ignore unsafe functions


/*
Prints the commands options for the user
Input: void
Output: void
*/
void printMenu()
{
	puts("What would you like to do?");
	puts(" [0] Exit");
	puts(" [1] Add new Frame");
	puts(" [2] Remove a Frame");
	puts(" [3] Change frame index");
	puts(" [4] Change frame duration");
	puts(" [5] Change duration of all frames");
	puts(" [6] List frames");
	puts(" [7] Play movie!");
	puts(" [8] Save project");
}


/*
Gets a valid user input
Input: min & max of valid input
Output: a valid int
*/
int getUserInput(const unsigned int MIN, const unsigned int MAX)
{
	int input = 0, result = 0;
	char ch = ' ';

	while (true)
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
	}
}


/*
Simply clears the whole buffer
Input: void
Output: void
*/
void clearBuffer()
{
	int scanfResult = 0;
	while ((scanfResult = getchar()) != '\n' && scanfResult != EOF);
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
Input: pointers to path, name and duration, also head to check
Output: void
*/
void getFrameProperties(char** path, char** name, unsigned int *duration, FrameNode* head)
{
	puts("*** Creating new frame ***");
	puts("Please insert frame path:");
	myFgets(*path);
	puts("Please insert frame duration (in milliseconds):");
	*duration = getUserInput(0, (unsigned int)UINT_MAX);
	puts("Please choose a name for that frame:");
	do
	{
		myFgets(*name);
		if (!findFrameByName(head, *name))
		{
			break; // Unique name
		}
		puts("The name is already taken, please enter another name:");
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
