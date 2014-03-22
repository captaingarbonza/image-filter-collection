include (boost.pri)

TARGET = ImageFilterCollection
QT += widgets
DESTDIR = ../Build

HEADERS += \
	Filter.h \
	FilterProcessor.h \
	Filters/BoxBlur.h \
	Filters/Convolution.h \
	Filters/GaussianBlur.h \
	Filters/InvertFilter.h \
	MainWindow.h \

SOURCES += \
	FilterProcessor.cpp \
	Filters/BoxBlur.cpp \
	Filters/Convolution.cpp \
	Filters/GaussianBlur.cpp \
	Filters/InvertFilter.cpp \
    main.cpp \
    MainWindow.cpp \
    
