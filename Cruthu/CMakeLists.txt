set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(CruthuConfig.hpp.in "${CMAKE_CURRENT_BINARY_DIR}/CruthuConfig.hpp" @ONLY)

find_package(glm REQUIRED)

add_library(CruthuCore SHARED
    Cruthu.cpp
    Tera.cpp
    Point.cpp
    CruthuConfig.hpp.in
)

set_target_properties(CruthuCore PROPERTIES
    VERSION 0.1.0
    SOVERSION 1
    PUBLIC_HEADER "Cruthu.hpp;IGenerate.hpp;DLLoader.hpp;Point.hpp;${CMAKE_CURRENT_BINARY_DIR}/CruthuConfig.hpp")

install(TARGETS CruthuCore
    EXPORT CruthuCoreTargets
    RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
    LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
    PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/Cruthu" COMPONENT dev)
