list(APPEND KITCHENSINK_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets/calendar.h
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets/line_edit.h
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets/sliders.h
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets/tabdialog.h
)

list(APPEND KITCHENSINK_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets/calendar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets/line_edit.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets/sliders.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets/tabdialog.cpp
)
