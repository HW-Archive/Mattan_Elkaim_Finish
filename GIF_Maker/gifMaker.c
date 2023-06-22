/*********************************
* Class: MAGSHIMIM C2			 *
* Week:                			 *
* Name: Mattan Elkaim            *
**********************************/
#pragma warning(disable : 4996) // Ignore unsafe functions
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "linkedList.h"
#include "view.h"
#include "user_io.h"

extern unsigned int listSize;

int main(void)
{
	int userChoice = 0;
	FrameNode* first = initNode("1", 500, "C:\\Users\\Magshimim\\Desktop\\gif_images\\1.png");
	listSize++;
	char string[STR_LEN] = { 0 }; // Temp for several functions

	puts("Welcome to Magshimim Movie Maker! what would you like to do?");
	while (true)
	{
		printf("%u items\n", listSize);
		printMenu();
		userChoice = getUserInput(EXIT, SAVE);

		// Separate from switch to save the use of a flag
		if (userChoice == EXIT)
		{
			puts("\nBye!");
			break;
		}

		switch (userChoice)
		{
		case ADD:
			addFrame(&first);
			break;
		case REMOVE:
			puts("Enter frame name to remove:");
			myFgets(string);
			removeFrame(&first, string, true);
			break;
		case CHANGE_INDEX:
			puts("Enter frame name to move:");
			myFgets(string);
			changeFramePosition(&first, string);
			break;
		case CHANGE_DURATION:
			puts("Enter frame name to change:");
			myFgets(string);
			changeFrameDuration(first, string);
			break;
		case CHANGE_DURATION_ALL:
			changeAllDuration(first);
			break;
		case LIST:
			listFrames(first);
			break;
		case PLAY:
			play(first);
			break;
		default:
			break;
		}

		puts(""); // Newline
	}

	deleteVideo(&first);
	(void)getchar();
	return 0;
}
