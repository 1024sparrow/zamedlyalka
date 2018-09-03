################################################################
# Qwt Widget Library
# Copyright (C) 1997   Josef Wilgen
# Copyright (C) 2002   Uwe Rathmann
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the Qwt License, Version 1.0
################################################################

QT = core widgets
CONFIG+=qwt
#TARGET       = simpleplot

INCLUDEPATH += /usr/include/qwt
LIBS += -lqwt

SOURCES = \
    main.cpp \
    mw.cpp

HEADERS += \
    mw.h

FORMS +=
