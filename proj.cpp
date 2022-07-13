
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <iostream>
using namespace std;

void busy();

int main()
{
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

	// run busy function
	busy();

	return 0;
}

void busy()
{
	//run for set amount of time	
	float i = 1.383468272;
	float j = 2.378364924;
	//continously increment and add two numbers
	for (int a = 0; a < 9999999009; a++)
	{
		j = i * j;
		i++;
//		cout << a << endl;
	}
	printf("busy complete.\n");
	ifstream fin;
	fin.open("../../../../sys/class/thermal/thermal_zone0/temp");
	ofstream fout;
	fout.open("tempbusy.txt");
	string line = "";
	getline(fin, line);
	fout << line;
	fin.close();
	fout.close();
	
	return;
	//write temp to tempbusy.txt
}
