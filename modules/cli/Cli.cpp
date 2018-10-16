#include <cruthu/Cruthu.hpp>

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <filesystem>
#include <algorithm>
#include <iomanip>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

int main(int argc, char ** argv) {
    auto log_level = spdlog::level::trace;
    log_level = spdlog::level::debug;
    auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto logger = std::make_shared<spdlog::logger>("Cruthu-Cli", sink);
    logger->set_level(log_level);
    logger->trace("Logger Initilized");

    cruthu::Cruthu world(sink, log_level);

    if(!world.Initialize()) {
        logger->error("Cruthu initialization failed!");
        return EXIT_FAILURE;
    }

    world.Run();
    return EXIT_SUCCESS;
}
