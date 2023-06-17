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


int main(void)
{
	//printf("Welcome to Magshimim Movie Maker! what would you like to do?\n");
	FrameNode* first = initNode("hithere", 5000, "C:\\");
	//first->next = initNode("well well", 321, "C:\\PICS");
	addFrame(&first);
	listFrames(first);
	//getUserInput(EXIT, SAVE);
	deleteVideo(&first);
	(void)getchar();
	return 0;
}
