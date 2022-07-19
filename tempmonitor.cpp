
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
using namespace std;

static volatile bool stop = false;
int temp_change = 0;
int temp = 0;
int state = 0;

void busy();
int get_temp(int m, string dest);
void fan(int s);
static void* userInput_thread(void*);

int main()
{
	printf("Enter amount to add to temperature: ");
	cin >> temp_change;
	//spawn threads for the busy-wait function.
	pthread_t tId;
	(void) pthread_create(&tId, 0, userInput_thread, 0);

	temp = get_temp(temp_change, "temp.txt");
	cout << "Initial temp: " << temp << endl;
	// run busy function
	busy();

	(void) pthread_join(tId, NULL);
	
	if (state == 1)
	{	
		fan(0);
	}

	return 0;
}

void busy()
{
	int count = 0;
	printf("\nTemperature monitoring starting. Press 'q' to quit and  display temperature.\n");
	while(stop == false)
	{
		temp = get_temp(temp_change, "tempbusy.txt");

		if (temp >= 80 && state == 0)
		{
			state = 1;
			fan(state); //on
			sleep(10);
		}	
		else if (temp < 70 && state == 1)
		{
			state = 0;
			fan(state); //off
			sleep(10);
		}

		count++;
		if (count == 1000)
		{
			count = 0;
			cout << "Current temp: " << temp << endl;
		}

	}
	temp = get_temp(temp_change, "busytemp.txt");
	printf("\nProgram quit.\n");
	cout << "Temp: " << temp << endl;
	//write temp to busytemp.txt
}

int get_temp(int m, string dest)
{
	// open temperature file, store in temp.txt
	ifstream fin;
	fin.open("../../../../sys/class/thermal/thermal_zone0/temp");
	ofstream fout;
	fout.open(dest.c_str());
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
void fan(int s)
{
	if (s == 1)
	{
		//activate GPIO pins
		system("gpio mode 1 out");
		system("gpio toggle 1");
		printf("FAN ON WHOOOOOOOSH");
	}
	else if (s == 0)
	{
		//deactivate GPIO pins
		//system("gpio mode 1 in");
		system("gpio toggle 1");
		printf("fan not on big sad");
	}
}
