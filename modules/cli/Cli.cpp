#include <cruthu/Cruthu.hpp>
#include <cruthu/DLLoader.hpp>
#include <cruthu/Config.hpp>
#include <cruthu/IGenerate.hpp>


#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <filesystem>
#include <algorithm>
#include <iomanip>

void Generate(Cruthu::DLLoader<Cruthu::IGenerate>& dlloader) {
    std::shared_ptr<Cruthu::IGenerate> teraGen = dlloader.DLGetInstance();

	size_t fSize = teraGen.get()->Create().size();
    std::cout << "Node Count: " << fSize << std::endl;
}

std::map<std::string, std::string> Search(std::vector<std::string> LD_LIBRARY_PATHS, std::map<std::string, std::string> sharedLibraryNames) {
    std::map<std::string, std::string> sharedLibraryPaths;
    for(const auto & elm : LD_LIBRARY_PATHS) {
        if(elm.empty()) {
            continue;
        }
        try {
            for (auto & p : std::filesystem::recursive_directory_iterator(elm)) {
                if(p.is_directory()) {
                    continue;
                }
                auto so = p.path();
                for(const auto sharedLibraryName :sharedLibraryNames) {
                    if(so.filename() == sharedLibraryName.second) {
                        sharedLibraryPaths[sharedLibraryName.first] = so;
                    }
                }
            }
        }catch(std::filesystem::filesystem_error err) {
            continue;
        }
    }

    return sharedLibraryPaths;
}

int main(int argc, char ** argv) {
    Cruthu::Config conf(argv[1]);

    std::map<std::string, std::string> sharedLibraryNames;
    sharedLibraryNames[Cruthu::Config::Index::TERA] = conf.GetConf(Cruthu::Config::Index::TERA);
    sharedLibraryNames[Cruthu::Config::Index::TERAGEN] = conf.GetConf(Cruthu::Config::Index::TERAGEN);
    sharedLibraryNames[Cruthu::Config::Index::INDEXER] = conf.GetConf(Cruthu::Config::Index::INDEXER);

    std::vector<std::string> LD_LIBRARY_PATHS;
    LD_LIBRARY_PATHS.push_back("/lib");
    LD_LIBRARY_PATHS.push_back("/usr/lib");

    std::vector<std::string> env_l;
    env_l = Cruthu::split(std::getenv("LD_LIBRARY_PATH"), ':');
    if(!env_l.empty()) {
        LD_LIBRARY_PATHS.insert(std::end(LD_LIBRARY_PATHS), std::begin(env_l), std::end(env_l));
    }

    std::map<std::string, std::string> sharedLibraryPaths = Search(LD_LIBRARY_PATHS, sharedLibraryNames);
    std::cout << "-----------------------------------------------------------------------------" << std::endl;
    std::cout << "|" << std::internal << std::setw(10) << std::setfill(' ') << "PLUGIN";
    std::cout << std::internal << std::setw(3) << " | ";
    std::cout << std::left << std::setw(10) << std::setfill(' ') << "Path" << std::endl;
    std::cout << "-----------------------------------------------------------------------------" << std::endl;
    for(const auto sharedLibraryPath : sharedLibraryPaths) {
        std::cout <<"|" << std::right << std::setw(10) << std::setfill(' ') << sharedLibraryPath.first;
        std::cout << std::setw(3) << " | ";
        std::cout << std::left << std::setw(10) << std::setfill(' ') << sharedLibraryPath.second << std::endl;
    }
    std::cout << "-----------------------------------------------------------------------------" << std::endl;

    for(const auto sharedLibraryPath : sharedLibraryPaths) {
        if(sharedLibraryPath.first == Cruthu::Config::Index::TERAGEN) {
            Cruthu::DLLoader<Cruthu::IGenerate> dlloader(sharedLibraryPath.second);
            dlloader.DLOpenLib();
            Generate(dlloader);
            dlloader.DLCloseLib();
        }
    }

    return EXIT_SUCCESS;
}
