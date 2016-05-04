#include <tuple>
#include <cv.h>
#include <openbr/openbr_plugin.h>
#include <opencv2/core/core.hpp>
#include <dirent.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include "openBr.h"
using namespace std;

int main(int argc, char* argv[]){
	br::Context::initialize(argc,argv);
	QSharedPointer<br::Transform> transform = br::Transform::fromAlgorithm("FaceRecognition");
	QSharedPointer<br::Distance> distance = br::Distance::fromAlgorithm("FaceRecognition");
	QSharedPointer<br::Transform> ageTransform = br::Transform::fromAlgorithm("AgeEstimation");
	QSharedPointer<br::Transform> genderTransform = br::Transform::fromAlgorithm("GenderEstimation");
	cout << endl << "STARTING" << endl;
	cout << flush
	;
	while(true) {
		string input;
		cin >> input;
		if( input.compare("CAPTURE") == 0){
			char source[255];
			cin >> source;
			br::Template faceTemplate(source);
			br::Template age = faceTemplate.clone();
			br::Template gender = faceTemplate.clone();

			faceTemplate >> *transform;
			
			if(faceTemplate.file.contains("Confidence")) {
				float confidence = faceTemplate.file.get<float>("Confidence");
				if(confidence > 0.0){
						
					OpenBrClass class1;
					string location = "templates";
					std::vector<string> v = class1.getTemplateList(location);
					char base[512] = "templates/";
					bool foundmatch;
					br::Template resultTemplate;
					const char * destPtr;
					std::tie(foundmatch, resultTemplate,destPtr) = class1.getMatch(v, base, distance, faceTemplate);
					if(!foundmatch){
						QString baseQString = "templates/";
						class1.createTemplateFile(baseQString,faceTemplate,age,ageTransform,gender,genderTransform);
					} 
					else {
						class1.updateTemplateFile(destPtr,resultTemplate);
					}					
				}
				else {
					cout << "NOFACE\n";
				}
			}
		} else if (input.compare("QUIT") == 0){
			break;
		}
		cout << flush;	
	}
}
