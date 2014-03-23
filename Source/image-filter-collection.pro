include (boost.pri)

TARGET = ImageFilterCollection
QT += widgets
DESTDIR = ../Build

HEADERS += \
	Filter.h \
	FilterProcessor.h \
	Filters/BoxBlur.h \
	Filters/Canny.h \
	Filters/GaussianBlur.h \
	Filters/ImageAlgorithms.h \
	Filters/InvertFilter.h \
	MainWindow.h \

SOURCES += \
	FilterProcessor.cpp \
	Filters/BoxBlur.cpp \
	Filters/Canny.cpp \
	Filters/GaussianBlur.cpp \
	Filters/ImageAlgorithms.cpp \
	Filters/InvertFilter.cpp \
    main.cpp \
    MainWindow.cpp \
    
