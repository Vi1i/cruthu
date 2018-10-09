#include <cruthu/Config.hpp>

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <map>
#include <filesystem>

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
        //TODO: Parse config file
        try {
            this->mConf.readFile(this->mConfigFilename.c_str());
        }catch(const libconfig::FileIOException &fioex) {
            std::cerr << "I/O error while reading file." << std::endl;
            throw fioex;
        }catch(const libconfig::ParseException &pex) {
            std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                << " - " << pex.getError() << std::endl;
            throw pex;
        }
        const libconfig::Setting & root = this->mConf.getRoot();
        std::string IIndexerName;
        std::string ITeraName;
        std::string ITeraGenName;
        std::map<std::string, std::string> IFormas;
        try {
            const libconfig::Setting & plugins = root["plugins"];
            IIndexerName = std::string(plugins.lookup("IIndexer"));
            ITeraName = std::string(plugins.lookup("ITera"));
            ITeraGenName = std::string(plugins.lookup("ITeraGen"));

            const libconfig::Setting & formas = plugins["IForma"];
            for(auto z = 0; z < formas.getLength(); ++z) {
                const libconfig::Setting & forma = formas[z];
                IFormas[forma.lookup("name")] = std::string(forma.lookup("lib"));
            }
        }  catch(const libconfig::SettingNotFoundException &nfex) {
            // Ignore.
        }
        std::cout << IIndexerName << std::endl;
        std::cout << ITeraName << std::endl;
        std::cout << ITeraGenName << std::endl;
        std::cout << "Forma:" << std::endl;
        for(auto const & forma : IFormas) {
            std::cout << "\t" << forma.first << std::endl;
            std::cout << "\t\t" << forma.second << std::endl;
        }
    }else{
        //TODO: SetDefaults
    }
}
