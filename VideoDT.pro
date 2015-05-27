#-------------------------------------------------
#
# Project created by QtCreator 2015-05-24T17:15:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoDT
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
    mainwindow.cpp \
    decodesplitstage.cpp \
    decodesplitresult.cpp

HEADERS  += \
    mainwindow.h \
    decodesplitstage.h \
    decodesplitresult.h \
    types.h \
    ../../../Dropbox/opcv/opcv/DecoderFilter.h \
    ../../../Dropbox/opcv/opcv/DSPipeline.h \
    ../../../Dropbox/opcv/opcv/FrameTypes.h \
    ../../../Dropbox/opcv/opcv/HistFilter.h \
    ../../../Dropbox/opcv/opcv/PHAFilter.h \
    ../../../Dropbox/opcv/opcv/SplitFilter.h \
    ../../../Dropbox/opcv/opcv/WriterFilter.h

FORMS    += \
    mainwindow.ui

INCLUDEPATH += /usr/local/include\

LIBS += -L/usr/local/lib\
     -lopencv_core \
     -lopencv_imgproc \
     -lopencv_features2d \
     -lopencv_highgui \
     -lopencv_ml \
     -lopencv_video \
     -lopencv_calib3d \
     -lopencv_objdetect \
     -lopencv_contrib \
     -lopencv_legacy \
     -lopencv_stitching \
     -ltbb

