find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(cruthu-gl main.cpp)

target_include_directories(cruthu-gl PUBLIC 
	${OPENGL_INCLUDE_DIR}
	${GLEW_INCLUDE_DIRS}
)

target_link_libraries(cruthu-gl
	cruthu
	${OPENGL_gl_LIBRARY}
	${GLEW_LIBRARIES}
	glfw
	# ${OPENGL_glu_LIBRARY}
)

install(TARGETS cruthu-gl
    EXPORT CruthuTargets
    RUNTIME DESTINATION ${INSTALL_BIN_DIR} COMPONENT bin
)