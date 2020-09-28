list(APPEND KITCHENSINK_INCLUDES
   ${CMAKE_CURRENT_SOURCE_DIR}/camera/camera.h
   ${CMAKE_CURRENT_SOURCE_DIR}/camera/imagesettings.h
   ${CMAKE_CURRENT_SOURCE_DIR}/camera/videosettings.h
)

list(APPEND KITCHENSINK_SOURCES
   ${CMAKE_CURRENT_SOURCE_DIR}/camera/camera.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/camera/imagesettings.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/camera/videosettings.cpp

)
