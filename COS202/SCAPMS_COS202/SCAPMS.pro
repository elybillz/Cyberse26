QT += widgets
CONFIG += c++17
TEMPLATE = app
TARGET = SCAPMS

SOURCES += \
    main.cpp \
    model/PatientRecord.cpp \
    controller/ClinicManager.cpp \
    gui/MainWindow.cpp \
    utils/FileHandler.cpp

HEADERS += \
    model/PatientRecord.h \
    controller/ClinicManager.h \
    gui/MainWindow.h \
    utils/FileHandler.h
