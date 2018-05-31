cmake_minimum_required(VERSION 3.9)
project(cruthu LANGUAGES CXX)

set(CRUTHU_MAJOR_VERSION 0)
set(CRUTHU_MINOR_VERSION 1)
set(CRUTHU_PATCH_VERSION 0)
set(CRUTHU_TWEAK_VERSION 0)
set(CRUTHU_VERSION
    ${CRUTHU_MAJOR_VERSION}.${CRUTHU_MINOR_VERSION}.${CRUTHU_PATCH_VERSION}.${CRUTHU_TWEAK_VERSION}
)

set(CMAKE_CXX_STANDARD 11)

if(WIN32 AND NOT CYGWIN)
    set(DEF_INSTALL_CMAKE_DIR CMake)
else()
    set(DEF_INSTALL_CMAKE_DIR lib/CMake/Cruthu)
endif()

set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")

# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
    set(var INSTALL_${p}_DIR)
    if(NOT IS_ABSOLUTE ${${var}})
        set(${var} ${CMAKE_INSTALL_PREFIX}/${${var}})
    endif()
endforeach()

# Set up include-directories
include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

add_subdirectory(cruthu)
add_subdirectory(cruthu-cli)
add_subdirectory(cruthu-gl)

export(TARGETS cruthu cruthu-gl cruthu-cli FILE ${PROJECT_BINARY_DIR}/CruthuTargets.cmake)
export(PACKAGE Cruthu)

file(RELATIVE_PATH REL_INCLUDE_DIR ${INSTALL_CMAKE_DIR} ${INSTALL_INCLUDE_DIR})

set(CONF_INCLUDE_DIRS ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR})
configure_file(CruthuConfig.cmake.in
    ${PROJECT_BINARY_DIR}/CruthuConfig.cmake @ONLY
)

set(CONF_INCLUDE_DIRS ${CRUTHU_CMAKE_DIR}/${REL_INCLUDE_DIR})
configure_file(CruthuConfig.cmake.in
    ${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CruthuConfig.cmake @ONLY
)

configure_file(CruthuConfigVersion.cmake.in
    ${PROJECT_BINARY_DIR}/CruthuConfigVersion.cmake @ONLY
)

install(FILES
    ${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CruthuConfig.cmake
    ${PROJECT_BINARY_DIR}/CruthuConfigVersion.cmake
    DESTINATION ${INSTALL_CMAKE_DIR} COMPONENT dev
)

install(EXPORT CruthuTargets DESTINATION
    ${INSTALL_CMAKE_DIR} COMPONENT dev
)
