
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <pthread.h>
using namespace std;

void busy();

int conv_temp(string i);

int main()
{
	//spawn threads for the busy-wait function.
	pthread_t threads[2];

	// open temperature file, store in temp.txt
	ifstream fin;
	fin.open("../../../../sys/class/thermal/thermal_zone0/temp");
	/*  debugging 
	    if (fin.is_open())
	    {
	    printf("File opened successfully.\n");
	    }
	    else
	    {
	    printf("File wasn't opened.\n");
	    }
	    */
	ofstream fout;
	fout.open("temp.txt");
	string line = "";
	getline(fin, line);
	fout << line;
	fin.close();
	fout.close();

	int temp = conv_temp(line);
	cout << "temp: " << temp << endl;

	// run busy function
	busy();

	return 0;
}

void busy()
{
	//run for set amount of time	
	int count = 0;
	float i = 1.383468272;
	float j = 2.378364924;
	//continously increment and add two numbers
	printf("Busy function starting. Enter 'q' and then enter to break busy loop and display temperature.\n");
	char input = 'p';
	while (1)
	{
		j = i * j;
		i++;
		//cin >> input;
		if (count == 10000000000)
		{
			ifstream fin;
			fin.open("../../../../sys/class/thermal/thermal_zone0/temp");
			ofstream fout;
			fout.open("tempbusy.txt");
			string line = "";
			getline(fin, line);
			fout << line;
			fin.close();
			fout.close();
			int temp = conv_temp(line);
			//cout << "temp: " << temp << endl;
			count = 0;	//fstream 
		}
		count++;
	}
	printf("busy complete.\n");

	return;
	//write temp to tempbusy.txt
}

int conv_temp(string i)
{
	//convert temp string to an int, then get rid of decimals
	int t = stoi(i);
	t = t / 1000;

	return t;
}
