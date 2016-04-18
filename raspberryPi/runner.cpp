#include <unistd.h>
#include <cv.h>
#include <opencv2/highgui/highgui.hpp>
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
		std::cout << "after pic\n";
		system("raspistill -o temp.jpg -t 100");
		std::string tempstr = "temp.jpg";
                compare(argc,argv,tempstr.c_str());
		std::cout << "after compare\n";
		
	}
	printf("After all");
	return 0;
}
