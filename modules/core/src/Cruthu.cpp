#include <cruthu/Cruthu.hpp>
#include <cruthu/Settings.hpp>

#include <filesystem>
#include <string>
#include <exception>
#include <libconfig.h++>
#include <iostream>

cruthu::Cruthu::Cruthu() {
    this->mConfigFileName = "cruthu.cfg";

    char * xdg_config_home = std::getenv("XDG_CONFIG_HOME");
    if(xdg_config_home == NULL) {
        char * bash_home = std::getenv("HOME");
        if(bash_home == NULL) {
            //TODO: (Vi1i) Actually add this piece
            throw std::runtime_error("Needs implementation of getpuid perhaps...");
        }else{
            this->mConfigFilePath = static_cast<std::string>(bash_home) + "/.config/Cruthu";
        }
    }else{
        this->mConfigFilePath = static_cast<std::string>(xdg_config_home) + "/.config/Cruthu";
    }

    std::filesystem::path conf(this->mConfigFilePath + "/" + this->mConfigFileName);
    if(!std::filesystem::exists(conf.stem())) {
        std::filesystem::create_directories(conf.stem());
        if(!this->CreateDefaultConfigFile()) {
            throw std::runtime_error("Failed to create a default conf file");
        }
    }else if(!std::filesystem::exists(conf)) {
        if(!this->CreateDefaultConfigFile()) {
            throw std::runtime_error("Failed to create a default conf file");
        }
    }
}

bool cruthu::Cruthu::SetConfigFileName(std::string configFileName) {
    bool exists(false);
    std::filesystem::path confPath(this->mConfigFilePath + "/" + configFileName);
    exists = std::filesystem::exists(confPath);

    if(exists) {
        this->mConfigFileName = configFileName;
    }

    return exists;
}

bool cruthu::Cruthu::SetConfigFilePath(std::string configFilePath) {
    bool exists(false);
    std::filesystem::path confPath(configFilePath);
    exists = std::filesystem::exists(confPath);

    if(exists) {
        this->mConfigFilePath = configFilePath;
    }

    return exists;
}

bool cruthu::Cruthu::Initialize() {
    bool initialized(false);
    if(this->ParseConfig() && this->FindLibraries()) {
        initialized = true;
    }
    return initialized;
}

bool cruthu::Cruthu::ParseConfig() {
    bool parsed(false);
    libconfig::Config cfg;

    //TODO: Parse config file
    try {
        cfg.readFile((this->mConfigFilePath + "/" +this->mConfigFileName).c_str());
        const libconfig::Setting & root = cfg.getRoot();
        const libconfig::Setting & cfgSettings = root["Settings"];

        const libconfig::Setting & cfgITera = cfgSettings["ITera"];
        cruthu::Settings::ITera settingsITera;
        settingsITera.Name = std::string(cfgITera.lookup("Name"));
        settingsITera.LibName = std::string(cfgITera.lookup("LibName"));
        settingsITera.SignificantPointIndex = bool(cfgITera.lookup("SignificantPointIndex"));
        settingsITera.IndexChain = bool(cfgITera.lookup("IndexChain"));

        const libconfig::Setting & cfgITeraGen = cfgSettings["ITeraGen"];
        cruthu::Settings::ITeraGen settingsITeraGen;
        settingsITeraGen.Name = std::string(cfgITeraGen.lookup("Name"));
        settingsITeraGen.LibName = std::string(cfgITeraGen.lookup("LibName"));
        settingsITeraGen.SignificantPointIndex = bool(cfgITeraGen.lookup("SignificantPointIndex"));

        const libconfig::Setting & cfgIIndexer = cfgSettings["IIndexer"];
        const libconfig::Setting & cfgIndexers = cfgIIndexer["Indexers"];
        std::vector<cruthu::Settings::IIndexer> settingsIIndexers;
        for(auto z = 0; z < cfgIndexers.getLength(); ++z) {
            const libconfig::Setting & cfgIndexer = cfgIndexers[z];
            cruthu::Settings::IIndexer settingsIIndexer;

            settingsIIndexer.Name = std::string(cfgIndexer.lookup("Name"));
            settingsIIndexer.LibName = std::string(cfgIndexer.lookup("LibName"));
            settingsIIndexer.SignificantPointIndex = bool(cfgIndexer.lookup("SignificantPointIndex"));

            settingsIIndexers.push_back(settingsIIndexer);
        }

        const libconfig::Setting & cfgIForma = cfgSettings["IForma"];
        const libconfig::Setting & cfgFormas = cfgIForma["Formas"];
        std::vector<cruthu::Settings::IForma> settingsIFormas;
        for(auto z = 0; z < cfgFormas.getLength(); ++z) {
            const libconfig::Setting & cfgForma = cfgFormas[z];
            cruthu::Settings::IForma settingsIForma;

            settingsIForma.Name = std::string(cfgForma.lookup("Name"));
            settingsIForma.LibName = std::string(cfgForma.lookup("LibName"));

            settingsIFormas.push_back(settingsIForma);
        }

        this->mSettings.Tera = settingsITera;
        this->mSettings.TeraGen = settingsITeraGen;
        this->mSettings.Indexers = settingsIIndexers;
        this->mSettings.Formas = settingsIFormas;
    }catch(const libconfig::FileIOException &fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        parsed = false;
    }catch(const libconfig::ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
            << " - " << pex.getError() << std::endl;
        parsed = false;
    }  catch(const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "Missing setting " << nfex.getPath() << std::endl;
        parsed = false;
    }

    return parsed;
}

bool cruthu::Cruthu::FindLibraries() {
    bool found(false);
    return found;
}

bool cruthu::Cruthu::CreateDefaultConfigFile() {
    return false;
}
