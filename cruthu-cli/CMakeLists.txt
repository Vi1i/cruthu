add_executable(cruthu-cli main.cpp)

target_link_libraries(cruthu-cli cruthu)

install(TARGETS cruthu-cli
    EXPORT CruthuTargets
    RUNTIME DESTINATION ${INSTALL_BIN_DIR} COMPONENT bin
)