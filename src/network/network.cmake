list(APPEND KITCHENSINK_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/network/chat_dialog.h
    ${CMAKE_CURRENT_SOURCE_DIR}/network/client.h
    ${CMAKE_CURRENT_SOURCE_DIR}/network/connection.h
    ${CMAKE_CURRENT_SOURCE_DIR}/network/peermanager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/network/server.h
    ${CMAKE_CURRENT_SOURCE_DIR}/network/ssl_cert.h
    ${CMAKE_CURRENT_SOURCE_DIR}/network/ssl_client.h
)

list(APPEND KITCHENSINK_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/network/chat_dialog.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/network/client.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/network/connection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/network/peermanager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/network/server.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/network/ssl_cert.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/network/ssl_client.cpp
)
