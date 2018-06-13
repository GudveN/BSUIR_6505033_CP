TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    cpu.cpp \
    pci.cpp \
    systeminf.cpp \
    hardware.cpp \
    memory.cpp \
    hdd.cpp \
    gui.cpp

HEADERS += \
    cpu.h \
    pci.h \
    systeminf.h \
    hardware.h \
    memory.h \
    hdd.h \
    gui.h
