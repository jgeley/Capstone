QT += core widgets

INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib/ -lopencv_core \
	-L/usr/local/lib/ -lopenbr \
	-L/usr/local/lib/ -lopencv_highgui \
	-L/usr/local/lib/ -lopencv_imgproc 
SOURCES += \
	pic.cpp
