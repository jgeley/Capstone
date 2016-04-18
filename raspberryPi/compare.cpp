#include <iostream>
#include <openbr/openbr.h>
#include <openbr/openbr_plugin.h>
#include <stdio.h>
#include <dirent.h>
#include <vector>
#include <ctime>
#include <sstream>
#include <string>


int compare(int argc, char *argv[], char const *tempfile)
{
	printf("%s\n",tempfile);		
	br::Context::initialize(argc,argv,"",true);
	std::vector<std::string> mylist;
	mylist.clear();	
	DIR *d;
	struct dirent *dir;
	d = opendir("gals");
	if (d){
		while((dir = readdir(d)) != NULL){
			mylist.push_back(dir->d_name);
		}
		closedir(d);
	}
		
	QSharedPointer<br::Transform> transform = br::Transform::fromAlgorithm("FaceRecognition");		
	QSharedPointer<br::Distance> distance = br::Distance::fromAlgorithm("FaceRecognition");
		
	
	br::TemplateList target = br::TemplateList::fromGallery("gals/meds.gal");
	for(unsigned t= 0; t < mylist.size(); ++t){
		char *s = new char[mylist.at(t).length()+1];
                strcpy(s,mylist.at(t).c_str());
                if(strstr(s,".gal") != NULL){
			char base[] = "gals/";
			strcat(base,s);
			const char *  destPtr = (const char *)base;
			//printf("%s\n",destPtr);
			br::File file(destPtr);
			br::TemplateList n = br::TemplateList::fromGallery(file);
			target.append(n);

		}
	}
	br::Template query(tempfile);
	br::Globals->enrollAll = false;
	query >> *transform;
	QList<float> scores = distance->compare(target,query);
	int highest = -1;
	for (int i = 0; i < scores.count(); ++i){

		printf("%s and %s score:  %.3f\n",qPrintable(target[i].file.name),qPrintable(query.file.name),scores[i]);
		if(scores[i] > highest){
			highest = scores[i];
		}
	}
	if(highest > 3){
		std::cout << "You have been here before";
	}
	else {
		std::cout << "You are new here, your picture will be added to our database";
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
		oss << "gals/" << mon << "" << day << "" << year << "" << hour << "" << min << "" << sec << ".gal";
		std::string mys = oss.str();
		QString qstr = QString::fromStdString(mys);	
		br::File gallery(qstr);
		br::File file(tempfile);
		br::Globals->setProperty("algorithm","FaceRecognition");
		br::Enroll(file,gallery); 			
		
	}
	br::Context::finalize();
	return 0;
}
