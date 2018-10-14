#include <cruthu/Cruthu.hpp>
#include <cruthu/Settings.hpp>
#include <cruthu/DLLoader.hpp>

#include <cruthu/ITeraGen.hpp>
#include <cruthu/IIndexer.hpp>
#include <cruthu/ITera.hpp>
#include <cruthu/IForma.hpp>

#include <filesystem>
#include <string>
#include <exception>
#include <libconfig.h++>
#include <Magick++.h>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <vector>
#include <set>

cruthu::Cruthu::Cruthu(std::shared_ptr<spdlog::sinks::sink> sink, spdlog::level::level_enum level) {
    this->mLogger = std::make_shared<spdlog::logger>("Cruthu", sink);
    this->mLogger->set_level(level);
    this->mLogger->trace("Logger Initilized");

    this->mConfigFileName = "cruthu.cfg";

    char * xdg_config_home = std::getenv("XDG_CONFIG_HOME");
    if(xdg_config_home == NULL) {
        this->mLogger->debug("$XDG_CONFIG_HOME not set.");
        char * bash_home = std::getenv("HOME");
        if(bash_home == NULL) {
            this->mLogger->debug("$HOME not set.");
            //TODO: (Vi1i) Actually add this piece
            throw std::runtime_error("Needs implementation of getpuid perhaps...");
        }else{
            this->mConfigFilePath = static_cast<std::string>(bash_home) + "/.config/Cruthu";
            this->mLogger->debug("Default config file path: " + this->mConfigFilePath);
        }
    }else{
        this->mLogger->info("Default config path: " + std::string(xdg_config_home));
        this->mConfigFilePath = static_cast<std::string>(xdg_config_home) + "/.config/Cruthu";
    }

    std::filesystem::path conf(this->mConfigFilePath + "/" + this->mConfigFileName);
    if(!std::filesystem::exists(conf.parent_path())) {
        this->mLogger->debug("Directory does not exist: " + conf.parent_path().string());
        this->mLogger->debug("Creating directories: " + conf.parent_path().string());
        std::filesystem::create_directories(conf.parent_path());
    }
    if(!std::filesystem::exists(conf)) {
        this->mLogger->info("No config, creating default settings");
        if(!this->CreateDefaultConfigFile()) {
            this->mLogger->critical("Failed to create a default config file!");
            throw std::runtime_error("Failed to create a default conf file");
        }
    }
}

cruthu::Cruthu::~Cruthu() {
    this->mLogger->info("Closing libraries");
    this->mSettings.Tera.Factory->DLCloseLib();
    this->mLogger->debug("Closed ITera library");
    this->mSettings.TeraGen.Factory->DLCloseLib();
    this->mLogger->debug("Closed ITeraGen library");
    for(auto & indexer : this->mSettings.Indexers) {
        indexer.Factory->DLCloseLib();
        this->mLogger->debug("Closed IIindexer library");
    }
    for(auto & forma : this->mSettings.Formas) {
        forma.Factory->DLCloseLib();
        this->mLogger->debug("Closed IForma library");
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
    if(this->ParseConfig() && this->FindLibraries() && this->OpenLibraries()) {
        initialized = true;
    }
    return initialized;
}

void cruthu::Cruthu::Run() {
    this->mLogger->info("Creating instances");
    std::shared_ptr<cruthu::ITera> tera(this->mSettings.Tera.Factory->DLGetInstance());
    if(!this->mLogger->sinks().empty()) {
        tera->SetSink(this->mLogger->sinks().at(0), this->mLogger->level());
    }
    this->mLogger->debug("Tera instance created");
    std::shared_ptr<cruthu::ITeraGen> teraGen(this->mSettings.TeraGen.Factory->DLGetInstance());
    if(!this->mLogger->sinks().empty()) {
        teraGen->SetSink(this->mLogger->sinks().at(0), this->mLogger->level());
    }
    this->mLogger->debug("TeraGen instance created");
    std::vector<std::shared_ptr<cruthu::IIndexer>> indexers;
    for(const auto indexer : this->mSettings.Indexers) {
        std::shared_ptr<cruthu::IIndexer> i(indexer.Factory->DLGetInstance());
        if(!this->mLogger->sinks().empty()) {
            i->SetSink(this->mLogger->sinks().at(0), this->mLogger->level());
        }
        indexers.push_back(i);
        this->mLogger->debug("Indexer(" + indexer.Name + ") instance created");
    }
    std::vector<std::shared_ptr<cruthu::IForma>> formas;
    for(const auto & forma : this->mSettings.Formas) {
        std::shared_ptr<cruthu::IForma> f(forma.Factory->DLGetInstance());
        if(!this->mLogger->sinks().empty()) {
            f->SetSink(this->mLogger->sinks().at(0), this->mLogger->level());
        }
        formas.push_back(f);
        this->mLogger->debug("Forma(" + forma.Name + ") instance created");
    }
    
    teraGen->Create(tera);
    indexers.at(0)->Index(tera);
    int size = tera->IndexedNodes.size() / 100;
    for(auto z = 0; z < size; ++z) {
        this->mLogger->debug("Forma Iteration: " + std::to_string(size) + "/" + std::to_string(z));
        formas.at(0)->Modify(tera);
    }

    this->CreateImage(tera);
}

bool cruthu::Cruthu::ParseConfig() {
    auto start = std::chrono::high_resolution_clock::now();
    bool parsed(false);
    libconfig::Config cfg;
    this->mLogger->info("Parsing config file");

    //TODO: Parse config file
    try {
        /***************************************************************************
         *  Open config file
         **************************************************************************/
        this->mLogger->debug("Opening config file");
        cfg.readFile((this->mConfigFilePath + "/" +this->mConfigFileName).c_str());
        this->mLogger->debug("Reading in the base of config");
        const libconfig::Setting & root = cfg.getRoot();
        const libconfig::Setting & cfgSettings = root["Settings"];

        /***************************************************************************
         *  Read ITera settings
         **************************************************************************/
        this->mLogger->debug("Reading in ITera settings");
        const libconfig::Setting & cfgITera = cfgSettings["ITera"];
        cruthu::Settings::ITera settingsITera;
        settingsITera.Name = std::string(cfgITera.lookup("Name"));
        settingsITera.LibName = std::string(cfgITera.lookup("LibName"));
        settingsITera.SignificantPointIndex = bool(cfgITera.lookup("SignificantPointIndex"));
        settingsITera.IndexChain = bool(cfgITera.lookup("IndexChain"));

        /***************************************************************************
         *  Read ITeraGen settings
         **************************************************************************/
        this->mLogger->debug("Reading in ITeraGen settings");
        const libconfig::Setting & cfgITeraGen = cfgSettings["ITeraGen"];
        cruthu::Settings::ITeraGen settingsITeraGen;
        settingsITeraGen.Name = std::string(cfgITeraGen.lookup("Name"));
        settingsITeraGen.LibName = std::string(cfgITeraGen.lookup("LibName"));
        settingsITeraGen.SignificantPointIndex = bool(cfgITeraGen.lookup("SignificantPointIndex"));

        /***************************************************************************
         *  Read IIndexer settings
         **************************************************************************/
        this->mLogger->debug("Reading in IIndexer settings");
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

        /***************************************************************************
         *  Read IForma settings
         **************************************************************************/
        this->mLogger->debug("Reading in IForma settings");
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

        /***************************************************************************
         *  Cache settings
         **************************************************************************/
        this->mLogger->debug("Caching settings");
        this->mSettings.Tera = settingsITera;
        this->mSettings.TeraGen = settingsITeraGen;
        this->mSettings.Indexers = settingsIIndexers;
        this->mSettings.Formas = settingsIFormas;
        parsed = true;
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        this->mLogger->debug("Finished reading config file: " + std::to_string(elapsed.count()) + "s");
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
    auto start = std::chrono::high_resolution_clock::now();
    this->mLogger->info("Searching for libraries");
    bool found(true);

    /***************************************************************************
     *  Set default search path
     **************************************************************************/
    std::set<std::string> LD_LIBRARY_PATHS;
    LD_LIBRARY_PATHS.insert("/lib");
    LD_LIBRARY_PATHS.insert("/usr/lib");

    /***************************************************************************
     *  Search environment for extra paths
     **************************************************************************/
    std::string env_s(std::getenv("LD_LIBRARY_PATH"));
    std::string token;
    this->mLogger->trace("LD_LIBRARY_PATH=" + env_s);
    std::istringstream tokenStream(env_s);
    while(std::getline(tokenStream, token, ':')) {
        if(token.empty()) {
            continue;
        }

        LD_LIBRARY_PATHS.insert(token);
        this->mLogger->trace(token);
    }
    this->mLogger->debug(std::to_string(LD_LIBRARY_PATHS.size()) + " library paths found.");
    for(const auto & libPath : LD_LIBRARY_PATHS) {
        this->mLogger->trace("Library search path: " + libPath);
    }

    /***************************************************************************
     *  Search for libraries
     **************************************************************************/
    for(const auto & elm : LD_LIBRARY_PATHS) {
        try {
            for (auto & p : std::filesystem::recursive_directory_iterator(elm)) {
                if(p.is_directory()) {
                    continue;
                }
                auto so = p.path();
                if(so.filename() == this->mSettings.Tera.LibName) {
                    this->mLogger->debug("Found ITera library");
                    this->mLogger->trace(so.string());
                    if(!this->mSettings.Tera.LibPath.empty()) {
                        this->mLogger->warn("Found multiple ITera libraries, replacing with newest");
                        this->mLogger->warn("Original ITera library: " + this->mSettings.Tera.LibPath);
                        this->mLogger->warn("Replacment ITera library: " + so.string());
                    }
                    this->mSettings.Tera.LibPath = so;
                }else if(so.filename() == this->mSettings.TeraGen.LibName) {
                    this->mLogger->debug("Found ITeraGen library");
                    this->mLogger->trace(so.string());
                    if(!this->mSettings.TeraGen.LibPath.empty()) {
                        this->mLogger->warn("Found multiple ITeraGen libraries, replacing with newest");
                        this->mLogger->warn("Original ITeraGen library: " + this->mSettings.TeraGen.LibPath);
                        this->mLogger->warn("Replacment ITeraGen library: " + so.string());
                    }
                    this->mSettings.TeraGen.LibPath = so;
                }else{
                    bool IndexFound(false);
                    for(auto & indexer : this->mSettings.Indexers) {
                        if(so.filename() == indexer.LibName) {
                            this->mLogger->debug("Found an IIndexer library");
                            this->mLogger->trace(so.string());
                            if(!indexer.LibPath.empty()) {
                                this->mLogger->warn("Found multiple IIndexer libraries, replacing with newest");
                                this->mLogger->warn("Original IIndexer library: " + indexer.LibPath);
                                this->mLogger->warn("Replacment IIndexer library: " + so.string());
                            }
                            indexer.LibPath = so;
                            IndexFound = true;
                            continue;
                        }
                    }
                    if(!IndexFound) {
                        for(auto & forma : this->mSettings.Formas) {
                            if(so.filename() == forma.LibName) {
                                this->mLogger->debug("Found an IForma library");
                                this->mLogger->trace(so.string());
                                if(!forma.LibPath.empty()) {
                                    this->mLogger->warn("Found multiple IForma libraries, replacing with newest");
                                    this->mLogger->warn("Original IForma library: " + forma.LibPath);
                                    this->mLogger->warn("Replacment IForma library: " + so.string());
                                }
                                forma.LibPath = so;
                            }
                        }
                    }
                }
            }
        }catch(std::filesystem::filesystem_error err) {
            this->mLogger->error(err.what());
        }
    }

    /***************************************************************************
     *  Check if libraries were found
     **************************************************************************/
    if(this->mSettings.Tera.LibPath.empty()) {
        found = false;
        this->mLogger->error("ITera library, " + this->mSettings.Tera.LibName + ", was not found!");
    }
    if(this->mSettings.TeraGen.LibPath.empty()) {
        found = false;
        this->mLogger->error("ITeraGen library, " + this->mSettings.TeraGen.LibName + ", was not found!");
    }
    for(auto & indexer : this->mSettings.Indexers) {
        if(indexer.LibPath.empty()) {
            found = false;
            this->mLogger->error("IIndexer library, " + indexer.LibName + ", was not found!");
        }
    }
    for(auto & forma : this->mSettings.Formas) {
        if(forma.LibPath.empty()) {
            found = false;
            this->mLogger->error("IForma library, " + forma.LibName + ", was not found!");
        }
    }

    if(!found) {
        this->mLogger->error("Specified libraries not found!");
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    this->mLogger->debug("Finished library search: " + std::to_string(elapsed.count()) + "s");
    return found;
}

bool cruthu::Cruthu::OpenLibraries() {
    bool opened(false);

    this->mLogger->info("Creating factories");
    this->mSettings.Tera.Factory = std::shared_ptr<cruthu::DLLoader<cruthu::ITera>>(new cruthu::DLLoader<cruthu::ITera>(this->mSettings.Tera.LibPath));
    this->mLogger->debug("Created ITera factory");
    this->mSettings.TeraGen.Factory = std::shared_ptr<cruthu::DLLoader<cruthu::ITeraGen>>(new cruthu::DLLoader<cruthu::ITeraGen>(this->mSettings.TeraGen.LibPath));
    this->mLogger->debug("Created ITeraGen factory");
    for(auto & indexer : this->mSettings.Indexers) {
        indexer.Factory = std::shared_ptr<cruthu::DLLoader<cruthu::IIndexer>>(new cruthu::DLLoader<cruthu::IIndexer>(indexer.LibPath));
        this->mLogger->debug("Created IIndexer factory");
    }
    for(auto & forma : this->mSettings.Formas) {
        forma.Factory = std::shared_ptr<cruthu::DLLoader<cruthu::IForma>>(new cruthu::DLLoader<cruthu::IForma>(forma.LibPath));
        this->mLogger->debug("Created IForma factory");
    }

    this->mLogger->info("Opening libraries");
    this->mSettings.Tera.Factory->DLOpenLib();
    this->mLogger->debug("Opened ITera library");
    this->mSettings.TeraGen.Factory->DLOpenLib();
    this->mLogger->debug("Opened ITeraGen library");
    for(auto & indexer : this->mSettings.Indexers) {
        indexer.Factory->DLOpenLib();
        this->mLogger->debug("Opened IIndxer library");
    }
    for(auto & forma : this->mSettings.Formas) {
        forma.Factory->DLOpenLib();
        this->mLogger->debug("Opened IForma library");
    }

    opened = true;
    return opened;
}

bool cruthu::Cruthu::CreateDefaultConfigFile() {
    return false;
}

void cruthu::Cruthu::CreateImage(std::shared_ptr<cruthu::ITera> tera) {
    double long size = std::sqrt(tera->Nodes.size());
    Magick::Image image(Magick::Geometry(size, size), "white");
    image.type(Magick::GrayscaleType);

    for(auto y = 0; y < size; ++y) {
        for(auto x = 0; x < size; ++x) {
            double color = tera->Nodes.at((y * size) + x)->GetHeight();
            this->mLogger->trace(tera->Nodes.at((y * size) + x)->to_string() + ": " + std::to_string(color));
            image.pixelColor(y, x, Magick::ColorGray(color));
        }
    }

    image.syncPixels();
    image.write("temp.png");
}
