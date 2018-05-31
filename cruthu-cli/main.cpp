#include <cstdlib>
#include <iostream>
#include <chrono>
#include <ctime>
#include <glm/glm.hpp>

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

    return EXIT_SUCCESS;
}
