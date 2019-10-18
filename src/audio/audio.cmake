list(APPEND KITCHENSINK_INCLUDES
   ${CMAKE_CURRENT_SOURCE_DIR}/audio/html_viewer.h
   ${CMAKE_CURRENT_SOURCE_DIR}/audio/musicplayer.h
   ${CMAKE_CURRENT_SOURCE_DIR}/audio/videoplayer.h
   ${CMAKE_CURRENT_SOURCE_DIR}/audio/videowidget.h
   ${CMAKE_CURRENT_SOURCE_DIR}/audio/videosurface.h
   ${CMAKE_CURRENT_SOURCE_DIR}/audio/volumebutton.h
   ${CMAKE_CURRENT_SOURCE_DIR}/audio/web_browser.h
)

list(APPEND KITCHENSINK_SOURCES
   ${CMAKE_CURRENT_SOURCE_DIR}/audio/html_viewer.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/audio/musicplayer.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/audio/videoplayer.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/audio/videowidget.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/audio/videosurface.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/audio/volumebutton.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/audio/web_browser.cpp
)
