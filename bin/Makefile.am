include copperspice.am

# dist
distdir_custom=source_dist/dist/KitchenSink-$(VERSION)

# path to gcc retrieved from configure (windows)
gccpath=$(dir $(shell which $(word 1,$(CC))))

# list of gcc libraries (windows)  sjlj  or seh
gcclibs=libgcc_s_*-1  libstdc++-6  libwinpthread-1

# list of CopperSpice libraries
cslibs=Core Gui Multimedia Network OpenGL Script Sql Svg WebKit Xml XmlPatterns
csver=1.4

if HAVE_PHONON
   cslibs += Phonon
endif

# location of includes
AM_CXXFLAGS+=-I../src -I../src/audio -I../src/graphics -I../src/network -I../src/views \
             -I../src/widgets -I$(CS_HOME)/include/phonon

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

	rsync -W -a $(top_srcdir)/resources/{ks.ico,script.js,sampleMenu.xml} $(deploydir)/resources
endif

if OSTYPE_BSD
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

	rsync -W -a $(top_srcdir)/resources/{ks.ico,script.js,sampleMenu.xml} $(deploydir)/resources
endif

if OSTYPE_DARWIN
deployapp=$(deploydir)/$(bin_PROGRAMS).app/Contents

deploy : all
	mkdir -p $(deployapp)/Frameworks
	mkdir -p $(deployapp)/MacOS
	mkdir -p $(deployapp)/Resources

	$(LIBTOOL) --mode=install cp $(bin_PROGRAMS) $(deployapp)/MacOS

	rm -f $(deployapp)/Info.plist
	sed -e "s,@ICON@,ks.icns,g" \
	    -e "s,@TYPEINFO@,????,g" \
	    -e "s,@EXECUTABLE@,$(bin_PROGRAMS),g" \
	    -e "s,com.yourcompany.,com.copperspice.,g" \
	$(CS_HOME)/mac/Info.plist.app > $(deployapp)/Info.plist

	rm -f $(deployapp)/PkgInfo
	echo "APPL????" > $(deployapp)/PkgInfo

	touch $(deployapp)/Resources/empty.lproj
	cp -r $(CS_HOME)/mac/qt_menu.nib $(deployapp)/Resources

	cp $(top_srcdir)/resources/ks.icns $(deployapp)/Resources
	rsync -W -a $(top_srcdir)/resources/{ks.ico,script.js,sampleMenu.xml} $(deployapp)/Resources

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
	mkdir -p $(deploydir)/resources

	$(LIBTOOL) --mode=install cp $(bin_PROGRAMS) $(deploydir)

	rsync -W -a --modify-window=2  $(patsubst %,$(gccpath)%.dll,$(gcclibs))  $(deploydir)
	rsync -W -a --modify-window=2  $(patsubst %,$(CS_HOME)/bin/libCs%$(csver).dll,$(cslibs))  $(deploydir)

   ifeq ($(findstring Phonon,$(cslibs)),Phonon)
		rsync -W -a --modify-window=2  $(CS_HOME)/lib/phonon_ds9.dll  $(deploydir)/phonon_backend
   else
		@echo "Phonon library was not found"
   endif

	rsync -W -a $(top_srcdir)/resources/{ks.ico,script.js,sampleMenu.xml} $(deploydir)/resources
endif

# search path for source
VPATH = ../

# linking
KitchenSink_LDFLAGS=$(AM_LDFLAGS) $(patsubst %,-lCs%$(csver),$(cslibs)) ${SSL_LIBS}

if OSTYPE_LINUX
   KitchenSink_LDFLAGS+=-lGL
endif

if OSTYPE_DARWIN
endif

if OSTYPE_WIN
   KitchenSink_LDFLAGS+=-lopengl32
endif

KitchenSink_Audio_C = \
   src/audio/html_viewer.cpp \
   src/audio/musicplayer.cpp  \
   src/audio/videosurface.cpp \
   src/audio/videoplayer.cpp \
   src/audio/videowidget.cpp \
   src/audio/web_browser.cpp

KitchenSink_Network_C = \
   src/network/chat_dialog.cpp \
   src/network/client.cpp  \
   src/network/connection.cpp \
   src/network/peermanager.cpp  \
   src/network/server.cpp  \
   src/network/ssl_cert.cpp  \
   src/network/ssl_client.cpp

KitchenSink_Views_C = \
   src/views/listview.cpp \
   src/views/tableview.cpp \
   src/views/tablewidget_view.cpp \
   src/views/treeview.cpp

KitchenSink_Widgets_C = \
   src/widgets/calendar.cpp \
   src/widgets/line_edit.cpp \
   src/widgets/sliders.cpp \
   src/widgets/tabdialog.cpp

KitchenSink_Graphics_C = \
   src/graphics/analogclock.cpp \
   src/graphics/animated_tiles.cpp \
   src/graphics/draglabel.cpp  \
   src/graphics/fridgemag.cpp \
   src/graphics/glwidget.cpp \
   src/graphics/grabber.cpp  \
   src/graphics/lighting.cpp \
   src/graphics/mandelbrot_thread.cpp \
   src/graphics/mandelbrot_widget.cpp \
   src/graphics/screenshot.cpp

# qmlapplicationviewer.cpp
# wiggle_boxes.cpp
# world_clock.cpp


KitchenSink_SOURCES = \
   src/aboutcs.cpp \
   src/colorpicker.cpp \
   src/dialogs.cpp \
   src/draw.cpp \
   src/draw_area.cpp \
   src/fontpicker.cpp \
   src/international.cpp \
   src/include_test.cpp \
   src/main.cpp \
   src/mainwindow.cpp \
   src/script.cpp \
   src/stdpath.cpp \
   src/style_edit.cpp \
   src/style_dw.cpp \
   src/svg_view.cpp  \
   src/svgtextobject.cpp \
   src/systray.cpp \
   src/util.cpp \
   src/xml.cpp \
   src/xmlpatterns.cpp \
   src/xmlsyntaxhighlighter.cpp \
   \
   ${KitchenSink_Audio_C}     \
   ${KitchenSink_Network_C}   \
   ${KitchenSink_Views_C}     \
   ${KitchenSink_Widgets_C}   \
   ${KitchenSink_Graphics_C}

KitchenSink_Audio_H = \
   src/audio/html_viewer.h  \
   src/audio/musicplayer.h \
   src/audio/videoplayer.h \
   src/audio/videowidget.h \
   src/audio/videosurface.h \
   src/audio/web_browser.h

KitchenSink_Network_H = \
   src/network/chat_dialog.h \
   src/network/client.h  \
   src/network/connection.h \
   src/network/peermanager.h  \
   src/network/server.h  \
   src/network/ssl_cert.h \
   src/network/ssl_client.h

KitchenSink_Views_H = \
   src/views/listview.h \
   src/views/tableview.h \
   src/views/tablewidget_view.h \
   src/views/treeview.h

KitchenSink_Widgets_H = \
   src/widgets/calendar.h \
   src/widgets/line_edit.h \
   src/widgets/sliders.h \
   src/widgets/tabdialog.h

KitchenSink_Graphics_H = \
   src/graphics/analogclock.h  \
   src/graphics/animated_tiles.h  \
   src/graphics/draglabel.h \
   src/graphics/fridgemag.h  \
   src/graphics/glwidget.h  \
   src/graphics/grabber.h  \
   src/graphics/lighting.h  \
   src/graphics/mandelbrot_thread.h  \
   src/graphics/mandelbrot_widget.h  \
   src/graphics/screenshot.h

# qmlapplicationviewer.h
# wiggle_boxes.h
# world_clock.h


noinst_HEADERS = \
   src/aboutcs.h \
   src/colorpicker.h \
   src/dialogs.h \
   src/draw.h \
   src/draw_area.h \
   src/fontpicker.h \
   src/international.h \
   src/ks_build_info.h \
   src/mainwindow.h \
   src/script.h \
   src/stdpath.h \
   src/style_dw.h  \
   src/style_edit.h  \
   src/svg_view.h  \
   src/svgtextobject.h \
   src/systray.h \
   src/util.h \
   src/xml.h \
   src/xmlpatterns.h \
   src/xmlsyntaxhighlighter.h \
   \
   ${KitchenSink_Audio_H}    \
   ${KitchenSink_Network_H}  \
   ${KitchenSink_Views_H}    \
   ${KitchenSink_Widgets_H}  \
   ${KitchenSink_Graphics_H}

FORMS = \
    forms/mainwindow.ui  \
    forms/chat_dialog.ui  \
    forms/colorpicker.ui \
    forms/fontpicker.ui  \
    forms/dialogs.ui \
    forms/html_viewer.ui \
    forms/international.ui \
    forms/line_edit.ui \
    forms/listview.ui \
    forms/musicplayer.ui \
    forms/ssl_cert.ui \
    forms/ssl_client.ui \
    forms/ssl_error.ui \
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
	rsync -W -a --modify-window=2  $(top_srcdir)/resources/ks.ico $(bindir)

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
