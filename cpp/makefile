openbr_loc= /home/mitchell/Applications/apps/local

all : main

main.o : main.cpp
	g++ -Wall -g -c `pkg-config --cflags --libs Qt5Widgets opencv`	-fPIC -I$(openbr_loc)/include main.cpp -o main.o

main : main.o
	g++ -Wall -g `pkg-config --cflags --libs Qt5Widgets opencv` -fPIC -I/include -L$(openbr_loc)/lib -lopenbr main.o -o main
