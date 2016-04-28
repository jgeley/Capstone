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
		std::vector<string> getTemplateList(string location);
		std::tuple<bool, br::Template,const char *> getMatch(std::vector<string> templateList, char base[512], QSharedPointer<br::Distance> distance, br::Template faceTemplate);
		 void createTemplateFile(QString base, br::Template targetTemplate, br::Template age, QSharedPointer<br::Transform> ageTransform, br::Template gender, QSharedPointer<br::Transform> genderTransform);
		void updateTemplateFile(const char * destPtr,br::Template resultTemplate);
};
