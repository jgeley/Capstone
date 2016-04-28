openbr_loc= /home/mitchell/Applications/apps/local

all : openBrMain



openBr.o : openBr.cpp
	g++ -Wall -g -std=gnu++0x -c `pkg-config --cflags --libs Qt5Widgets opencv`  -fPIC -I$(openbr_loc)/include openBr.cpp -o openBr.o

openBrMain.o : openBrMain.cpp openBr.o
	g++ -Wall -g -std=gnu++0x -c `pkg-config --cflags --libs Qt5Widgets opencv`  -fPIC -I$(openbr_loc)/include openBrMain.cpp -o openBrMain.o

openBrMain : openBr.o openBrMain.o 
	g++ -Wall -std=gnu++0x -g `pkg-config --cflags --libs Qt5Widgets opencv` -fPIC -I/include -L$(openbr_loc)/lib -lopenbr openBrMain.o openBr.o -o openBrMain
	


clean :
	rm openBr
	rm openBr.o
