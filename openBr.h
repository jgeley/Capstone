#include <cv.h>
#include <openbr/openbr_plugin.h>
#include <opencv2/core/core.hpp>
#include <tuple>
#include <dirent.h>
#include <iostream>
#include <unistd.h>
#include <string>

using namespace std;

class OpenBrClass{
	public:
		// This method gets the templates that are in the given folder
		// param location - a string that is the location of the folder
		// return - a string vector with all of teh template names
		std::vector<string> getTemplateList(string location);
		
		// finds if there is a match or not in the given tempalte list
		// param templateList - a string vector with all of the names of the templates to compare to
		// param base - a char[] that is the base/folder that the templates are in
		// param distance - the distance pointer that is used to compare two templates
		// param faceTemplate - the template that is being compared to every other template
		// return - a tuple that contains a boolean (if a match is found), a template ( the result template if found), char * (the ptr of the result)
		std::tuple<bool, br::Template,const char *> getMatch(std::vector<string> templateList, char base[512], QSharedPointer<br::Distance> distance, br::Template faceTemplate);
		
		// Creates a new template file with the given info
		// param base - the folder it is to go in
		// param targetTemplate - the template being stored
		// param age - age template (clone of targetTempalte)
		// param ageTransform - the age transformer
		// param gender - gender template (clone of targetTemplate)
		// param genderTransform - the gender transformer
		void createTemplateFile(QString base, br::Template targetTemplate, br::Template age, QSharedPointer<br::Transform> ageTransform, br::Template gender, QSharedPointer<br::Transform> genderTransform);
		
		// updates the template file with a new "times" variable (increments by 1)
		// param destPtr - the pointer of the file location
		// param resultTemplate - the template that is being incremented
		void updateTemplateFile(const char * destPtr,br::Template resultTemplate);
};
