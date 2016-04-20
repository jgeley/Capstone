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
//    QSharedPointer<br::Distance> distance = br::Distance::fromAlgorithm("FaceRecognition");

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
            thing >> *transform;
            age >> *ageTransform;

            //cv::imwrite("output.jpg",thing.m());
            //cout<<thing.m()<<endl;
            //cout << thing.file.m_metadata <<endl;
            //cout << thing.file.flat().toStdString() <<endl;
            if( thing.file.contains("Confidence") ) {
                float confidence = thing.file.get<float>("Confidence");
                if( confidence > 0.0 ){
                    QList<QPointF> points = thing.file.points();
                    QList<QRectF> rects = thing.file.rects();
                    cout << "FACE "<<points.length()<<" "<<rects.length()<<endl;
                    cout << age.file.flat().toStdString() <<endl;
                    /*cv::Mat matrix = thing.m();
                    for(cv::MatConstIterator_<double> it = matrix.begin<double>();it != matrix.end<double>();it++) {
                        cout << *it << " ";
                    }
                    cout << endl;*/
                    for(int i=0;i<points.length();i++) {
                        cout << points[i].x() << " " << points[i].y() << endl;
                    }
                    for(int i=0;i<rects.length();i++) {
                        cout << rects[i].x() << " " << rects[i].y() << " ";
                        cout << rects[i].width() << " " << rects[i].height() << endl;
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
