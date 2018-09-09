set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Cruthu-cli Cli.cpp)

target_link_libraries(Cruthu-cli 
    CruthuCore
    ${CMAKE_DL_LIBS}
    stdc++fs
)

install(TARGETS Cruthu-cli
  # IMPORTANT: Add the bar executable to the "export-set"
  EXPORT CruthuCoreTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)
