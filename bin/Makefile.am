include copperspice.am

# dist
distdir_custom=source_dist/dist/KitchenSink-$(VERSION)

# path to gcc retrieved from configure (windows)
gccpath=$(dir $(shell which $(word 1,$(CC))))

# list of gcc libraries (windows)  sjlj  or seh
gcclibs=libgcc_s_*-1  libstdc++-6  libwinpthread-1

# list of CopperSpice libraries
cslibs=Core Gui Multimedia Network OpenGL Phonon Script Sql Svg WebKit Xml XmlPatterns
csver=1.4

# location of includes
AM_CXXFLAGS+=-I../src -I$(CS_HOME)/include/phonon

if OSTYPE_WIN
   # disable console on window
   AM_CXXFLAGS+=-mwindows

   # location for 'make install'
   installdir=$(abs_top_builddir)/install
endif

# target app name
bin_PROGRAMS = KitchenSink

# copy required CopperSpice and gcc files for deployment
.PHONY: deploy

if OSTYPE_LINUX
deploy : all
	mkdir -p $(deploydir)
	mkdir -p $(deploydir)/phonon_backend
	mkdir -p $(deploydir)/resources

	$(LIBTOOL) --mode=install cp $(bin_PROGRAMS) $(deploydir)

	rsync -W -a $(patsubst %,$(CS_HOME)/lib/libCs%$(csver).so*,$(cslibs)) $(deploydir)

   ifeq ($(findstring Phonon,$(cslibs)),Phonon)
		rsync -W -a $(CS_HOME)/lib/phonon_gstreamer.so $(deploydir)/phonon_backend
   else
		@echo "Phonon library was not found"
   endif

	rsync -W -a $(top_srcdir)/resources/{ks_cs.ico,script.js,sampleMenu.xml} $(deploydir)/resources
endif

if OSTYPE_DARWIN
deployapp=$(deploydir)/$(bin_PROGRAMS).app/Contents

deploy : all
	mkdir -p $(deployapp)/Frameworks
	mkdir -p $(deployapp)/MacOS
	mkdir -p $(deployapp)/Resources

	$(LIBTOOL) --mode=install cp $(bin_PROGRAMS) $(deployapp)/MacOS

	rm -f $(deployapp)/Info.plist
	sed -e "s,@ICON@,ks_cs.icns,g" \
	    -e "s,@TYPEINFO@,????,g" \
	    -e "s,@EXECUTABLE@,$(bin_PROGRAMS),g" \
	    -e "s,com.yourcompany.,com.copperspice.,g" \
	$(CS_HOME)/mac/Info.plist.app > $(deployapp)/Info.plist

	rm -f $(deployapp)/PkgInfo
	echo "APPL????" > $(deployapp)/PkgInfo

	touch $(deployapp)/Resources/empty.lproj
	cp -r $(CS_HOME)/mac/qt_menu.nib $(deployapp)/Resources

	cp $(top_srcdir)/resources/ks_cs.icns $(deployapp)/Resources

	rsync -W -a $(patsubst %,$(CS_HOME)/lib/libCs%$(csver).dylib,$(cslibs)) $(deployapp)/Frameworks

# phonon	
	mkdir -p $(deployapp)/MacOS/phonon_backend
   ifeq ($(findstring Phonon,$(cslibs)),Phonon)	
		rsync -W -a $(CS_HOME)/lib/phonon_qt7.so  $(deployapp)/MacOS/phonon_backend
   else
		@echo "Phonon Backend library was not found"
   endif
	
	for libname in $(patsubst %,libCs%$(csver).dylib,$(cslibs)) ; do \
	\
	install_name_tool -change $(CS_HOME)/lib/$$libname \
	@executable_path/../Frameworks/$$libname $(deployapp)/MacOS/$(bin_PROGRAMS); \
	\
	install_name_tool -change $(CS_HOME)/lib/$$libname \
	@executable_path/../Frameworks/$$libname $(deployapp)/MacOS/phonon_backend/phonon_qt7.0.so; \
	\
	for templib in $(patsubst %,libCs%$(csver).dylib,$(cslibs)) ; do \
	install_name_tool -change $(CS_HOME)/lib/$$templib \
	@executable_path/../Frameworks/$$templib $(deployapp)/Frameworks/$$libname \
	; done \
	\
	; done
	
	hdiutil create -ov -srcfolder $(deploydir) -format UDBZ -volname $(bin_PROGRAMS) ../$(bin_PROGRAMS).dmg
	hdiutil internet-enable -yes ../$(bin_PROGRAMS).dmg

endif

if OSTYPE_WIN
deploy : all
	mkdir -p $(deploydir)
	mkdir -p $(deploydir)/phonon_backend

	$(LIBTOOL) --mode=install cp $(bin_PROGRAMS) $(deploydir)

	rsync -W -a --modify-window=2  $(top_srcdir)/resources/ks_cs.ico $(deploydir)

	rsync -W -a --modify-window=2  $(patsubst %,$(gccpath)%.dll,$(gcclibs))  $(deploydir)
	rsync -W -a --modify-window=2  $(patsubst %,$(CS_HOME)/bin/libCs%$(csver).dll,$(cslibs))  $(deploydir)

   ifeq ($(findstring Phonon,$(cslibs)),Phonon)
		rsync -W -a --modify-window=2  $(CS_HOME)/lib/phonon_ds9.dll  $(deploydir)/phonon_backend
   else
		@echo "Phonon library was not found"
   endif
endif

# search path for source
VPATH = ../

# linking
KitchenSink_LDFLAGS=$(AM_LDFLAGS) $(patsubst %,-lCs%$(csver),$(cslibs))

if OSTYPE_LINUX
   KitchenSink_LDFLAGS+=-lGL
endif

if OSTYPE_DARWIN
endif

if OSTYPE_WIN
   KitchenSink_LDFLAGS+=-lopengl32
endif

KitchenSink_SOURCES = \
   src/aboutcs.cpp \
   src/analogclock.cpp \
   src/animated_tiles.cpp \
   src/calendar.cpp \
   src/colorpicker.cpp \
   src/dialogs.cpp \
   src/draglabel.cpp  \
   src/draw.cpp \
   src/draw_area.cpp \
   src/fridgemag.cpp \
   src/fontpicker.cpp \
   src/glwidget.cpp \
   src/grabber.cpp  \
   src/html_viewer.cpp \
   src/international.cpp \
   src/lighting.cpp \
   src/line_edit.cpp \
   src/listview.cpp \
   src/main.cpp \
   src/mandelbrot_thread.cpp \
   src/mandelbrot_widget.cpp \
   src/mdi.cpp \
   src/musicplayer.cpp  \
   src/screenshot.cpp \
   src/sliders.cpp \
   src/script.cpp \
   src/stdpath.cpp \
   src/style_edit.cpp \
   src/style_dw.cpp \
   src/svg_view.cpp  \
   src/svgtextobject.cpp \
   src/systray.cpp \
   src/tableview.cpp \
   src/tablewidget_view.cpp \
   src/tabdialog.cpp \
   src/treeview.cpp \
   src/util.cpp \
   src/videosurface.cpp \
   src/videoplayer.cpp \
   src/videowidget.cpp \
   src/web_browser.cpp \
   src/xml.cpp \
   src/xmlpatterns.cpp \
   src/xmlsyntaxhighlighter.cpp

# qmlapplicationviewer.cpp
# wiggle_boxes.cpp
# world_clock.cpp

noinst_HEADERS = \
   src/aboutcs.h \
   src/calendar.h \
   src/colorpicker.h \
   src/dialogs.h \
   src/draw.h \
   src/draw_area.h \
   src/fontpicker.h \
   src/html_viewer.h  \
   src/international.h \
   src/line_edit.h \
   src/listview.h \
   src/mdi.h \
   src/musicplayer.h \
   src/script.h \
   src/stdpath.h \
   src/sliders.h \
   src/style_dw.h  \
   src/style_edit.h  \
   src/svg_view.h  \
   src/svgtextobject.h \
   src/systray.h \
   src/tabdialog.h \
   src/tableview.h \
   src/tablewidget_view.h \
   src/treeview.h \
   src/util.h \
   src/videoplayer.h \
   src/videowidget.h \
   src/videosurface.h \
   src/web_browser.h \
   src/analogclock.h  \
   src/animated_tiles.h  \
   src/draglabel.h \
   src/fridgemag.h  \
   src/glwidget.h  \
   src/grabber.h  \
   src/lighting.h  \
   src/mandelbrot_thread.h  \
   src/mandelbrot_widget.h  \
   src/screenshot.h \
   src/xml.h \
   src/xmlpatterns.h \
   src/xmlsyntaxhighlighter.h

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
install-exec-hook:
	rsync -W -a --modify-window=2  $(top_srcdir)/resources/ks_cs.ico $(bindir)

	rsync -W -a --modify-window=2  $(patsubst %,$(gccpath)%.dll,$(gcclibs))  $(bindir)
	rsync -W -a --modify-window=2  $(patsubst %,$(CS_HOME)/bin/libCs%$(csver).dll,$(cslibs))  $(bindir)

	mkdir -p $(bindir)/phonon_backend

   ifeq ($(findstring Phonon,$(cslibs)),Phonon)
		rsync -W -a --modify-window=2  $(CS_HOME)/lib/phonon_ds9.dll  $(bindir)/phonon_backend
   else
		@echo "Phonon library was not found"
   endif

endif

# distribution for 'make dist'
distdir: $(DISTFILES)
	cd .. ; \
	test -d "$(distdir_custom)" || mkdir -p "$(distdir_custom)" ; \
	mkdir -p $(distdir_custom)/bin                              ; \
	mkdir -p $(distdir_custom)/resources                        ; \
	mkdir -p $(distdir_custom)/resources_qml                    ; \
\
	for f in $(DIST_SOURCES)  ; do install -D $$f $(distdir_custom)/$$f ; done ; \
	for f in $(HEADERS)       ; do install -D $$f $(distdir_custom)/$$f ; done ; \
	for f in $(FORMS)         ; do install -D $$f $(distdir_custom)/$$f ; done ; \
\
	cp kitchensink.qrc        $(distdir_custom)/                ; \
	cp bin/*.am               $(distdir_custom)/bin/            ; \
	cp bin/Makefile.in        $(distdir_custom)/bin/            ; \
	cp -r resources/*         $(distdir_custom)/resources/      ; \
	cp -r resources_qml/*     $(distdir_custom)/resources_qml/

	$(MAKE) $(AM_MAKEFLAGS) dist-hook

# distdir is a temp folder
dist-hook:
	cd .. ; \
\
	cp -r bin/$(distdir)/../*   $(distdir_custom)  ; \
	cd $(distdir_custom)/..                        ; \
\
	rm -f    ../KitchenSink-$(VERSION).zip                  ; \
	zip -r   ../KitchenSink-$(VERSION).zip .                ; \
	rm  -f   ../KitchenSink-$(VERSION).tar.bz2              ; \
	tar -cjf ../KitchenSink-$(VERSION).tar.bz2 .
