set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glm REQUIRED)
find_package(Boost REQUIRED)
find_package(libconfig++ REQUIRED)

message("Config Found: ${CONFIG_LIBRARY}")

add_library(CruthuCore SHARED
    src/Cruthu.cpp
    src/Config.cpp
    src/Point.cpp
)

target_link_libraries(CruthuCore
    stdc++fs
    ${LIBCONFIG++_LIBRARIES}
)

target_include_directories(CruthuCore
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_target_properties(CruthuCore PROPERTIES
    VERSION 0.1.0
    SOVERSION 0
)

install(DIRECTORY include/ DESTINATION "${INSTALL_INCLUDE_DIR}")

install(TARGETS CruthuCore
    EXPORT CruthuCoreTargets
    RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
    LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
)
