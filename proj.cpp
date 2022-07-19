
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <pthread.h>
using namespace std;

static volatile bool stop = false;

void busy();
static void* userInput_thread(void*);

int main()
{
	//spawn threads for the busy-wait function.
	pthread_t tId;
	(void) pthread_create(&tId, 0, userInput_thread, 0);

	// run busy function
	busy();

	(void) pthread_join(tId, NULL);

	return 0;
}

void busy()
{
	float i = 1.383468272;
	float j = 2.378364924;
	//continously increment and multiply two numbers
	printf("\nBusy function starting. Press 'q' to break busy loop and display temperature.\n");
	while(stop == false)
	{
		j = i*j;
		i = i*i;
	}
	printf("\nProgram manually quit.\n");
}

static void* userInput_thread(void*)
{
	system("stty raw"); //set terminal to raw mode so enter doesn't need to be pressed
	while(stop == false)
	{
		if (getchar() == 'q')
		{
			stop = true;
			system("stty raw");
		}
	}
	return 0;
}
