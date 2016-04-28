#include <cv.h>
#include <openbr/openbr_plugin.h>
#include <opencv2/core/core.hpp>
#include <dirent.h>
#include <iostream>
#include <unistd.h>
#include "openBr.h"
#include <string>
using namespace std;

std::vector<string>  OpenBrClass::getTemplateList(string location){
	std::vector<std::string> templateList;
	templateList.clear();
	DIR *d;
	struct dirent *dir;
	d = opendir(location.c_str());
	if(d){
		while((dir = readdir(d)) != NULL){
			char* dirname = (char*) malloc(strlen(dir->d_name) + 1);
			strcpy(dirname,dir->d_name);
			templateList.push_back(string(dirname));
		}
		closedir(d);
	}
	return templateList;
}

std::tuple<bool, br::Template,const char *> OpenBrClass::getMatch(std::vector<string> templateList, char base[512], QSharedPointer<br::Distance> distance, br::Template faceTemplate){
	float highest = -10;
	bool foundmatch = false;
	br::Template result;
	const char * resultPtr;
	for(unsigned int j = 0; j < templateList.size(); j--){
		templateList[j].c_str();
		string x = templateList.at(j);
		const char *s = x.c_str();
		if(strstr(s,".tmpl") != NULL){
			strcat(base, s);
			const char * destPtr = (const char *)base;
			QFile file(destPtr);
			file.open(QIODevice::ReadOnly);
			QDataStream in(&file);
			br::Template templ;
			in >> templ;
			float score = distance -> compare(templ, faceTemplate);
			if(score > 3 && score > highest){
				result = templ.clone();
				resultPtr = (const char *)base;
				highest = score;
				foundmatch = true;
			}
		}	
	}
	return std::make_tuple(foundmatch,result,resultPtr);
}

void OpenBrClass::createTemplateFile(QString base, br::Template targetTemplate, br::Template age, QSharedPointer<br::Transform> ageTransform, br::Template gender, QSharedPointer<br::Transform> genderTransform){
	gender >> *genderTransform;
	age >> *ageTransform;
	base.append(targetTemplate.file.hash());
	base.append(".tmpl");
	QFile out(base);
	out.open(QIODevice::WriteOnly);
	QDataStream outstream(&out);
	targetTemplate.file.set("Age",QVariant::fromValue<float>(age.file.get<float>("Age")));
	targetTemplate.file.set("Gender",QVariant::fromValue<QString>(gender.file.get<QString>("Gender")));
	targetTemplate.file.set("Times",QVariant::fromValue<int>(1));
	outstream << targetTemplate;
	cout << "FACE " << "1" << " " << qPrintable(gender.file.get<QString>("Gender")) << " " << age.file.get<float>("Age") << endl;
}
void OpenBrClass::updateTemplateFile(const char * destPtr,br::Template resultTemplate){
	int numTimes = resultTemplate.file.get<int>("Times");
	resultTemplate.file.remove("Times");
	numTimes = numTimes + 1;
	resultTemplate.file.set("Times",QVariant::fromValue<int>(numTimes));
	QFile del(destPtr);
	del.remove();
	QFile out(destPtr);
	out.open(QIODevice::WriteOnly);
	QDataStream outstream(&out);
	outstream << resultTemplate;
	cout << "FACE " << numTimes <<  " " << qPrintable(resultTemplate.file.get<QString>("Gender")) << " " << resultTemplate.file.get<float>("Age") << endl;
	cout << flush;
}
