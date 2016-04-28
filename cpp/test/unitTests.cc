#include "gtest/gtest.h"
#include <cv.h>
#include <openbr/openbr_plugin.h>
#include <opencv2/core/core.hpp>
#include <tuple>
#include <dirent.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include "openBr.h"

using namespace std;

TEST(GET_TEMPLATE_LIST, TEST_EMPTY) {
  OpenBrClass class1;
  string location = "testDirEmpty";
  std::vector<string> v = class1.getTemplateList(location);
  int vsize = v.size();
  EXPECT_EQ(2, vsize);

}

TEST(GET_TEMPLATE_LIST, TEST_WITH_ONLY_GALS) {
  OpenBrClass class1;
  string location = "testDir1";
  std::vector<string> v = class1.getTemplateList(location);
  int vsize = v.size();
  EXPECT_EQ(4, vsize);

}


TEST(GET_TEMPLATE_LIST, TEST_WITH_SOME_GALS) {
  OpenBrClass class1;
  string location = "testDir2";
  std::vector<string> v = class1.getTemplateList(location);
  int vsize = v.size();
  EXPECT_EQ(4, vsize);

}

TEST(GET_MATCH, TEST_NO_MATCH){
  OpenBrClass class1;
  bool foundmatch;
  br::Template  resultTemplate;
  const char * destPtr;
  char base[512] = "testNoMatch/";
  string location = "testNoMatch";
  std::vector<string> v = class1.getTemplateList(location);
  QSharedPointer<br::Distance> distance = br::Distance::fromAlgorithm("FaceRecognition");
  br::Template faceTemplate;
  QFile file("testMatch/aTrWTE.tmpl");
  file.open(QIODevice::ReadOnly);
  QDataStream in(&file);
  in >> faceTemplate;
  std::tie(foundmatch, resultTemplate,destPtr)=  class1.getMatch(v, base, distance, faceTemplate);
  EXPECT_FALSE(foundmatch);
}

TEST(GET_MATCH, TEST__MATCH){
  OpenBrClass class1;
  bool foundmatch;
  br::Template  resultTemplate;
  const char * destPtr;
  char base[512] = "testMatch/";
  string location = "testMatch";
  std::vector<string> v = class1.getTemplateList(location);
  QSharedPointer<br::Distance> distance = br::Distance::fromAlgorithm("FaceRecognition");
  br::Template faceTemplate;
  QFile file("testMatch/aTrWTE.tmpl");
  file.open(QIODevice::ReadOnly);
  QDataStream in(&file);
  in >> faceTemplate;
  std::tie(foundmatch, resultTemplate,destPtr)=  class1.getMatch(v, base, distance, faceTemplate);
  EXPECT_FALSE(foundmatch);
}
int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
        br::Context::initialize(argc,argv);
	return RUN_ALL_TESTS();
}


