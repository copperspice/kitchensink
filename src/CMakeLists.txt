list(APPEND KITCHENSINK_INCLUDES
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

list(APPEND KITCHENSINK_SOURCES
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
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/camera.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/camera_imagesettings.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/camera_videosettings.ui
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
include(camera/camera.cmake)
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

   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/camera.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/camera_imagesettings.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/camera_videosettings.ui
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

target_include_directories(KitchenSink
   PRIVATE
   ${CMAKE_SOURCE_DIR}/src
   ${CMAKE_CURRENT_SOURCE_DIR}/audio
   ${CMAKE_CURRENT_SOURCE_DIR}/camera
   ${CMAKE_CURRENT_SOURCE_DIR}/graphics
   ${CMAKE_CURRENT_SOURCE_DIR}/network
   ${CMAKE_CURRENT_SOURCE_DIR}/views
   ${CMAKE_CURRENT_SOURCE_DIR}/widgets
)

target_link_libraries(KitchenSink
   CopperSpice::CsCore
   CopperSpice::CsGui
   CopperSpice::CsNetwork
   CopperSpice::CsOpenGL
   CopperSpice::CsScript
   CopperSpice::CsSql
   CopperSpice::CsSvg
   CopperSpice::CsXml
   CopperSpice::CsXmlPatterns
)

if("Multimedia" IN_LIST COPPERSPICE_COMPONENTS)
   target_link_libraries(KitchenSink CopperSpice::CsMultimedia)
endif()

# webkit temporarily removed, pending overflow issue resolution in CsWebKit

# if("WebKit" IN_LIST COPPERSPICE_COMPONENTS)
#   target_link_libraries(KitchenSink CopperSpice::CsWebKit)
# endif()

if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
   set_target_properties(KitchenSink PROPERTIES OUTPUT_NAME kitchensink)

   target_link_libraries(KitchenSink
      "-framework OpenGL"
   )

elseif(CMAKE_SYSTEM_NAME MATCHES "(Linux|OpenBSD|FreeBSD|NetBSD|DragonFly)")
   set_target_properties(KitchenSink PROPERTIES OUTPUT_NAME kitchensink)

elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
   # disable console on windows
   target_link_libraries(KitchenSink
      netapi32
      mpr
      -mwindows
   )

endif()

if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
   install(TARGETS KitchenSink DESTINATION ../MacOS)
else()
   install(TARGETS KitchenSink DESTINATION .)
endif()

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/../resources/script.js       DESTINATION ./resources)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/../resources/sampleMenu.xml  DESTINATION ./resources)

# installs the CopperSpice libraries
cs_copy_library(CsCore)
cs_copy_library(CsGui)
cs_copy_library(CsNetwork)
cs_copy_library(CsOpenGL)
cs_copy_library(CsScript)
cs_copy_library(CsSql)
cs_copy_library(CsSvg)
cs_copy_library(CsXml)
cs_copy_library(CsXmlPatterns)

if("Multimedia" IN_LIST COPPERSPICE_COMPONENTS)
   cs_copy_library(CsMultimedia)
endif()

if("WebKit" IN_LIST COPPERSPICE_COMPONENTS)
   # webkit temporarily removed, pending overflow issue resolution in CsWebKit
   # cs_copy_library(CsWebKit)
endif()

if (CMAKE_SYSTEM_NAME MATCHES "Darwin")

   set(CPACK_DMG_VOLUME_NAME KitchenSink)
   set(CPACK_DMG_FORMAT UDBZ)

   # installs the platform Gui plugin
   cs_copy_plugins(CsGui ../plugins)

   # two files
   if("Multimedia" IN_LIST COPPERSPICE_COMPONENTS)
      cs_copy_plugins(CsMultimedia ../plugins)
   endif()

   install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/../resources/ks.icns DESTINATION ./resources)

elseif(CMAKE_SYSTEM_NAME MATCHES "(Linux|OpenBSD|FreeBSD|NetBSD|DragonFly)")

   # installs the platform Gui plugin
   cs_copy_plugins(CsGui)
   cs_copy_plugins(CsOpenGL)

   # three files
   if("Multimedia" IN_LIST COPPERSPICE_COMPONENTS)
      cs_copy_plugins(CsMultimedia)
   endif()

   install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/../resources/ks.png DESTINATION ./resources)

elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")

   # installs the platform Gui plugin
   cs_copy_plugins(CsGui)

   # two files
   if("Multimedia" IN_LIST COPPERSPICE_COMPONENTS)
      cs_copy_plugins(CsMultimedia)
   endif()

   install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/../resources/ks.ico DESTINATION ./resources)

endif()
