#include <cstdlib>
#include <iostream>
#include <chrono>
#include <ctime>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cruthu/cruthu.hpp>
#include <cruthu/icosphere/icosphere.hpp>

int main(int argc, char * argv[]) {
    cruthu::Version();
    
    auto start_gen = std::chrono::high_resolution_clock::now();
    size_t world_level(std::stoi(argv[1]));
    std::vector<glm::vec3> colors;
    std::vector<glm::vec3> indices;
    cruthu::Icosphere dev = cruthu::Icosphere(world_level);
    colors = dev.GetColor();
    indices = dev.GetIndices();
    // dev.GenerateWorld();

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

    GLFWwindow* window;
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }

    // glfwWindowHint(GLFW_SAMPLES, 4);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // float *points = &indices[0].x;
    float * points = static_cast<float*>(glm::value_ptr(indices.front()));

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, indices.size() * 3 * sizeof(float), points, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    const char* vertex_shader =
    "#version 400\n"
    "in vec3 vp;"
    "void main() {"
    "  gl_Position = vec4(vp, 1.0);"
    "}";

    const char* fragment_shader =
    "#version 400\n"
    "out vec4 frag_colour;"
    "void main() {"
    "  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
    "}";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    GLuint shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);

    do{
        // wipe the drawing surface clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_programme);
        glBindVertexArray(vao);
        // draw points 0-3 from the currently bound VAO with current in-use shader
        glDrawArrays(GL_TRIANGLES, 0, indices.size());
        // update other events like input handling 
        glfwPollEvents();
        // put the stuff we've been drawing onto the display
        glfwSwapBuffers(window);

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return EXIT_SUCCESS;
}

void error_callback(int error, std::string description) {
    // fprintf(stderr, "Error: %s\n", description);
    std::cerr << "Error: " << description << std::endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}