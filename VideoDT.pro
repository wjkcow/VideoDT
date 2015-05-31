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
    DecodeSplit/DSPipeline/CompressFilter.cpp \
    Dectector/Dectector.cpp \
    Dectector/TrackingTask.cpp \
    Dectector/TTaskManager.cpp \
    FrameLibrary.cpp \
    Tracking/Tracking.cpp \
    Tracking/TrackingResult.cpp \
    Tracking/CppMT/CMT.cpp \
    Tracking/CppMT/common.cpp \
    Tracking/CppMT/Consensus.cpp \
    Tracking/CppMT/Fusion.cpp \
    Tracking/CppMT/gui.cpp \
    Tracking/CppMT/Matcher.cpp \
    Tracking/CppMT/Tracker.cpp \
    Tracking/CppMT/fastcluster/fastcluster.cpp \
    Dectector/TrackerInfo.cpp \
    Tracking/TrackingAlgorithm.cpp \
    Tracking/OpenTLD/src/3rdparty/cvblobs/blob.cpp \
    Tracking/OpenTLD/src/3rdparty/cvblobs/BlobContour.cpp \
    Tracking/OpenTLD/src/3rdparty/cvblobs/BlobOperators.cpp \
    Tracking/OpenTLD/src/3rdparty/cvblobs/BlobProperties.cpp \
    Tracking/OpenTLD/src/3rdparty/cvblobs/BlobResult.cpp \
    Tracking/OpenTLD/src/3rdparty/cvblobs/ComponentLabeling.cpp \
    Tracking/OpenTLD/src/libopentld/tld/Clustering.cpp \
    Tracking/OpenTLD/src/libopentld/tld/DetectionResult.cpp \
    Tracking/OpenTLD/src/libopentld/tld/DetectorCascade.cpp \
    Tracking/OpenTLD/src/libopentld/tld/EnsembleClassifier.cpp \
    Tracking/OpenTLD/src/libopentld/tld/ForegroundDetector.cpp \
    Tracking/OpenTLD/src/libopentld/tld/MedianFlowTracker.cpp \
    Tracking/OpenTLD/src/libopentld/tld/NNClassifier.cpp \
    Tracking/OpenTLD/src/libopentld/tld/TLD.cpp \
    Tracking/OpenTLD/src/libopentld/tld/TLDUtil.cpp \
    Tracking/OpenTLD/src/libopentld/tld/VarianceFilter.cpp \
    Tracking/OpenTLD/src/libopentld/mftracker/BB.cpp \
    Tracking/OpenTLD/src/libopentld/mftracker/BBPredict.cpp \
    Tracking/OpenTLD/src/libopentld/mftracker/FBTrack.cpp \
    Tracking/OpenTLD/src/libopentld/mftracker/Lk.cpp \
    Tracking/OpenTLD/src/libopentld/mftracker/Median.cpp

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
    DecodeSplit/DSPipeline/CompressFilter.h \
    Dectector/Dectector.h \
    Dectector/TrackingTask.h \
    Dectector/TTaskManager.h \
    FrameLibrary.h \
    Tracking/Tracking.h \
    Tracking/TrackingResult.h \
    Tracking/CppMT/CMT.h \
    Tracking/CppMT/common.h \
    Tracking/CppMT/Consensus.h \
    Tracking/CppMT/Fusion.h \
    Tracking/CppMT/gui.h \
    Tracking/CppMT/Matcher.h \
    Tracking/CppMT/Tracker.h \
    Tracking/CppMT/fastcluster/fastcluster.h \
    Tracking/CppMT/logging/log.h \
    Dectector/TrackerInfo.h \
    Tracking/TrackingAlgorithm.h \
    Tracking/OpenTLD/src/3rdparty/cvblobs/blob.h \
    Tracking/OpenTLD/src/3rdparty/cvblobs/BlobContour.h \
    Tracking/OpenTLD/src/3rdparty/cvblobs/BlobLibraryConfiguration.h \
    Tracking/OpenTLD/src/3rdparty/cvblobs/BlobOperators.h \
    Tracking/OpenTLD/src/3rdparty/cvblobs/BlobProperties.h \
    Tracking/OpenTLD/src/3rdparty/cvblobs/BlobResult.h \
    Tracking/OpenTLD/src/3rdparty/cvblobs/ComponentLabeling.h \
    Tracking/OpenTLD/src/libopentld/tld/Clustering.h \
    Tracking/OpenTLD/src/libopentld/tld/DetectionResult.h \
    Tracking/OpenTLD/src/libopentld/tld/DetectorCascade.h \
    Tracking/OpenTLD/src/libopentld/tld/EnsembleClassifier.h \
    Tracking/OpenTLD/src/libopentld/tld/ForegroundDetector.h \
    Tracking/OpenTLD/src/libopentld/tld/IntegralImage.h \
    Tracking/OpenTLD/src/libopentld/tld/MedianFlowTracker.h \
    Tracking/OpenTLD/src/libopentld/tld/NNClassifier.h \
    Tracking/OpenTLD/src/libopentld/tld/NormalizedPatch.h \
    Tracking/OpenTLD/src/libopentld/tld/TLD.h \
    Tracking/OpenTLD/src/libopentld/tld/TLDUtil.h \
    Tracking/OpenTLD/src/libopentld/tld/VarianceFilter.h \
    Tracking/OpenTLD/src/libopentld/mftracker/BB.h \
    Tracking/OpenTLD/src/libopentld/mftracker/BBPredict.h \
    Tracking/OpenTLD/src/libopentld/mftracker/FBTrack.h \
    Tracking/OpenTLD/src/libopentld/mftracker/Lk.h \
    Tracking/OpenTLD/src/libopentld/mftracker/Median.h

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
