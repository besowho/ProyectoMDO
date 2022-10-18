QT -= gui
QT +=testlib network



CONFIG += c++11 console
CONFIG -= app_bundle



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    communicationthread.cpp \
    controlcommunication.cpp \
    main.cpp \
    maininterface.cpp \
    mavlinkprocess.cpp \
    processimagethread.cpp \
    ssmDetect/Object.c \
    ssmDetect/ObjectPart.c \
    ssmDetect/abs.c \
    ssmDetect/algbwmorph.c \
    ssmDetect/bsxfun.c \
    ssmDetect/bwmorph.c \
    ssmDetect/colon.c \
    ssmDetect/combine_vector_elements.c \
    ssmDetect/convn.c \
    ssmDetect/cov.c \
    ssmDetect/diag.c \
    ssmDetect/diff.c \
    ssmDetect/eml_sort.c \
    ssmDetect/exp.c \
    ssmDetect/extractTheLargestCurve.c \
    ssmDetect/extractTheLargestRegion.c \
    ssmDetect/getEdgeAndObjectsNoScaling.c \
    ssmDetect/getOptimalLineImage_constrained.c \
    ssmDetect/getUnknownWeightForTheFeatureModel.c \
    ssmDetect/imfilter.c \
    ssmDetect/inv.c \
    ssmDetect/isequal.c \
    ssmDetect/ismatrix.c \
    ssmDetect/loadPriorModelFromDisk.c \
    ssmDetect/mean.c \
    ssmDetect/mergePd.c \
    ssmDetect/mldivide.c \
    ssmDetect/normpdf.c \
    ssmDetect/padarray.c \
    ssmDetect/power.c \
    ssmDetect/prod.c \
    ssmDetect/rdivide.c \
    ssmDetect/replacement_bwconncomp.c \
    ssmDetect/rot90.c \
    ssmDetect/rtGetInf.c \
    ssmDetect/rtGetNaN.c \
    ssmDetect/rt_nonfinite.c \
    ssmDetect/run_SSM.c \
    ssmDetect/sqrt.c \
    ssmDetect/ssmDetect.c \
    ssmDetect/ssmDetect_emxutil.c \
    ssmDetect/ssmDetect_initialize.c \
    ssmDetect/ssmDetect_rtwutil.c \
    ssmDetect/ssmDetect_terminate.c \
    ssmDetect/sum.c \
    ssmDetect/suppressDetections.c \
    ssmDetect/svd.c \
    ssmDetect/unique.c \
    testping.cpp



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Include all paths for libraries associated with opencv
INCLUDEPATH += /usr/local/include/opencv4
#INCLUDEPATH += /media/osboxes/rootfs/usr/local/include/
INCLUDEPATH += /usr/local/include/
INCLUDEPATH += /home/osboxes/Documents/mavlink/include

# Link to openCV (include all)
LIBS += -L/usr/local/lib -lopencv_world -lpthread -std=c++11

HEADERS += \
    mavlinkprocess.h \
    nzmqt.hpp \
    ssmDetect/Object.h \
    ssmDetect/ObjectPart.h \
    ssmDetect/abs.h \
    ssmDetect/algbwmorph.h \
    ssmDetect/bsxfun.h \
    ssmDetect/bwmorph.h \
    ssmDetect/colon.h \
    ssmDetect/combine_vector_elements.h \
    ssmDetect/convn.h \
    ssmDetect/cov.h \
    ssmDetect/diag.h \
    ssmDetect/diff.h \
    ssmDetect/eml_sort.h \
    ssmDetect/exp.h \
    ssmDetect/extractTheLargestCurve.h \
    ssmDetect/extractTheLargestRegion.h \
    ssmDetect/getEdgeAndObjectsNoScaling.h \
    ssmDetect/getOptimalLineImage_constrained.h \
    ssmDetect/getUnknownWeightForTheFeatureModel.h \
    ssmDetect/imfilter.h \
    ssmDetect/inv.h \
    ssmDetect/isequal.h \
    ssmDetect/ismatrix.h \
    ssmDetect/loadPriorModelFromDisk.h \
    ssmDetect/mean.h \
    ssmDetect/mergePd.h \
    ssmDetect/mldivide.h \
    ssmDetect/normpdf.h \
    ssmDetect/padarray.h \
    ssmDetect/power.h \
    ssmDetect/prod.h \
    ssmDetect/rdivide.h \
    ssmDetect/replacement_bwconncomp.h \
    ssmDetect/rot90.h \
    ssmDetect/rtGetInf.h \
    ssmDetect/rtGetNaN.h \
    ssmDetect/rt_nonfinite.h \
    ssmDetect/rtwtypes.h \
    ssmDetect/run_SSM.h \
    ssmDetect/sqrt.h \
    ssmDetect/ssmDetect.h \
    ssmDetect/ssmDetect_emxutil.h \
    ssmDetect/ssmDetect_initialize.h \
    ssmDetect/ssmDetect_rtwutil.h \
    ssmDetect/ssmDetect_terminate.h \
    ssmDetect/ssmDetect_types.h \
    ssmDetect/sum.h \
    ssmDetect/suppressDetections.h \
    ssmDetect/svd.h \
    ssmDetect/unique.h \
    controlcommunication.h \
    maininterface.h \
    communicationthread.h \
    processimagethread.h \
    testping.h

LIBS += -lzmq



