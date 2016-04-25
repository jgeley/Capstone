#include <unistd.h>
#include <cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <openbr/openbr_plugin.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	br::Context::initialize(argc,argv);
	QSharedPointer<br::Transform> transform = br::Transform::fromAlgorithm("FaceRecognition");
	QSharedPointer<br::Distance> distance = br::Distance::fromAlgorithm("FaceRecognition");
	int i = 0;
	unsigned int microseconds = 1;
	int mycontinue = 1;
	while(mycontinue == 1){
		br::Template thing("0.webcam");
		thing >> *transform;
		if(thing.file.contains("Confidence")){
			float confidence = thing.file.get<float>("Confidence");
			if(confidence > 0.0) {
				std::cout << "Found face\n";
				mycontinue = 0;
			} else{
				std::cout << "No Face\n";	
			}
		}

		i++;
		usleep(microseconds);		
	}
	br::Context::finalize();
	return 0;
}
