cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

cmake_policy(VERSION 3.8..3.13)

# support using rpath on Mac OS X
cmake_policy(SET CMP0042 NEW)

project(KitchenSink)

set(BUILD_MAJOR "1")
set(BUILD_MINOR "7")
set(BUILD_MICRO "1")

set(BUILD_COMPONENTS "KitchenSink")

include(CheckCXXCompilerFlag)
include(CheckCXXSourceCompiles)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckTypeSize)

find_package(CopperSpice REQUIRED)

# file locations for installing
if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
   include(GNUInstallDirs)

   # indicates where libraries are located relative to the executable
   set(CMAKE_INSTALL_RPATH "@executable_path/../Resources")

elseif(CMAKE_SYSTEM_NAME MATCHES "(Linux|OpenBSD|FreeBSD|NetBSD|DragonFly)")
   # binaries are in bin, libraries are in lib or lib64
   include(GNUInstallDirs)

   # application should look for libraries in the current directory
   set(CMAKE_INSTALL_RPATH "\$ORIGIN")

elseif(MSVC)
   # use defaults

elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
   set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION .)
   include(${CopperSpice_DIR}/InstallMinGW.cmake)

endif()

set(PACKAGE           "kitchensink")
set(PACKAGE_NAME      "KitchenSink")
set(PACKAGE_VERSION   "${BUILD_MAJOR}.${BUILD_MINOR}.${BUILD_MICRO}")
set(PACKAGE_STRING    "KitchenSink ${BUILD_MAJOR}.${BUILD_MINOR}.${BUILD_MICRO}")
set(PACKAGE_TARNAME   "kitchensink")
set(PACKAGE_BUGREPORT "info@copperspice.com")
set(PACKAGE_URL       "https://www.copperspice.com/")

set(CPACK_PACKAGE_NAME    ${PROJECT_NAME} )
set(CPACK_PACKAGE_VENDOR  "CopperSpice")

set(CPACK_PACKAGE_VERSION_MAJOR ${BUILD_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${BUILD_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${BUILD_MICRO})

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "GUI application containing multiple examples using the CopperSpice libraries")
set(CPACK_PACKAGE_DESCRIPTION_FILE    "${CMAKE_SOURCE_DIR}/README.md")

set(CPACK_PACKAGE_INSTALL_DIRECTORY   ${CMAKE_INSTALL_PREFIX})
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY  OFF)

set(CPACK_BUNDLE_NAME  KitchenSink)
set(CPACK_BUNDLE_ICON  "${CMAKE_SOURCE_DIR}/resources/ks.icns")
set(CPACK_BUNDLE_PLIST "${CMAKE_SOURCE_DIR}/resources/Info.plist")

include(CPack)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_DIRECTORIES_BEFORE ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

if("Multimedia" IN_LIST COPPERSPICE_COMPONENTS)
  # multimedia found and will be linked with this project
else()
  add_definitions(-DQT_NO_MULTIMEDIA)
endif()


# webkit temporarily removed, pending overflow issue resolution in CsWebKit
add_definitions(-DQT_NO_WEBKIT)

# if("WebKit" IN_LIST COPPERSPICE_COMPONENTS)
#   # webkit found and will be linked with this project
# else()
#   add_definitions(-DQT_NO_WEBKIT)
# endif()


if(APPLE)
    set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS}    -Wl,-undefined,error")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-undefined,error")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,-undefined,error")
else()
    set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS}    -Wl,--no-undefined")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,--no-undefined")
endif()

string(TIMESTAMP BUILD_DATE "%m/%d/%Y")
add_definitions(-DBUILD_DATE="${BUILD_DATE}")

configure_file(
   ${CMAKE_SOURCE_DIR}/src/ks_build_info.h.in
   src/ks_build_info.h
)

# location for building binary files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)

if(${CMAKE_SIZEOF_VOID_P} EQUAL 4)
   set(TARGETBITS 32)
else()
   set(TARGETBITS 64)
endif()

message("")
message("KitchenSink configured to run on:  ${CMAKE_SYSTEM_NAME} ${TARGETBITS} bit, ${CMAKE_BUILD_TYPE} Mode")
message("KitchenSink will be built in:      ${CMAKE_BINARY_DIR}")
message("KitchenSink will be installed in:  ${CMAKE_INSTALL_PREFIX}")
message("\n")
