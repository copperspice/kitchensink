include copperspice.am

# path to gcc
gccpath=/c/MingW/bin

# list of gcc libraries your app uses
gcclibs=libgcc_s_sjlj-1  libstdc++-6  libwinpthread-1

# list of CopperSpice libraries your app uses
cslibs=Core Gui Multimedia Network Phonon Script Sql Svg WebKit Xml

# location of includes, libs, defines for compiling, turn off debugging
AM_CXXFLAGS+=-mwindows  -I$(CS_HOME)/include/phonon

# 'KitchenSink-CS' target app name
deploy_PROGRAMS = KitchenSink-CS
    
# copy the required CopperSpice and gcc files for deployment - windows only
install-data-hook:	
	mkdir -p $(deploydir)
	mkdir -p $(deploydir)/phonon_backend	

	cp --preserve=timestamps  $(patsubst %,$(gccpath)/%.dll,$(gcclibs))  $(deploydir)
	cp --preserve=timestamps  $(CS_HOME)/bin/lupdate*  $(deploydir)
	cp --preserve=timestamps  $(patsubst %,$(CS_HOME)/bin/libCs%1-0.dll,$(cslibs))  $(deploydir)

    ifeq ($(findstring Phonon,$(cslibs)),Phonon)		
		cp --preserve=timestamps  $(CS_HOME)/lib/phonon_ds9-0.dll  $(deploydir)/phonon_backend
    else		
		@echo "Phonon library was not found"		
    endif

# search path for source
VPATH = ../

# linking
KitchenSink_CS_LDFLAGS=$(AM_LDFLAGS)   $(patsubst %,-lCs%1,$(cslibs))

# 'KitchenSink_CS' must match the app name ( dash had to be replaced )
KitchenSink_CS_SOURCES = \
    main.cpp \
    aboutcs.cpp \
    calendar.cpp \
    colorpicker.cpp \
    dialogs.cpp \
    draw.cpp \
    draw_area.cpp \
    fontpicker.cpp \
    html_viewer.cpp \
    international.cpp \
    line_edit.cpp \
    listview.cpp \
    mdi.cpp \
    musicplayer.cpp \
    sliders.cpp \
    script.cpp \
	stdpath.cpp \
    style_edit.cpp \
    style_dw.cpp \
    svg_view.cpp  \
    svgtextobject.cpp \
    systray.cpp \
    tableview.cpp \
    tablewidget_view.cpp \
    tabdialog.cpp \
    treeview.cpp \
    util.cpp \
    videoplayer.cpp \
    videowidget.cpp \
    videosurface.cpp \
    web_browser.cpp \
    xml.cpp
    
#              
noinst_HEADERS = \
   aboutcs.h \
   calendar.h \
   colorpicker.h \
   dialogs.h \
   draw.h \
   draw_area.h \
   fontpicker.h \
   html_viewer.h  \
   international.h \
   line_edit.h \
   listview.h \
   mdi.h \
   musicplayer.h \
   script.h \
   stdpath.h \
   sliders.h \
   style_dw.h  \
   style_edit.h  \
   svg_view.h  \
   svgtextobject.h \
   systray.h \
   tabdialog.h \
   tableview.h \
   tablewidget_view.h \
   treeview.h \
   util.h \
   videoplayer.h \
   videowidget.h \
   videosurface.h \
   web_browser.h \
   xml.h
                
# list of files that require compiling with moc
MOCS = \
   aboutcs.h \
   calendar.h \
   colorpicker.h \
   dialogs.h \
   draw.h \
   draw_area.h \
   fontpicker.h \
   html_viewer.h \
   international.h \
   line_edit.h \
   listview.h \
   mdi.h \
   musicplayer.h \
   script.h \
   stdpath.h \
   sliders.h \
   style_dw.h \
   style_edit.h \
   svg_view.h  \
   svgtextobject.h \
   systray.h \
   tableview.h \
   tablewidget_view.h \
   tabdialog.h \
   videoplayer.h \
   videowidget.h \
   videosurface.h  \
   web_browser.h \
   xml.h
    
KitchenSink_CS_LDADD=$(patsubst %.h,moc_%.$(OBJEXT),$(MOCS))    
           
#
FORMS = \
    forms/mdi.ui \
    forms/colorpicker.ui \
    forms/fontpicker.ui \
    forms/dialogs.ui \
    forms/html_viewer.ui \
    forms/international.ui \
    forms/line_edit.ui \
    forms/listview.ui \
    forms/musicplayer.ui \
    forms/stdpath.ui \
    forms/style_dw.ui \
    forms/style_edit.ui \
    forms/script.ui \
	 forms/tabdialog.ui \
    forms/tablewidget_view.ui \
    forms/xml.ui    
          
#
TRANSLATIONS =  \
    resources/qt_en.ts   \
    resources/qt_de.ts   \
    resources/qt_fr.ts
    
#
RESOURCES  =  kitchensink.qrc

#    
KitchenSink_CS_SOURCES += qrc_kitchensink.cpp   
    
# use wilcard to obtain just the dependency list
qrc_kitchensink.cpp: kitchensink.qrc   $(wildcard ../resources/*)
