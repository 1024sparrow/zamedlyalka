TEMPLATE = lib
DESTDIR = ../bin

MOC_DIR +=  tmp/moc
RCC_DIR +=  tmp/rcc
OBJECTS_DIR += tmp/obj
INCLUDEPATH +=  \
                . \
                ../include \
                ./tmp/moc
