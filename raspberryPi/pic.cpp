#include <unistd.h>
#include <cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <openbr/openbr_plugin.h>
#include <iostream>
#include "compare.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	br::Context::initialize(argc,argv);
	QSharedPointer<br::Transform> transform = br::Transform::fromAlgorithm("FaceRecognition");
	QSharedPointer<br::Distance> distance = br::Distance::fromAlgorithm("FaceRecognition");
	int i = 0;
	unsigned int microseconds = 1000000;
	while(true){
		br::Template thing("0.webcam");
		thing >> *transform;
		std::cout << thing.file.flat().toStdString() << "\n";
		if(thing.file.contains("Confidence")){
			float confidence = thing.file.get<float>("Confidence");
			if(confidence > 0.0) {
				//cv::imwrite("temp.jpg",thing.m());
				//std::string tempstr = "images/temp.jpg";
				//compare(argc,argv,tempstr.c_str());
			} else{
				std::cout << "No Face\n";	
			}
		}
		i++;
		usleep(microseconds);		
	}
	printf("Before compare\n");
	//compare(argc,argv);		
	return 0;
}
