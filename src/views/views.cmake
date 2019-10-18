list(APPEND KITCHENSINK_INCLUDES
   ${CMAKE_CURRENT_SOURCE_DIR}/views/listview.h
   ${CMAKE_CURRENT_SOURCE_DIR}/views/tableview.h
   ${CMAKE_CURRENT_SOURCE_DIR}/views/tablewidget_view.h
   ${CMAKE_CURRENT_SOURCE_DIR}/views/treeview.h
)

list(APPEND KITCHENSINK_SOURCES
   ${CMAKE_CURRENT_SOURCE_DIR}/views/listview.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/views/tableview.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/views/tablewidget_view.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/views/treeview.cpp
)
