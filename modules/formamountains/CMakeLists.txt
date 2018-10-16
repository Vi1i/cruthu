set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(CruthuCoreFormaMountains SHARED
    src/FormaMountains.cpp
)

target_link_libraries(CruthuCoreFormaMountains CruthuCore)

target_include_directories(CruthuCoreFormaMountains
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_target_properties(CruthuCoreFormaMountains PROPERTIES
    VERSION 0.1.0
    SOVERSION 0
)

install(DIRECTORY include/ DESTINATION "${INSTALL_INCLUDE_DIR}")
install(TARGETS CruthuCoreFormaMountains
    EXPORT CruthuCoreTargets
    RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
    LIBRARY DESTINATION "${INSTALL_LIB_DIR}/Cruthu/core" COMPONENT shlib
)
