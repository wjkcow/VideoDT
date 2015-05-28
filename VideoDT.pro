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
    DecodeSplit/DecodeSplitResult.cpp \
    DecodeSplit/DecodeSplitStage.cpp \
    DecodeSplit/DSPipeline/DecoderFilter.cpp \
    DecodeSplit/DSPipeline/DSPipeline.cpp \
    DecodeSplit/DSPipeline/FrameTypes.cpp \
    DecodeSplit/DSPipeline/HistFilter.cpp \
    DecodeSplit/DSPipeline/PHAFilter.cpp \
    DecodeSplit/DSPipeline/SplitFilter.cpp \
    DecodeSplit/DSPipeline/Utility.cpp \
    DecodeSplit/DSPipeline/WriterFilter.cpp \
    VideoEdit/videocapture.cpp \
    VideoEdit/videoui.cpp \
    DecodeSplit/DSPipeline/CompressFilter.cpp

HEADERS  += \
    mainwindow.h \
    types.h \
    DecodeSplit/DecodeSplitResult.h \
    DecodeSplit/DecodeSplitStage.h \
    DecodeSplit/DSPipeline/DecoderFilter.h \
    DecodeSplit/DSPipeline/DSPipeline.h \
    DecodeSplit/DSPipeline/FrameTypes.h \
    DecodeSplit/DSPipeline/HistFilter.h \
    DecodeSplit/DSPipeline/PHAFilter.h \
    DecodeSplit/DSPipeline/SplitFilter.h \
    DecodeSplit/DSPipeline/Utility.h \
    DecodeSplit/DSPipeline/WriterFilter.h \
    VideoEdit/videocapture.h \
    VideoEdit/videoui.h \
    DecodeSplit/DSPipeline/CompressFilter.h

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
