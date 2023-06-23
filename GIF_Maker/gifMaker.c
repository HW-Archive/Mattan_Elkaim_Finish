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
#include "project_save.h"

int main(void) // 835 lines
{
	int userChoice = 0;
	bool isProjectSaved = false; // Has user saved recent changes
	char string[STR_LEN] = { 0 }; // Temp for several functions
	FrameNode* first = NULL;
	FrameNode* temp = NULL; // For reverse

	puts("Welcome to Magshimim GIF Maker! What would you like to do?");
	puts(" [0] Create a new project");
	puts(" [1] Load existing project");
	userChoice = getUserInput(0, 1);
	if (userChoice == 1)
	{
		puts("Enter the full path of the project:");
		myFgets(string);
		first = loadProject(string);
	}

	while (true)
	{
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
			isProjectSaved = false;
			break;
		case REMOVE:
			puts("Enter frame name to remove:");
			myFgets(string);
			removeFrame(&first, string, true);
			isProjectSaved = false;
			break;
		case CHANGE_INDEX:
			puts("Enter frame name to move:");
			myFgets(string);
			changeFramePosition(&first, string);
			isProjectSaved = false;
			break;
		case RENAME:
			puts("Enter frame name to rename:");
			myFgets(string);
			renameFrame(first, string);
			isProjectSaved = false;
			break;
		case CHANGE_DURATION:
			puts("Enter frame name to change:");
			myFgets(string);
			changeFrameDuration(first, string);
			isProjectSaved = false;
			break;
		case CHANGE_DURATION_ALL:
			changeAllDuration(first);
			isProjectSaved = false;
			break;
		case LIST:
			listFrames(first);
			break;
		case PLAY:
			play(first);
			break;
		case PLAY_REVERSED:
			reverseList(first, &temp);
			listFrames(temp);
			play(temp);
			break;
		case SAVE:
			puts("Enter path to save file:");
			myFgets(string);
			saveProject(first, string);
			isProjectSaved = true;
			break;
		}
	}
	
	// A backup saving system in-case user forgets to save
	if (!isProjectSaved)
	{
		saveProject(first, DEFAULT_SAVE_FILE);
		puts("Saved recent changed automatically at %s\n", DEFAULT_SAVE_FILE);
	}

	deleteVideo(&first); // Free memory
	(void)getchar();
	return 0;
}
