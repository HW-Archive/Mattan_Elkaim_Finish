#include <stdio.h>
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
	printf("What would you like to do?\n");
	printf(" [0] Exit\n");
	printf(" [1] Add new Frame\n");
	printf(" [2] Remove a Frame\n");
	printf(" [3] Change frame index\n");
	printf(" [4] Change frame duration\n");
	printf(" [5] Change duration of all frames\n");
	printf(" [6] List frames\n");
	printf(" [7] Play movie!\n");
	printf(" [8] Save project\n");
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
