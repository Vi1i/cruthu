set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(CruthuCoreIndexerMountains SHARED
    src/IndexerMountains.cpp
)

target_link_libraries(CruthuCoreIndexerMountains CruthuCore)

target_include_directories(CruthuCoreIndexerMountains
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_target_properties(CruthuCoreIndexerMountains PROPERTIES
    VERSION 0.1.0
    SOVERSION 0
)

install(DIRECTORY include/ DESTINATION "${INSTALL_INCLUDE_DIR}")

install(TARGETS CruthuCoreIndexerMountains
    EXPORT CruthuCoreTargets
    RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
    LIBRARY DESTINATION "${INSTALL_LIB_DIR}/Cruthu/core" COMPONENT shlib
)
