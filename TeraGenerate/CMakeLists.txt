set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(TeraGeneratorConfig.hpp.in "${CMAKE_CURRENT_BINARY_DIR}/TeraGeneratorConfig.hpp" @ONLY)

add_library(CruthuCoreTeraGenerate SHARED
    Generate.cpp
    TeraGeneratorConfig.hpp.in
)

target_link_libraries(CruthuCoreTeraGenerate CruthuCore)

set_target_properties(CruthuCoreTeraGenerate PROPERTIES
    VERSION 0.1.0
    SOVERSION 1
    PUBLIC_HEADER "Generate.hpp;${CMAKE_CURRENT_BINARY_DIR}/TeraGeneratorConfig.hpp")

install(TARGETS CruthuCoreTeraGenerate
    EXPORT CruthuCoreTargets
    RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
    LIBRARY DESTINATION "${INSTALL_LIB_DIR}/Cruthu" COMPONENT shlib
    PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/Cruthu/TeraGenerator" COMPONENT dev)
