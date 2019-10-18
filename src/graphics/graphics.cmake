list(APPEND KITCHENSINK_INCLUDES
   ${CMAKE_CURRENT_SOURCE_DIR}/graphics/analogclock.h
   ${CMAKE_CURRENT_SOURCE_DIR}/graphics/animated_tiles.h
   ${CMAKE_CURRENT_SOURCE_DIR}/graphics/draglabel.h
   ${CMAKE_CURRENT_SOURCE_DIR}/graphics/fridgemag.h
   ${CMAKE_CURRENT_SOURCE_DIR}/graphics/glwidget.h
   ${CMAKE_CURRENT_SOURCE_DIR}/graphics/grabber.h
   ${CMAKE_CURRENT_SOURCE_DIR}/graphics/lighting.h
   ${CMAKE_CURRENT_SOURCE_DIR}/graphics/mandelbrot_thread.h
   ${CMAKE_CURRENT_SOURCE_DIR}/graphics/mandelbrot_widget.h
   ${CMAKE_CURRENT_SOURCE_DIR}/graphics/screenshot.h
)

list(APPEND KITCHENSINK_SOURCES
   ${CMAKE_CURRENT_SOURCE_DIR}/graphics/analogclock.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/graphics/animated_tiles.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/graphics/draglabel.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/graphics/fridgemag.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/graphics/glwidget.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/graphics/grabber.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/graphics/lighting.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/graphics/mandelbrot_thread.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/graphics/mandelbrot_widget.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/graphics/screenshot.cpp
)
