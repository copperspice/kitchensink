include copperspice.am

# dist windows
distdir_custom=install_win/dist

# path to gcc
gccpath=/c/MingW/bin

# list of gcc libraries your app uses
gcclibs=libgcc_s_sjlj-1  libstdc++-6  libwinpthread-1

# list of CopperSpice libraries your app uses
cslibs=Core Gui Multimedia Network OpenGL Script Sql Svg WebKit Xml XmlPatterns

# BROOM - missing Declarative Phonon

# disable console on window, location of includes, defines
AM_CXXFLAGS+=-mwindows  -I$(CS_HOME)/include/phonon

# 'KitchenSink-Cs4' target app name
deploy_PROGRAMS = KitchenSink-Cs4

# copy the required CopperSpice and gcc files for deployment - windows only
install-data-hook:	
	mkdir -p $(deploydir)
	mkdir -p $(deploydir)/phonon_backend	

	rsync -W -a --size-only  $(patsubst %,$(gccpath)/%.dll,$(gcclibs))  $(deploydir)
#	rsync -W -a --size-only  $(CS_HOME)/bin/lupdate*  $(deploydir)
	rsync -W -a --size-only  $(patsubst %,$(CS_HOME)/bin/libCs%1-0.dll,$(cslibs))  $(deploydir)

    ifeq ($(findstring Phonon,$(cslibs)),Phonon)		
		cp --preserve=timestamps  $(CS_HOME)/lib/phonon_ds9-0.dll  $(deploydir)/phonon_backend
    else		
		@echo "Phonon library was not found"		
    endif

# search path for source
VPATH = ../

# linking
KitchenSink_Cs4_LDFLAGS=$(AM_LDFLAGS)   $(patsubst %,-lCs%1,$(cslibs)) -lopengl32

# 'KitchenSink_Cs4' must match the app name ( dash had to be replaced )
KitchenSink_Cs4_SOURCES = \
    main.cpp \
    aboutcs.h \
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
    web_browser.cpp \
    xml.cpp \
    analogclock.cpp \
    animated_tiles.cpp \
    draglabel.cpp  \
    dragwidget.cpp \
    glwidget.cpp \
    grabber.cpp  \
    lighting.cpp \
    mandelbrot_thread.cpp \
    mandelbrot_widget.cpp \
    screenshot.cpp


# musicplayer.cpp \
# videosurface.cpp \
# videoplayer.cpp \
# videowidget.cpp \
# qmlapplicationviewer.cpp
# wiggle_boxes.cpp
# world_clock.cpp


#
noinst_HEADERS = \
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
   web_browser.h \
   xml.h \
   analogclock.h  \
   animated_tiles.h  \
   draglabel.h \
   dragwidget.h  \
   glwidget.h  \
   grabber.h  \
   lighting.h  \
   mandelbrot_thread.h  \
   mandelbrot_widget.h  \
   screenshot.h

# musicplayer.h \
# qmlapplicationviewer.h
# videoplayer.h \
# videowidget.h \
# videosurface.h \
# wiggle_boxes.h
# world_clock.h

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
RESOURCES = kitchensink.qrc

# use wilcard to obtain just the dependency list
qrc_kitchensink.cpp: kitchensink.qrc   $(wildcard ../resources/*)

# source distribution
nodist_KitchenSink_Cs4_SOURCES = qrc_kitchensink.cpp

distdir: $(DISTFILES)
	cd .. ; \
	test -d "$(distdir_custom)" || mkdir -p "$(distdir_custom)" ; \
	for f in $(DIST_SOURCES)  ; do install -D $$f $(distdir_custom)/$$f ; done ;\
	for f in $(HEADERS)       ; do install -D $$f $(distdir_custom)/$$f ; done ;\
	for f in $(FORMS)         ; do install -D $$f $(distdir_custom)/$$f ; done ;\
	mkdir -p $(distdir_custom)/bin           ; \
	mkdir -p $(distdir_custom)/resources     ; \
	cp kitchensink.qrc        $(distdir_custom)/     ; \
	cp install_files/cs.conf  $(distdir_custom)/     ; \
	cp bin/*.am               $(distdir_custom)/bin/ ; \
	cp resources/*	           $(distdir_custom)/resources/
	$(MAKE) $(AM_MAKEFLAGS) dist-hook

dist-hook:
	cd .. ; \
	cp -r bin/$(distdir)/../*   $(distdir_custom) ; \
	rm -r bin/$(distdir)/../   ; \
	cd $(distdir_custom)       ; \
	rm -f  ../KS_CS-$(VERSION).zip  ; \
	zip -r ../KS_CS-$(VERSION).zip .


