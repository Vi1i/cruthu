configure_file(config.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/config.hpp @ONLY)

add_library(cruthu SHARED
    cruthu.cpp
    cruthu.hpp
    config.hpp.in
    voxel/block.hpp
    voxel/block.cpp
    voxel/blocktype.hpp
    # voxel/chunk.hpp
    # voxel/chunk.cpp
)

set_target_properties(cruthu PROPERTIES
    PUBLIC_HEADER "cruthu.hpp;${CMAKE_CURRENT_BINARY_DIR}/config.hpp"
)

install(TARGETS cruthu
    EXPORT CruthuTargets
    RUNTIME DESTINATION ${INSTALL_BIN_DIR} COMPONENT bin
    LIBRARY DESTINATION ${INSTALL_LIB_DIR} COMPONENT shlib
    PUBLIC_HEADER DESTINATION ${INSTALL_INCLUDE_DIR}/cruthu COMPONENT dev
)
