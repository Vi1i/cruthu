cmake_minimum_required(VERSION 3.9)
project(CruthuCore)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CRUTHUCORE_MAJOR_VERSION 0)
set(CRUTHUCORE_MINOR_VERSION 1)
set(CRUTHUCORE_PATCH_VERSION 0)
set(CRUTHUCORE_VERSION
    ${CRUTHUCORE_MAJOR_VERSION}.${CRUTHUCORE_MINOR_VERSION}.${CRUTHUCORE_PATCH_VERSION})

set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")

if(WIN32 AND NOT CYGWIN)
    set(DEF_INSTALL_CMAKE_DIR CMake)
else()
    set(DEF_INSTALL_CMAKE_DIR lib/CMake/CruthuCore)
endif()

set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")

# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
    set(var INSTALL_${p}_DIR)
    if(NOT IS_ABSOLUTE "${${var}}")
        set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
    endif()
endforeach()

# set up include-directories
include_directories(
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_BINARY_DIR}")

# Add sub-directories
add_subdirectory(modules/core)
add_subdirectory(modules/tera)
add_subdirectory(modules/teragen)
add_subdirectory(modules/indexer)
add_subdirectory(modules/indexermountains)
add_subdirectory(modules/formamountains)
add_subdirectory(modules/formarivers)
add_subdirectory(modules/formaperlin)
add_subdirectory(modules/cli)

# The interesting stuff goes here
# ===============================

# Add all targets to the build-tree export set
export(TARGETS CruthuCore CruthuCoreTera CruthuCoreIndexer CruthuCoreFormaPerlin
    FILE "${PROJECT_BINARY_DIR}/CruthuCoreTargets.cmake")

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE CruthuCore)

# Create the CruthuCoreConfig.cmake and CruthuCoreConfigVersion files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
    "${INSTALL_INCLUDE_DIR}")
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(CruthuCoreConfig.cmake.in
    "${PROJECT_BINARY_DIR}/CruthuCoreConfig.cmake" @ONLY)
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${CRUTHUCORE_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(CruthuCoreConfig.cmake.in
    "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CruthuCoreConfig.cmake" @ONLY)
# ... for both
configure_file(CruthuCoreConfigVersion.cmake.in
    "${PROJECT_BINARY_DIR}/CruthuCoreConfigVersion.cmake" @ONLY)

# Install the CruthuCoreConfig.cmake and CruthuCoreConfigVersion.cmake
install(FILES
    "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CruthuCoreConfig.cmake"
    "${PROJECT_BINARY_DIR}/CruthuCoreConfigVersion.cmake"
    DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

# Install the export set for use with the install-tree
install(EXPORT CruthuCoreTargets DESTINATION
    "${INSTALL_CMAKE_DIR}" COMPONENT dev)

