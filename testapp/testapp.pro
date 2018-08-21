TEMPLATE = app
QT += core widgets
LIBS += -L../bin
INCLUDEPATH += \
                ../include \
                ./tmp/moc
DESTDIR = ../bin

MOC_DIR +=  tmp/moc
RCC_DIR +=  tmp/rcc
OBJECTS_DIR += tmp/obj

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    test1.cpp

HEADERS += \
    mainwindow.h \
    test1.h
