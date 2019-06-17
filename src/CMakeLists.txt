set(CS_VERSION 1.5)

macro(cs_copy_dll APP DLL)
   get_target_property(CS_${DLL}_LIB  CopperSpice::Cs${DLL}${CS_VERSION} LOCATION)
   install(FILES  ${CS_${DLL}_LIB}  DESTINATION .)
endmacro()

# only called for windows
macro(cs_copy_plugins name)

if (name strequal "Gui")
   get_target_property(GUI_PLATFORM_LIB  CopperSpice::CsGuiWin${CS_VERSION} LOCATION)
   install(FILES  ${GUI_PLATFORM_LIB}  DESTINATION ./platforms)
endif()

if (name strequal "Multimedia")
   get_target_property(DIRECTSHOW_LIB  CopperSpice::CsMultimedia_DirectShow${CS_VERSION} LOCATION)
   install(FILES  ${DIRECTSHOW_LIB}  DESTINATION ./mediaservices)

   get_target_property(MU3_LIB  CopperSpice::CsMultimedia_m3u${CS_VERSION} LOCATION)
   install(FILES  ${MU3_LIB}  DESTINATION ./playlistformats)
endif()

endmacro()

check_include_file(windows.h HAVE_WINDOWS_H)

if (HAVE_WINDOWS_H)
   add_definitions(-DHAVE_WINDOWS_H)
endif()

set(KITCHENSINK_INCLUDES
   ${CMAKE_CURRENT_SOURCE_DIR}/aboutcs.h
   ${CMAKE_CURRENT_SOURCE_DIR}/colorpicker.h
   ${CMAKE_CURRENT_SOURCE_DIR}/dialogs.h
   ${CMAKE_CURRENT_SOURCE_DIR}/draw.h
   ${CMAKE_CURRENT_SOURCE_DIR}/draw_area.h
   ${CMAKE_CURRENT_SOURCE_DIR}/fontpicker.h
   ${CMAKE_CURRENT_SOURCE_DIR}/international.h
   ${CMAKE_CURRENT_SOURCE_DIR}/ks_build_info.h
   ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.h
   ${CMAKE_CURRENT_SOURCE_DIR}/script.h
   ${CMAKE_CURRENT_SOURCE_DIR}/stdpath.h
   ${CMAKE_CURRENT_SOURCE_DIR}/style_dw.h
   ${CMAKE_CURRENT_SOURCE_DIR}/style_edit.h
   ${CMAKE_CURRENT_SOURCE_DIR}/svg_view.h
   ${CMAKE_CURRENT_SOURCE_DIR}/svgtextobject.h
   ${CMAKE_CURRENT_SOURCE_DIR}/systray.h
   ${CMAKE_CURRENT_SOURCE_DIR}/util.h
   ${CMAKE_CURRENT_SOURCE_DIR}/xml.h
   ${CMAKE_CURRENT_SOURCE_DIR}/xmlpatterns.h
   ${CMAKE_CURRENT_SOURCE_DIR}/xmlsyntaxhighlighter.h
)

set(KITCHENSINK_SOURCES
   ${CMAKE_CURRENT_SOURCE_DIR}/aboutcs.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/colorpicker.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/dialogs.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/draw.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/draw_area.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/fontpicker.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/international.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include_test.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/script.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/stdpath.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/style_dw.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/style_edit.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/svg_view.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/svgtextobject.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/systray.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/util.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/xml.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/xmlpatterns.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/xmlsyntaxhighlighter.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/mainwindow.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/chat_dialog.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/colorpicker.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/fontpicker.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/dialogs.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/html_viewer.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/international.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/line_edit.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/listview.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/musicplayer.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/ssl_cert.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/ssl_client.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/ssl_error.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/stdpath.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/style_dw.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/style_edit.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/script.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/tabdialog.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/tablewidget_view.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/xml.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/xmlpatterns.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../resources/qt_en.ts
   ${CMAKE_CURRENT_SOURCE_DIR}/../resources/qt_de.ts
   ${CMAKE_CURRENT_SOURCE_DIR}/../resources/qt_fr.ts
   qrc_kitchensink.cpp
)

include(audio/audio.cmake)
include(graphics/graphics.cmake)
include(network/network.cmake)
include(views/views.cmake)
include(widgets/widgets.cmake)

# run lrelease to generate translation files
COPPERSPICE_RESOURCES(
   ${CMAKE_CURRENT_SOURCE_DIR}/../resources/qt_en.ts
   ${CMAKE_CURRENT_SOURCE_DIR}/../resources/qt_de.ts
   ${CMAKE_CURRENT_SOURCE_DIR}/../resources/qt_fr.ts
)

# run rcc to generate qrc output
COPPERSPICE_RESOURCES(
   ${CMAKE_CURRENT_SOURCE_DIR}/../kitchensink.qrc
)

# run uic to generate source
COPPERSPICE_RESOURCES(
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/mainwindow.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/chat_dialog.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/colorpicker.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/fontpicker.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/dialogs.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/html_viewer.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/international.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/line_edit.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/listview.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/musicplayer.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/ssl_cert.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/ssl_client.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/ssl_error.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/stdpath.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/style_dw.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/style_edit.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/script.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/tabdialog.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/tablewidget_view.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/xml.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/xmlpatterns.ui
)

add_executable(KitchenSink ${KITCHENSINK_SOURCES} )

# location of includes
target_include_directories(KitchenSink
   PRIVATE
   ${CMAKE_SOURCE_DIR}/src
   ${CMAKE_CURRENT_SOURCE_DIR}/audio
   ${CMAKE_CURRENT_SOURCE_DIR}/graphics
   ${CMAKE_CURRENT_SOURCE_DIR}/network
   ${CMAKE_CURRENT_SOURCE_DIR}/views
   ${CMAKE_CURRENT_SOURCE_DIR}/widgets
)

target_link_libraries(KitchenSink
   CopperSpice::CsCore${CS_VERSION}
   CopperSpice::CsGui${CS_VERSION}
   CopperSpice::CsNetwork${CS_VERSION}
   CopperSpice::CsOpenGL${CS_VERSION}
   CopperSpice::CsScript${CS_VERSION}
   CopperSpice::CsSql${CS_VERSION}
   CopperSpice::CsSvg${CS_VERSION}
   CopperSpice::CsXml${CS_VERSION}
   CopperSpice::CsXmlPatterns${CS_VERSION}
)

if("Multimedia" IN_LIST COPPERSPICE_COMPONENTS)
   target_link_libraries(KitchenSink CopperSpice::CsMultimedia${CS_VERSION}
)
endif()

if("WebKit" IN_LIST COPPERSPICE_COMPONENTS)
   target_link_libraries(KitchenSink CopperSpice::CsWebKit${CS_VERSION}
)
endif()

if(WIN32)
   # disable console on windows
   target_link_libraries(KitchenSink -lnetapi32 -lmpr -mwindows)
endif()

install(TARGETS KitchenSink DESTINATION .)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/../resources/ks.ico  DESTINATION ./resources)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/../resources/script.js  DESTINATION ./resources)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/../resources/sampleMenu.xml  DESTINATION ./resources)

if(WIN32)
   cs_copy_dll(KitchenSink Core)
   cs_copy_dll(KitchenSink Gui)
   cs_copy_dll(KitchenSink Network)
   cs_copy_dll(KitchenSink OpenGL)
   cs_copy_dll(KitchenSink Script)
   cs_copy_dll(KitchenSink Sql)
   cs_copy_dll(KitchenSink Svg)
   cs_copy_dll(KitchenSink Xml)
   cs_copy_dll(KitchenSink XmlPatterns)

   cs_copy_plugins("Gui")

if("Multimedia" IN_LIST COPPERSPICE_COMPONENTS)
   cs_copy_dll(KitchenSink Multimedia)
   cs_copy_plugins("Multimedia")
endif()

if("WebKit" IN_LIST COPPERSPICE_COMPONENTS)
   cs_copy_dll(KitchenSink WebKit)
endif()

endif()

