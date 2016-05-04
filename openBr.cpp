#include <cv.h>
#include <openbr/openbr_plugin.h>
#include <opencv2/core/core.hpp>
#include <dirent.h>
#include <iostream>
#include <unistd.h>
#include "openBr.h"
#include <string>
using namespace std;

// This method gets the templates that are in the given folder
// param location - a string that is the location of the folder
// return - a string vector with all of teh template names
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

// finds if there is a match or not in the given tempalte list
// param templateList - a string vector with all of the names of the templates to compare to
// param base - a char[] that is the base/folder that the templates are in
// param distance - the distance pointer that is used to compare two templates
// param faceTemplate - the template that is being compared to every other template
// return - a tuple that contains a boolean (if a match is found), a template ( the result template if found), char * (the ptr of the result)
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

// Creates a new template file with the given info
// param base - the folder it is to go in
// param targetTemplate - the template being stored
// param age - age template (clone of targetTempalte)
// param ageTransform - the age transformer
// param gender - gender template (clone of targetTemplate)
// param genderTransform - the gender transformer
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

// updates the template file with a new "times" variable (increments by 1)
// param destPtr - the pointer of the file location
// param resultTemplate - the template that is being incremented
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
