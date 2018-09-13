set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(CruthuCoreTera SHARED
    Tera.cpp
)

target_link_libraries(CruthuCoreTera CruthuCore)

set_target_properties(CruthuCoreTera PROPERTIES
    VERSION 0.1.0
    SOVERSION 1)

install(TARGETS CruthuCoreTera
    EXPORT CruthuCoreTargets
    RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
    LIBRARY DESTINATION "${INSTALL_LIB_DIR}/Cruthu" COMPONENT shlib
    PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/Cruthu/TeraCore" COMPONENT dev)
