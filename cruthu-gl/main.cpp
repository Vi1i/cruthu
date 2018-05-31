#include <cstdlib>
#include <iostream>
#include <chrono>
#include <ctime>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cruthu/cruthu.hpp>
#include <cruthu/icosphere/icosphere.hpp>

#include <cruthu-gl/camera.hpp>

GLFWwindow * initialize();
cruthu::Icosphere get_sphere(size_t world_level);
void gen_world(size_t level, size_t seed, std::vector<glm::vec3> &mesh_colors, std::vector<glm::vec3> &mesh);
std::vector<GLuint> load_shaders(std::vector<glm::vec3> &mesh_colors, std::vector<glm::vec3> &mesh);
void loop();
void cleanup();

void error_callback(int error, std::string description) {
    // fprintf(stderr, "Error: %s\n", description);
    std::cerr << "Error: " << description << std::endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(int argc, char * argv[]) {
    cruthu::Version();
    size_t world_level(std::stoi(argv[1]));
    size_t seed = 0;

    
    GLFWwindow * window;
    window = initialize();

    std::vector<glm::vec3> mesh_colors;
    std::vector<glm::vec3> mesh;
    gen_world(world_level, seed, mesh_colors, mesh);

    std::vector<GLuint> data = load_shaders(mesh_colors, mesh);
    GLuint vao = data[0];
    GLuint shader_programme = data[1];

    while(!glfwWindowShouldClose(window)) {
        // processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_programme);

        glBindVertexArray(vao);

        // glEnableVertexAttribArray(0);
        // glBindBuffer(GL_ARRAY_BUFFER, vbo);
        // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, mesh.size());
        // glDrawArrays(GL_POINTS, 0, indices.size());
        // glDisableVertexAttribArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Close OpenGL window and terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}

GLFWwindow * initialize() {

    if(!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    // glfwWindowHint(GLFW_FLOATING, GL_TRUE);

    GLFWwindow * window;

    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primary);
    int height = mode->height;
    int width = mode->width;

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(height, height, "Cruthu",  glfwGetPrimaryMonitor(), NULL);
    if(window == NULL) {
        std::cerr << "Failed to initialize GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }

    // get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    glfwSetKeyCallback(window, key_callback);
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // glfwSetCursorPosCallback(window, mouse_callback);
    // glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_PROGRAM_POINT_SIZE);
    glPointSize(1.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    return window;
}

std::vector<GLuint> load_shaders(std::vector<glm::vec3> &mesh_colors, std::vector<glm::vec3> &mesh) {
    float * points = static_cast<float*>(glm::value_ptr(mesh.front()));
    float * colors = static_cast<float*>(glm::value_ptr(mesh_colors.front()));

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.size() * 3 * sizeof(float), points, GL_STATIC_DRAW);

    GLuint vboc;
    glGenBuffers(1, &vboc);
    glBindBuffer(GL_ARRAY_BUFFER, vboc);
    glBufferData(GL_ARRAY_BUFFER, mesh_colors.size() * 3 * sizeof(float), colors, GL_STATIC_DRAW);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vboc);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    const char* vertex_shader =
    "#version 130\n"
    "in vec3 vp;"
    "in vec3 vc;"
    "out vec3 frag_colour;"
    "void main() {"
    "  gl_Position = vec4(vp, 1.0);"
    "  frag_colour = vc;"
    "}";

    const char* fragment_shader =
    "#version 130\n"
    "in vec3 frag_colour;"
    "out vec3 color;"
    "void main() {"
    "  color = vec3(1,1,1);"
    "}";

    GLint Result = GL_FALSE;
    int InfoLogLength;

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if(InfoLogLength > 0) {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(vs, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);    glGetShaderiv(vs, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if(InfoLogLength > 0) {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(fs, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }

    GLuint shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);

    // Check the program
    glGetProgramiv(shader_programme, GL_LINK_STATUS, &Result);
    glGetProgramiv(shader_programme, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if(InfoLogLength > 0) {
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(shader_programme, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }
    
    glDetachShader(shader_programme, vs);
    glDetachShader(shader_programme, fs);
    
    glDeleteShader(vs);
    glDeleteShader(fs);

    std::vector<GLuint> data;
    data.push_back(vao);
    data.push_back(shader_programme);

    return data;
}


cruthu::Icosphere get_sphere(size_t world_level) {
    auto start_gen = std::chrono::high_resolution_clock::now();

    cruthu::Icosphere dev = cruthu::Icosphere(world_level);

    auto end_gen = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end_gen - start_gen;
    auto gen_elapsed_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_time).count();
    auto gen_elapsed_milliseconds = gen_elapsed_nanoseconds / 1000000.0;
    auto gen_elapsed_seconds = gen_elapsed_milliseconds / 1000.0;

    std::time_t start_gen_time = std::chrono::high_resolution_clock::to_time_t(start_gen);
    std::time_t end_gen_time = std::chrono::high_resolution_clock::to_time_t(end_gen);

    std::cout << "Started at: " << std::ctime(&start_gen_time) << std::endl;
    std::cout << "Finished at: " << std::ctime(&end_gen_time) << std::endl;
    std::cout << "Elapsed time: " << gen_elapsed_seconds << "s\n";
    std::cout << "Elapsed time: " << gen_elapsed_milliseconds << "ms\n";
    std::cout << "Elapsed time: " << gen_elapsed_nanoseconds << "ns\n";
    return dev;
}

void gen_world(size_t level, size_t seed, std::vector<glm::vec3> &mesh_colors, std::vector<glm::vec3> &mesh) {
    cruthu::Icosphere dev = get_sphere(level);
    std::vector<glm::vec3> points = dev.GetIndices();
    std::vector<glm::vec3> points_colors = dev.GetColor();

    mesh = points;
    mesh_colors = points_colors;

    // float *points = &indices[0].x;
    // float * points = static_cast<float*>(glm::value_ptr(dev.GetIndices().front()));
}

void loop() {
    // while(glfwGetKey(this->_window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(this->_window) == 0) {
    //       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
    //       glUseProgram(this->_programID);
  
    //       glUniformMatrix4fv(this->_matrixID, 1, GL_FALSE, &this->_mvp[0][0]);
  
    //       glEnableVertexAttribArray(0);
    //       glBindBuffer(GL_ARRAY_BUFFER, this->_vertexBuffer);
    //       glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  
    //       glEnableVertexAttribArray(1);
    //       glBindBuffer(GL_ARRAY_BUFFER, this->_colorBuffer);
    //       glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  
    //       glDrawArrays(GL_TRIANGLES, 0, this->_icsp.GetIndices().size()*3);
  
    //       glDisableVertexAttribArray(0);
    //       glDisableVertexAttribArray(1);
  
    //       glfwSwapBuffers(this->_window);
    //       glfwPollEvents();
    //   }  
}
