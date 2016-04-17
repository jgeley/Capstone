#include <openbr/openbr.h>
#include <openbr/openbr_plugin.h>
#include <stdio.h>
#include <dirent.h>
#include <vector>
int main(int argc, char *argv[])
{
		
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
			const char *  destPtr = (const char *)s;
			br::File file(destPtr);
			br::TemplateList n = br::TemplateList::fromGallery(file);
			target.append(n);

		}
	}
	br::Template query("images/james3.jpg");
	br::Globals->enrollAll = false;
	query >> *transform;
	QList<float> scores = distance->compare(target,query);

	for (int i = 0; i < scores.count(); ++i){

		printf("Images %s and %s have a match score of %.3f\n",
			qPrintable(target[i].file.name),
			qPrintable(query.file.name),
			scores[i]);
	}
		
	br::Context::finalize();
	return 0;
}
