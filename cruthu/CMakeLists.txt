find_package(glm REQUIRED)

configure_file(config.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/config.hpp @ONLY)

add_library(cruthu SHARED
    cruthu.cpp
    cruthu.hpp
    config.hpp.in
    icosphere/icosphere.hpp
    icosphere/icosphere.cpp
)

target_include_directories(cruthu PUBLIC ${GLM_INCLUDE_DIRS})

set_target_properties(cruthu PROPERTIES
    PUBLIC_HEADER "cruthu.hpp;${CMAKE_CURRENT_BINARY_DIR}/config.hpp"
)

install(TARGETS cruthu
    EXPORT CruthuTargets
    RUNTIME DESTINATION ${INSTALL_BIN_DIR} COMPONENT bin
    LIBRARY DESTINATION ${INSTALL_LIB_DIR} COMPONENT shlib
    PUBLIC_HEADER DESTINATION ${INSTALL_INCLUDE_DIR}/cruthu COMPONENT dev
)
