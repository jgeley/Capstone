QT += core widgets

INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib/ -lopencv_core \
	-L/usr/local/lib/ -lopenbr
SOURCES += \
	pic.cpp
SOURCES += \
	compare.cpp
