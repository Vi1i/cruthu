#ifndef CRUTHU_CONFIG_HPP
#define CRUTHU_CONFIG_HPP

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <filesystem>
#include <libconfig.h++>

namespace cruthu {
class Config {
public:
    Config(std::string filename = "");
    ~Config() = default;

private:
    std::string mConfigFilename;
    libconfig::Config mConf;
};
} // namespace cruthu
#endif
