#include "Config.hpp"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <map>
#include <filesystem>

const std::string Cruthu::Config::Index::TERA = "ITera";
const std::string Cruthu::Config::Index::INDEXER = "IIndexer";
const std::string Cruthu::Config::Index::THREAD_COUNT = "Thread_Count";

Cruthu::Config::Config(std::string filename) {
    this->mConfigFilename = filename;
    if(this->mConfigFilename.empty()) {
        char * xdg_config_home = std::getenv("XDG_CONFIG_HOME");
        if(xdg_config_home == NULL) {
            char * bash_home = std::getenv("HOME");
            if(bash_home == NULL) {
                //TODO: (Vi1i) Actually add this piece
                throw std::runtime_error("Needs implementation of getpuid perhaps...");
            }else{
                this->mConfigFilename = static_cast<std::string>(bash_home) + "/.config/Cruthu/config.conf";
            }
        }else{
            this->mConfigFilename = static_cast<std::string>(xdg_config_home) + "/.config/Cruthu/config.conf";
        }
    }

    std::filesystem::path configFilePath(this->mConfigFilename);
    if(std::filesystem::exists(configFilePath)) {
        std::ifstream file;
        file.open(this->mConfigFilename, std::ios::in);
        if(file.is_open()) {
            std::string line;
            while(std::getline(file, line)) {
                //TODO: Parse config file
                std::vector<std::string> key_val(Cruthu::split(line, '='));
                if(key_val[0] == Cruthu::Config::Index::TERA) {
                    this->mConf[Cruthu::Config::Index::TERA] = key_val[1];
                }else if(key_val[0] == Cruthu::Config::Index::INDEXER) {
                    this->mConf[Cruthu::Config::Index::INDEXER] = key_val[1];
                }else if(key_val[0] == Cruthu::Config::Index::THREAD_COUNT) {
                    this->mConf[Cruthu::Config::Index::THREAD_COUNT] = key_val[1];
                }else{
                    throw std::runtime_error("Invalid cruthu.conf file key: " + key_val[0]);
                }
            }
        }else{
            throw std::runtime_error("Could not open config file: " + this->mConfigFilename);
        }
    }else{
        //TODO: SetDefaults
        //TODO: (Vi1i) Maybe relook the whole enum thing.
        this->mConf[Cruthu::Config::Index::TERA] = "libCruthuCoreTera.so";
        this->mConf[Cruthu::Config::Index::INDEXER] = "libCruthuCoreTera.so";
    }
}

std::string Cruthu::Config::GetConf(std::string index) {
    return this->mConf[index];
}
