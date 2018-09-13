set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glm REQUIRED)

add_library(CruthuCore SHARED
    Cruthu.cpp
    Config.cpp
    Point.cpp
    CruthuConfig.hpp.in
)

target_link_libraries(CruthuCore
    stdc++fs
)

set_target_properties(CruthuCore PROPERTIES
    VERSION 0.1.0
    SOVERSION 1
    PUBLIC_HEADER "Config.hpp;Cruthu.hpp;IGenerate.hpp;ITera.hpp;IDLLoader.hpp;Point.hpp;IIndexer.hpp")

install(TARGETS CruthuCore
    EXPORT CruthuCoreTargets
    RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
    LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
    PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/Cruthu" COMPONENT dev)
