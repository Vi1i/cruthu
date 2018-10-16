set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(CruthuCoreFormaPerlin SHARED
    src/FormaPerlin.cpp
    src/PerlinNoise.cpp
)

target_link_libraries(CruthuCoreFormaPerlin CruthuCore)

target_include_directories(CruthuCoreFormaPerlin
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_target_properties(CruthuCoreFormaPerlin PROPERTIES
    VERSION 0.1.0
    SOVERSION 0
)

install(DIRECTORY include/ DESTINATION "${INSTALL_INCLUDE_DIR}")
install(TARGETS CruthuCoreFormaPerlin
    EXPORT CruthuCoreTargets
    RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
    LIBRARY DESTINATION "${INSTALL_LIB_DIR}/Cruthu/core" COMPONENT shlib
)
