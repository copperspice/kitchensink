AUTOMAKE_OPTIONS= 
ACLOCAL_AMFLAGS= -I autotools/m4 --install

# list of CopperSpice libraries your app uses
cslibs=Core Gui Sql Xml Network

# adjustment for windows slash vs backslash
CS_HOME:=$(shell cd $(CS_HOME); pwd)

# location of CopperSpice programs
LRELEASE=$(CS_HOME)/bin/lrelease
MOC=$(CS_HOME)/bin/moc
RCC=$(CS_HOME)/bin/rcc
UIC=$(CS_HOME)/bin/uic

# location of includes, libs, defines for compiling
AM_CXXFLAGS=$(AM_CFLAGS) -DQ_BYTE_ORDER=Q_LITTLE_ENDIAN -DQ_LITTLE_ENDIAN=1234 -DQ_BIG_ENDIAN=4321  \
    -DQT_EDITION=QT_EDITION_OPENSOURCE  -DQT_ARCH_I386  -DQT_NO_STYLE_S60 \
    $(patsubst %,-I$(CS_HOME)/include/Qt%,$(cslibs))   -I$(CS_HOME)/include 
                   
# 'deploy' is the folder where the install will be located
deploydir=$(abs_top_builddir)/deploy

# 'KitchenSink-Cs1' target app name
deploy_PROGRAMS = KitchenSink-Cs1

# copy the required CopperSpice dll files for deployment (windows)
install-exec-hook:
	install -p  $(patsubst %,$(CS_HOME)/bin/libCs%1-0.dll,$(cslibs))	$(deploydir)
	
# x11	
# install-exe-hook:	
# cp -p  $(patsubst %,$(CS_HOME)/lib/libCs%1.so,$(cslibs))   $(deploydir)

# location of CopperSpice libraries for linking
AM_LDFLAGS=-L$(CS_HOME)/lib

# linking
KitchenSink_Cs1_LDFLAGS=$(AM_LDFLAGS)   $(patsubst %,-lCs%1,$(cslibs))

# 'KitchenSink_Cs1' must match the app name ( dash had to be replaced )
KitchenSink_Cs1_SOURCES = \
    ../main.cpp \
    ../mdi.cpp \
    ../util.cpp \
    ../line_edit.cpp \
    ../calendar.cpp \
    ../draw.cpp \
    ../draw_area.cpp \
    ../sliders.cpp \
    ../style_edit.cpp \
    ../style_dw.cpp \
    ../dialogs.cpp \
    ../colorpicker.cpp \
    ../fontpicker.cpp \
    ../treeview.cpp \
    ../listview.cpp \
    ../tableview.cpp \
    ../systray.cpp \
    ../tablewidget_view.cpp \
    ../tabdialog.cpp \
    ../translate.cpp \
    ../xml.cpp
    
#              
noinst_HEADERS = \
    ../mdi.h \
    ../util.h \
    ../line_edit.h \
    ../calendar.h \
    ../draw.h \
    ../draw_area.h \
    ../sliders.h \
    ../style_edit.h \
    ../style_dw.h \
    ../dialogs.h \
    ../colorpicker.h \
    ../fontpicker.h \
    ../treeview.h \
    ../listview.h \
    ../tableview.h \
    ../systray.h \
    ../tablewidget_view.h \
    ../tabdialog.h \
    ../translate.h \
    ../xml.h    
    
# list of files that require compiling with moc
MOCS = \
    ../mdi.h \
    ../line_edit.h \
    ../calendar.h \
    ../draw.h \
    ../draw_area.h \
    ../sliders.h \
    ../style_edit.h \
    ../style_dw.h \
    ../dialogs.h \
    ../colorpicker.h \
    ../fontpicker.h \
    ../listview.h \
    ../tableview.h \
    ../systray.h \
    ../tablewidget_view.h \
    ../tabdialog.h \
    ../translate.h \
    ../xml.h
    
KitchenSink_Cs1_LDADD=$(patsubst ../%.h,moc_%.$(OBJEXT),$(MOCS))    
           
 
#
FORMS = \
    ../mdi.ui \
    ../line_edit.ui \
    ../style_dw.ui \
    ../style_edit.ui \
    ../colorpicker.ui \
    ../fontpicker.ui \
    ../dialogs.ui \
    ../listview.ui \
    ../tablewidget_view.ui \
    ../tabdialog.ui \
    ../translate.ui \
    ../xml.ui    
    
BUILT_SOURCES=$(patsubst ../%.ui,ui_%.h,$(FORMS))    
EXTRA_DIST=$(FORMS)    
      
#
RESOURCES  =  ../kitchensink.qrc

BUILT_SOURCES+=$(patsubst ../%.qrc,qrc_%.cpp,$(RESOURCES))    
EXTRA_DIST+=$(RESOURCES)    
     
KitchenSink_Cs1_SOURCES += qrc_kitchensink.cpp


#
TRANSLATIONS =  \
    ../resources/qt_en.ts   \
    ../resources/qt_de.ts   \
    ../resources/qt_fr.ts
    
BUILT_SOURCES+=$(patsubst %.ts,%.qm,$(TRANSLATIONS))    
EXTRA_DIST+=$(TRANSLATIONS)     
    
                        
# rules

%.qm: %.ts
	$(LRELEASE) $< $@ 
	
moc_%.cpp: ../%.h
	$(MOC) $< -o $@    		
    
qrc_%.cpp: ../%.qrc
	$(RCC) $< -o $@   	

ui_%.h: ../%.ui
	$(UIC) $< -o $@       	
    
# additional files to delete on 'make clean' 	
clean-local:
	-rm moc_*.cpp
	-rm qrc_*.cpp
	-rm ui_*.h
    