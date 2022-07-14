
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <pthread.h>
using namespace std;

static volatile bool stop = false;
int temp_change = 0;
int temp = 0;

void busy();
int get_temp(int m);
static void* userInput_thread(void*);

int main()
{
	printf("\nEnter amount of degrees to add to temp: ");
	cin >> temp_change;

	//spawn threads for the busy-wait function.
	pthread_t tId;
	(void) pthread_create(&tId, 0, userInput_thread, 0);

	temp = get_temp(temp_change);
	cout << "Initial temp: " << temp << endl;
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
		j = i * j;
		i++;
		//temp = get_temp(temp_change);
	//	cout << "Temp: " << temp << endl;
	}
		temp = get_temp(temp_change);
	printf("\nProgram manually quit.\n");
	cout << "Temp: " << temp << endl;
	//write temp to tempbusy.txt
}

int get_temp(int m)
{
	// open temperature file, store in temp.txt
	ifstream fin;
	fin.open("../../../../sys/class/thermal/thermal_zone0/temp");
	ofstream fout;
	fout.open("temp.txt");
	string line = "";
	getline(fin, line);
	fout << line;
	fin.close();
	fout.close();
	//convert temp string to an int, then get rid of decimals
	int t = stoi(line);
	t = t / 1000;
	t = t + temp_change;

	return t;
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
