TARGET = ImageFilterCollection
QT += widgets
DESTDIR = ../Build

HEADERS += \
	Filter.h \
	FilterProcessor.h \
	Filters/InvertFilter.h \
	MainWindow.h \

SOURCES += \
	FilterProcessor.cpp \
	Filters/InvertFilter.cpp \
    main.cpp \
    MainWindow.cpp \
    
