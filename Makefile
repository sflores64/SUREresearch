all: proj.cpp tempmonitor.cpp
	g++ proj.cpp -lpthread -Wall -oproj
	g++ tempmonitor.cpp -lpthread -Wall -otemp
