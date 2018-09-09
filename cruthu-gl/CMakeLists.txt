#set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(cruthu-gl
	main.cpp
	camera.hpp
)

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

# set_target_properties(cruthu PROPERTIES
#     PUBLIC_HEADER "camera/camera.h;${CMAKE_CURRENT_BINARY_DIR}/config.hpp"
# )

install(TARGETS cruthu-gl
    EXPORT CruthuTargets
    RUNTIME DESTINATION ${INSTALL_BIN_DIR} COMPONENT bin
)
