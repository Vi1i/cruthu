add_executable(cruthu-gl main.cpp)

target_link_libraries(cruthu-gl cruthu)

install(TARGETS cruthu-gl
    EXPORT CruthuTargets
    RUNTIME DESTINATION ${INSTALL_BIN_DIR} COMPONENT bin
)