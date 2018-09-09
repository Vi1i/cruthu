find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(cruthu-vulkan
	main.cpp
)

target_include_directories(cruthu-vulkan PUBLIC 
    ${Vulkan_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
)

target_link_libraries(cruthu-vulkan
	cruthu
    ${Vulkan_LIBRARIES}
    glfw
)

install(TARGETS cruthu-vulkan
    EXPORT CruthuTargets
    RUNTIME DESTINATION ${INSTALL_BIN_DIR} COMPONENT bin
)
