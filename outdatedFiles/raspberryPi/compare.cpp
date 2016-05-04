#include <iostream>
#include <openbr/openbr_plugin.h>
#include <stdio.h>
#include <dirent.h>
#include <vector>
#include <ctime>
#include <sstream>
#include <string>
#include <fstream>


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
	QString highestName = "";
	for (int i = 0; i < scores.count(); ++i){

		printf("%s and %s score:  %.3f\n",qPrintable(target[i].file.name),qPrintable(query.file.name),scores[i]);
		if(scores[i] > highest){
			highestName = target[i].file.name;
			highest = scores[i];
		}
	}
	if(highest > 3){
		std::cout << "You have been here before\n";
		std::ofstream out;
                out.open("historytemp.csv",std::ios::trunc);
                //out <<  tempfile << "," << "0\n";
                //out.close();
		std::ifstream data("history.csv");
                std::string line;
                //std::cout << "-------------------------------------------\n";
                while(std::getline(data,line)){
		      std::vector<std::string> row;
                      std::stringstream lineStream(line);
                      std::string cell;
                      while(std::getline(lineStream,cell,',')){
			      row.push_back(cell);
                              //std::cout << cell << "\n";
                      }
		      QString current = QString(row[0].c_str());
			if(highestName.compare(current) == 0){
				std::cout << qPrintable(current);
				int value = atoi(row[1].c_str());
				value = value + 1;
				std::ostringstream oss;
				oss << row[0] << "," << value << "," << row[2] << "," <<row[3];			
				out << oss.str() << "\n";
			}else {
				out << line  << "\n";
			}
                }
                out.close();
		data.close();
		// copy over historytemp to history file
		out.open("history.csv",std::ios::trunc);
		std::ifstream data2("historytemp.csv");
		while(std::getline(data2,line)){
			out << line << "\n";
		}
		out.close();
		data2.close();
                //std::cout << "---------------------------------------------\n";
	}
	else {
		// Makes gallery
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
		// add entry to history.csv
		std::ofstream out;
		
		// get age estimation
		QSharedPointer<br::Transform> ageTransform = br::Transform::fromAlgorithm("AgeEstimation");
		br::Template ageQuery(tempfile);
		ageQuery >> *ageTransform;
		int age = int(ageQuery.file.get<float>("Age"));
		// get gender
		QSharedPointer<br::Transform> genderTransform = br::Transform::fromAlgorithm("GenderEstimation");
		br::Template genderQuery(tempfile);
		genderQuery >> *genderTransform;
		QString gender = genderQuery.file.get<QString>("Gender");
		out.open("history.csv",std::ios::app);
		out <<  tempfile << "," << "0," << age << "," << qPrintable(gender) << "\n";
		out.close();			
	}
	br::Context::finalize();
	return 0;
}
