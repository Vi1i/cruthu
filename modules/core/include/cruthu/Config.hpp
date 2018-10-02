#ifndef CRUTHU_CONFIG_HPP
#define CRUTHU_CONFIG_HPP

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <filesystem>

namespace Cruthu {
template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

class Config {
public:
    struct Index {
        const static std::string TERA;
        const static std::string TERAGEN;
        const static std::string INDEXER;
        const static std::string THREAD_COUNT;
    };

    Config(std::string filename = "");
    ~Config() = default;

    std::string GetConf(std::string index);

private:
    std::string mConfigFilename;
    std::map<std::string, std::string> mConf;
};
} // namespace Cruthu
#endif
