#find_package(glm REQUIRED)

add_executable(cruthu-cli main.cpp)

target_link_libraries(cruthu-cli cruthu)

target_include_directories(cruthu PUBLIC ${GLM_INCLUDE_DIRS})

install(TARGETS cruthu-cli
    EXPORT CruthuTargets
    RUNTIME DESTINATION ${INSTALL_BIN_DIR} COMPONENT bin
)
