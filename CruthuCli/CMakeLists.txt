set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cruthu-cli
    Cli.cpp)

target_link_libraries(cruthu-cli 
    CruthuCore
    ${CMAKE_DL_LIBS}
    stdc++fs
)

install(TARGETS cruthu-cli
  EXPORT CruthuCoreTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)
