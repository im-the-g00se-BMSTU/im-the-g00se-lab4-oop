QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    facade.cpp \
    file_reader.cpp \
    qt_scene_drawer.cpp \
    touchpad_scene_controller.cpp \
    transform_matrix.cpp \
    transform_matrix_builder.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    constants.h \
    edge.h \
    facade.h \
    facade_operation_result.h \
    figure.h \
    file_reader.h \
    normalization_parameters.h \
    point3d.h \
    qt_scene_drawer.h \
    scene.h \
    scene_drawer_base.h \
    scene_object.h \
    touchpad_scene_controller.h \
    transform_matrix.h \
    transform_matrix_builder.h \
    vertex.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
