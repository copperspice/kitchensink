include copperspice.am

# dist (windows)
distdir_custom=install_win/dist

# path to gcc (windows)
gccpath=/c/MingW/bin

# list of gcc libraries (windows)
gcclibs=libgcc_s_sjlj-1  libstdc++-6  libwinpthread-1

# list of CopperSpice libraries
cslibs=Core Gui Multimedia Network OpenGL Phonon Script Sql Svg WebKit Xml XmlPatterns
# Declarative  (on hold)

# location of includes, defines
AM_CXXFLAGS+=-I$(CS_HOME)/include/phonon

if OSTYPE_WIN
   # disable console on window
   AM_CXXFLAGS+=-mwindows

   # 'instal' is the folder for "make install"
   installdir=$(abs_top_builddir)/install
endif

# target app name
bin_PROGRAMS = KitchenSink

# copy required CopperSpice and gcc files for deployment
.PHONY: deploy

if OSTYPE_LINUX
deploy: $(bin_PROGRAMS)
	mkdir -p $(deploydir)
	mkdir -p $(deploydir)/phonon_backend
	mkdir -p $(deploydir)/resources

	$(LIBTOOL) --mode=install cp $(bin_PROGRAMS) $(deploydir)

	rsync -W -a $(patsubst %,$(CS_HOME)/lib/libCs%1-0.so*,$(cslibs)) $(deploydir)
	rsync -W -a $(top_srcdir)/resources/{ks_cs.ico, script.js, sampleMenu.xml} $(deploydir)/resources
endif

if OSTYPE_DARWIN
deployapp=$(deploydir)/$(bin_PROGRAMS).app/Contents

deploy: $(bin_PROGRAMS)
	mkdir -p $(deployapp)/Frameworks
	mkdir -p $(deployapp)/MacOS
	mkdir -p $(deployapp)/Resources

	$(LIBTOOL) --mode=install cp $(bin_PROGRAMS) $(deployapp)/MacOS

	rm -f $(deployapp)/Info.plist
	sed -e "s,@ICON@,,g" \
	    -e "s,@TYPEINFO@,????,g" \
	    -e "s,@EXECUTABLE@,$(bin_PROGRAMS),g" \
	$(CS_HOME)/mac/Info.plist.app > $(deployapp)/Info.plist
	
	rm -f $(deployapp)/PkgInfo
	echo "APPL????" > $(deployapp)/PkgInfo
	
	touch $(deployapp)/Resources/empty.lproj
	cp -r $(CS_HOME)/mac/qt_menu.nib $(deployapp)/Resources
	
	rsync -W -a $(patsubst %,$(CS_HOME)/lib/libCs%1.0.dylib,$(cslibs)) $(deployapp)/Frameworks

# phonon	
	mkdir -p $(deployapp)/MacOS/phonon_backend
   ifeq ($(findstring Phonon,$(cslibs)),Phonon)	
		rsync -W -a $(CS_HOME)/lib/phonon_qt7.0.so  $(deployapp)/MacOS/phonon_backend
   else		
		@echo "Phonon Backend library was not found"
   endif
	
	for libname in $(patsubst %,libCs%1.0.dylib,$(cslibs)) ; do \
	\
	install_name_tool -change $(CS_HOME)/lib/$$libname \
	@executable_path/../Frameworks/$$libname $(deployapp)/MacOS/$(bin_PROGRAMS); \
	\
	for templib in $(patsubst %,libCs%1.0.dylib,$(cslibs)) ; do \
	install_name_tool -change $(CS_HOME)/lib/$$templib \
	@executable_path/../Frameworks/$$templib $(deployapp)/Frameworks/$$libname \
	; done \
	\
	; done
	
	hdiutil create -ov -srcfolder $(deploydir) -format UDBZ -volname $(bin_PROGRAMS) ../$(bin_PROGRAMS).dmg
	hdiutil internet-enable -yes ../$(bin_PROGRAMS).dmg

endif

if OSTYPE_WIN
deploy: $(bin_PROGRAMS)
	mkdir -p $(deploydir)
	mkdir -p $(deploydir)/phonon_backend

	$(LIBTOOL) --mode=install cp $(bin_PROGRAMS) $(deploydir)

	rsync -W -a --modify-window=2  $(patsubst %,$(gccpath)/%.dll,$(gcclibs))  $(deploydir)
	rsync -W -a --modify-window=2  $(patsubst %,$(CS_HOME)/bin/libCs%1-0.dll,$(cslibs))  $(deploydir)

   ifeq ($(findstring Phonon,$(cslibs)),Phonon)
		rsync -W -a --modify-window=2  $(CS_HOME)/lib/phonon_ds9-0.dll  $(deploydir)/phonon_backend
   else
		@echo "Phonon library was not found"
   endif
endif

# search path for source
VPATH = ../

# linking
KitchenSink_LDFLAGS=$(AM_LDFLAGS) $(patsubst %,-lCs%1,$(cslibs))

if OSTYPE_LINUX
   KitchenSink_LDFLAGS+=-lGL
endif

if OSTYPE_DARWIN
endif

if OSTYPE_WIN
   KitchenSink_LDFLAGS+=-lopengl32
endif

KitchenSink_SOURCES = \
   aboutcs.cpp \
   analogclock.cpp \
   animated_tiles.cpp \
   calendar.cpp \
   colorpicker.cpp \
   dialogs.cpp \
   draglabel.cpp  \
   draw.cpp \
   draw_area.cpp \
   fridgemag.cpp \
   fontpicker.cpp \
   glwidget.cpp \
   grabber.cpp  \
   html_viewer.cpp \
   international.cpp \
   lighting.cpp \
   line_edit.cpp \
   listview.cpp \
   main.cpp \
   mandelbrot_thread.cpp \
   mandelbrot_widget.cpp \
   mdi.cpp \
   musicplayer.cpp  \
   screenshot.cpp \
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
   videosurface.cpp \
   videoplayer.cpp \
   videowidget.cpp \
   web_browser.cpp \
   xml.cpp \
   xmlpatterns.cpp \
   xmlsyntaxhighlighter.cpp

# qmlapplicationviewer.cpp
# wiggle_boxes.cpp
# world_clock.cpp

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
   analogclock.h  \
   animated_tiles.h  \
   draglabel.h \
   fridgemag.h  \
   glwidget.h  \
   grabber.h  \
   lighting.h  \
   mandelbrot_thread.h  \
   mandelbrot_widget.h  \
   screenshot.h \
   xml.h \
   xmlpatterns.h \
   xmlsyntaxhighlighter.h

# qmlapplicationviewer.h
# wiggle_boxes.h
# world_clock.h

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
    forms/xml.ui  \
    forms/xmlpatterns.ui

TRANSLATIONS =  \
    resources/qt_en.ts \
    resources/qt_de.ts \
    resources/qt_fr.ts

RESOURCES = kitchensink.qrc

# use wilcard to obtain just the dependency list
qrc_kitchensink.cpp: kitchensink.qrc   $(wildcard ../resources/*)

# required to compile qrc
nodist_KitchenSink_SOURCES=qrc_kitchensink.cpp

# install
if OSTYPE_LINUX
endif

if OSTYPE_DARWIN
endif

if OSTYPE_WIN
endif

# distribution
distdir: $(DISTFILES)
	cd .. ; \
	test -d "$(distdir_custom)" || mkdir -p "$(distdir_custom)" ;  \
	for f in $(DIST_SOURCES)  ; do install -D $$f $(distdir_custom)/$$f ; done ;  \
	for f in $(HEADERS)       ; do install -D $$f $(distdir_custom)/$$f ; done ;  \
	for f in $(FORMS)         ; do install -D $$f $(distdir_custom)/$$f ; done ;  \
	mkdir -p $(distdir_custom)/bin           ;          \
	mkdir -p $(distdir_custom)/resources     ;          \
	cp kitchensink.qrc        $(distdir_custom)/     ;  \
	cp install_files/cs.conf  $(distdir_custom)/     ;  \
	cp bin/*.am               $(distdir_custom)/bin/ ;  \
	cp resources/*            $(distdir_custom)/resources/
	$(MAKE) $(AM_MAKEFLAGS) dist-hook

dist-hook:
	cd .. ; \
	cp -r bin/$(distdir)/../*   $(distdir_custom) ;  \
	rm -r bin/$(distdir)/../   ;      \
	cd $(distdir_custom)       ;      \
	rm -f  ../KS_CS-$(VERSION).zip  ; \
	zip -r ../KS_CS-$(VERSION).zip .
