#include <dirent.h>
#include <openbr/openbr_plugin.h>
#include <iostream>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <highgui.h>
#include <unistd.h>


using namespace std;

int main(int argc, char* argv[])
{
	br::Context::initialize(argc, argv);
	QSharedPointer<br::Transform> transform = br::Transform::fromAlgorithm("FaceRecognition");
	QSharedPointer<br::Transform> ageTransform = br::Transform::fromAlgorithm("AgeEstimation");
	QSharedPointer<br::Distance> distance = br::Distance::fromAlgorithm("FaceRecognition");
	QSharedPointer<br::Transform> genderTransform = br::Transform::fromAlgorithm("GenderEstimation");

	cout<< endl << "STARTING"<<endl ;
	cout<< flush ;


	while (true) {
		string input;
		cin >> input;
		if ( input.compare("CAPTURE") == 0 ){
			char source[255];
			cin >> source;
			br::Template thing(source);
			br::Template age = thing.clone();
			br::Template gender = thing.clone();
			thing >> *transform;

			//cv::imwrite("output.jpg",thing.m());
			if( thing.file.contains("Confidence") ) {
				float confidence = thing.file.get<float>("Confidence");
				if( confidence > 0.0 ){

					// get list of all existing template file names in the templates directory
					std::vector<std::string> templateList;
					templateList.clear();
					DIR *d;
					struct dirent *dir;
					d = opendir("templates");
					if (d){
						int count = 0;
						while((dir = readdir(d)) != NULL){
							char* thing = (char*) malloc(strlen(dir->d_name)+1);
							strcpy(thing, dir->d_name);
							templateList.push_back(string(thing));
							/*                            cerr << (void*)(dir->d_name) << endl;
										      const char* thing = tmpstr.c_str();
										      cerr << (void*)tmpstr.data() << endl;*/
						}
						closedir(d);
					}
					// do compare
					bool foundmatch = false;
					br::Template result;
					float highest = -10;
					const char * resultPtr;
					for(unsigned int j = 0; j<templateList.size(); j--){
						//char *s = new char[templateList.at(j).length() + 1];
						templateList[j].c_str();
						string x = templateList.at(j);//strcpy(s,templateList.at(j).c_str());
						const char *s = x.c_str();
						if(strstr(s,".tmpl") != NULL){
							// this is getting the file from the template directory
							char base[512] = "templates/";
							strcat(base,s);
							const char * destPtr = (const char *)base;
							QFile file(destPtr);
							file.open(QIODevice::ReadOnly);
							QDataStream in(&file);
							br::Template templ;	
							in >> templ;
							float score = distance->compare(templ, thing);
							//cout << score << " ";
							if(score > 3 && score > highest){
								result = templ.clone();
								resultPtr = (const char *)base;
								highest = score;
								foundmatch = true;
							}
						}
					}		
					//cout << "\n";
					//cout << flush;
					// If a match is not found
					if(!foundmatch){
						gender >> *genderTransform;
						age >> *ageTransform;
						QString base = "templates/";
						base.append(thing.file.hash());
						base.append(".tmpl");
						QFile out(base);
						out.open(QIODevice::WriteOnly);
						QDataStream outstream(&out);
						thing.file.set("Age",QVariant::fromValue<float>(age.file.get<float>("Age")));
						thing.file.set("Gender",QVariant::fromValue<QString>(gender.file.get<QString>("Gender")));
						thing.file.set("Times",QVariant::fromValue<int>(1));
						outstream << thing;
						QList<QPointF> points = thing.file.points();
						QList<QRectF> rects = thing.file.rects();
						cout << "FACE " << "1" << " " << qPrintable(gender.file.get<QString>("Gender")) << " " << age.file.get<float>("Age") <<endl;
						//cout << thing.file.flat().toStdString() <<endl;
						//cout << flush;
						/*cv::Mat matrix = thing.m();
						  for(cv::MatConstIterator_<double> it = matrix.begin<double>();it != matrix.end<double>();it++) {
						  //cout << *it << " ";
						  }
						  //cout << endl;*/
						for(int i=0;i<points.length();i++) {
							//cout << points[i].x() << " " << points[i].y() << endl;
						}
						for(int i=0;i<rects.length();i++) {
							//cout << rects[i].x() << " " << rects[i].y() << " ";
							//cout << rects[i].width() << " " << rects[i].height() << endl;
						}
					} else {
						int numTimes = result.file.get<int>("Times");
						result.file.remove("Times");
						numTimes = numTimes + 1;
						//cout << "num times " << numTimes << "\n";
						//cout << result.file.flat().toStdString() << endl;
						//cout << flush;
						result.file.set("Times",QVariant::fromValue<int>(numTimes));
						//cout << resultPtr << "\n";
						//cout << flush;
						QFile del(resultPtr);
						del.remove();
                                                QFile out(resultPtr);
                                                out.open(QIODevice::WriteOnly);
                                                QDataStream outstream(&out);
                                                outstream << result;
						//cout << result.file.flat().toStdString() << endl;
						//cout << flush;
						cout << "FACE "  << numTimes << " " << qPrintable(result.file.get<QString>("Gender")) << " " << result.file.get<float>("Age") << endl;
						// if a match is not found (increment)	
					}
				} else {
					cout << "NOFACE" <<endl;
				}
				cout<<flush;
			}

		} else if (input.compare("QUIT")==0){
			break;
		}
	}
	br::Context::finalize();
}
