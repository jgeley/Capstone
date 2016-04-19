#include <unistd.h>
#include <cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <ctime>
#include <opencv2/imgproc/imgproc.hpp>
#include <openbr/openbr_plugin.h>
#include <iostream>
#include "compare.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	while(true){
		std::cout << "Before pic\n";
		int status = system("./pic");
		//if(status < 0){
		//	std::cout << "Error: " << " could not start ./pic" << "\n";
		//} else {
		//	if(WIFEXITED(status)){
		//
		//		std::cout << "Program returned normally with exit code " << WEXITSTATUS(status) << "\n";
		//	} else {
		//		std::cout << "Program exited abnormally";
		//	}
		//}
		time_t t = time(0);
                struct tm * now = localtime(&t);
                int year = now->tm_year + 1900;
                int mon = now->tm_mon + 1;
                int day = now->tm_mday +1;
                int hour= now->tm_hour;
                int min = now->tm_min;
                int sec = now->tm_sec;
                std::string str = "";
                std::ostringstream oss;
                oss << "images/" << mon << "" << day << "" << year << "" << hour << "" << min << "" << sec << ".jpg";
                std::string mys = oss.str();
		std::cout << "after pic\n";
		std::ostringstream oss2;
		oss2 << "raspistill -o " << mys << " -t 100";
		system(oss2.str().c_str());
		//std::string tempstr = "temp.jpg";
                compare(argc,argv,mys.c_str());
		std::cout << "after compare\n";
		
	}
	printf("After all");
	return 0;
}
