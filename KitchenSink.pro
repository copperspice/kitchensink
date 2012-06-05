#-------------------------------------------------
#
# Project created by QtCreator 2012-05-15T13:01:27
#
#-------------------------------------------------

QT += core
QT += gui
QT += network
QT += phonon
QT += sql
QT += webkit
QT += xml

TARGET = KitchenSink
TEMPLATE = app

SOURCES  += \
    main.cpp\
    mdi.cpp \
    util.cpp \
    line_edit.cpp \
    web_browser.cpp \
    html_viewer.cpp \
    calendar.cpp \
    draw.cpp \
    draw_area.cpp \
    sliders.cpp \
    style_edit.cpp \
    style_dw.cpp \    
    dialogs.cpp \
    colorpicker.cpp \
    fontpicker.cpp \
    treeview.cpp \
    listview.cpp \
    tableview.cpp \
    musicplayer.cpp \
    systray.cpp \
    tablewidget_view.cpp \
    aboutcs.cpp \
    tabdialog.cpp \
    translate.cpp \
    xml.cpp


HEADERS  += \
    mdi.h \
    util.h \
    line_edit.h \
    web_browser.h \
    html_viewer.h \
    calendar.h \
    draw.h \
    draw_area.h \
    sliders.h \
    style_edit.h \
    style_dw.h \    
    dialogs.h \
    colorpicker.h \
    fontpicker.h \
    treeview.h \
    listview.h \
    tableview.h \
    musicplayer.h \
    systray.h \
    tablewidget_view.h \
    aboutcs.h \
    tabdialog.h \
    translate.h \
    xml.h

FORMS    += \
    mdi.ui \
    line_edit.ui \
    html_viewer.ui \
    style_dw.ui \
    style_edit.ui \
    colorpicker.ui \
    fontpicker.ui \
    dialogs.ui \
    listview.ui \
    musicplayer.ui \
    tablewidget_view.ui \
    tabdialog.ui \
    translate.ui \
    xml.ui

RESOURCES  += kitchensink.qrc

TRANSLATIONS += resources/qt_en.ts   \
                resources/qt_de.ts   \
                resources/qt_fr.ts




