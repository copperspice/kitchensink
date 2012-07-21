include copperspice.am

# path to gcc
gccpath=/c/MingW

# list of gcc libraries your app uses
gcclibs=libgcc_s_sjlj-1  libstdc++-6  libwinpthread-1

# list of CopperSpice libraries your app uses
cslibs=Core Gui Multimedia Network Phonon Script Svg Sql Xml XmlPatterns

# location of includes, libs, defines for compiling, turn off debugging
AM_CXXFLAGS+=-mwindows  -I$(CS_HOME)/include/phonon  -gtoggle 
    
# copy the required CopperSpice and gcc files for deployment - windows only
install-exec-hook:	
	mkdir -p $(deploydir)
	mkdir -p $(deploydir)/phonon_backend	
	cp --preserve=timestamps  $(patsubst %,$(gccpath)/bin/%.dll,$(gcclibs))  $(deploydir)
	cp --preserve=timestamps  $(patsubst %,$(CS_HOME)/bin/libCs%1-0.dll,$(cslibs))  $(deploydir)
    ifeq ($(findstring Phonon,$(cslibs)),Phonon)		
		cp --preserve=timestamps  $(CS_HOME)/lib/phonon_ds9-0.dll  $(deploydir)/phonon_backend
    else		
		@echo "Phonon library was not found"		
    endif

# copy the required CopperSpice dll files for deployment - x11 only
# install-exe-hook:
#		install -p  -D $(patsubst %,$(CS_HOME)/lib/libCs%1.so,$(cslibs))   $(deploydir)
#      ifeq ($(findstring Phonon,$(cslibs)),Phonon)		
#			install -p  $(CS_HOME)/lib/phonon_gstreamer.so  $(deploydir)/phonon_backend
#      else		
#			@echo "Phonon library was not found"		
#      endif

# search path for source
VPATH = ../

# 'KitchenSink-Cs1' target app name
deploy_PROGRAMS = KitchenSink-Cs1

# linking
KitchenSink_Cs1_LDFLAGS=$(AM_LDFLAGS)   $(patsubst %,-lCs%1,$(cslibs))

# 'KitchenSink_Cs1' must match the app name ( dash had to be replaced )
KitchenSink_Cs1_SOURCES = \
    main.cpp \
    calendar.cpp \
    colorpicker.cpp \
    dialogs.cpp \
    draw.cpp \
    draw_area.cpp \
    fontpicker.cpp \
    line_edit.cpp \
    listview.cpp \
    mdi.cpp \
    musicplayer.cpp \
    sliders.cpp \
    script.cpp \
    style_edit.cpp \
    style_dw.cpp \
    svg_view.cpp  \
    svgtextobject.cpp \
    systray.cpp \
    tableview.cpp \
    tablewidget_view.cpp \
    tabdialog.cpp \
    translate.cpp \
    treeview.cpp \
    util.cpp \
    videoplayer.cpp \
    videowidget.cpp \
    videosurface.cpp \
    xml.cpp   \
    core_me.cpp   \
    sql_me.cpp  \
    xml_me.cpp  \
    gui_me.cpp  \
	phone_me.cpp \
	svg_me.cpp \
	multi_me.cpp \
	xmlpat_me.cpp \
    network_me.cpp	
 	
# ../web_me.cpp
     
#              
noinst_HEADERS = \
	calendar.h \
	colorpicker.h \
	dialogs.h \
	draw.h \
    draw_area.h \
	fontpicker.h \
	line_edit.h \
	listview.h \
    mdi.h \
    musicplayer.h \
	script.h \
    sliders.h \
	style_dw.h  \
    style_edit.h  \
    svg_view.h  \
    svgtextobject.h \
    systray.h \
	tabdialog.h \
    tableview.h \
    tablewidget_view.h \
    translate.h \
    treeview.h \
	util.h \
	videoplayer.h \
    videowidget.h \
    videosurface.h \
    xml.h
                
# list of files that require compiling with moc
MOCS = \
    calendar.h \
	colorpicker.h \
	dialogs.h \
    draw.h \
    draw_area.h \
	fontpicker.h \
	line_edit.h \
	listview.h \
    mdi.h \
    musicplayer.h \
    script.h \
    sliders.h \
	style_dw.h \
    style_edit.h \
    svg_view.h  \
    svgtextobject.h \
    systray.h \
	tableview.h \
    tablewidget_view.h \
    tabdialog.h \
    translate.h \
    videoplayer.h \
    videowidget.h \
    videosurface.h  \
    xml.h
    
KitchenSink_Cs1_LDADD=$(patsubst %.h,moc_%.$(OBJEXT),$(MOCS))    
           
#
FORMS = \
    mdi.ui \
    line_edit.ui \
    style_dw.ui \
    style_edit.ui \
    colorpicker.ui \
    fontpicker.ui \
    dialogs.ui \
    listview.ui \
    musicplayer.ui \
    script.ui \
	tabdialog.ui \
    tablewidget_view.ui \
	translate.ui \
    xml.ui    
          
#
TRANSLATIONS =  \
    resources/qt_en.ts   \
    resources/qt_de.ts   \
    resources/qt_fr.ts
    
#
RESOURCES  =  kitchensink.qrc

#    
KitchenSink_Cs1_SOURCES += qrc_kitchensink.cpp   
    
#depedency to build qrc     * do this  *
