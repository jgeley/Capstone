QT += core widgets

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib/ -lopencv_core \
	-L/usr/local/lib/ -lopenbr
SOURCES += \
	main.cpp
