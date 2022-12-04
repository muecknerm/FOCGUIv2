QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


DEFINES += QCUSTOMPLOT_USE_LIBRARY

# Link with debug version of qcustomplot if compiling in debug mode, else with release library:
CONFIG(debug, release|debug) {
  win32:QCPLIB = qcustomplotd2
  else: QCPLIB = qcustomplotd
} else {
  win32:QCPLIB = qcustomplot2
  else: QCPLIB = qcustomplot
}
LIBS += -L$$PWD/./ -l$$QCPLIB

SOURCES += \
    add_plot_dialoag.cpp \
    add_variable_dialog.cpp \
    dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    parameter_window.cpp \
    serial_thread.cpp \
    tabbar_class.cpp

HEADERS += \
    add_plot_dialoag.h \
    add_variable_dialog.h \
    dialog.h \
    mainwindow.h \
    parameter_window.h \
    serial_thread.h \
    tabbar_class.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS +=
