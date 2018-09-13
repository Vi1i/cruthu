#include "Cruthu/Cruthu.hpp"
#include "Cruthu/DLLoader.hpp"
#include "Cruthu/Config.hpp"


#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <filesystem>
#include <algorithm>

//void Generate(Cruthu::DLLoader<Cruthu::IGenerate>& dlloader) {
//    std::shared_ptr<Cruthu::IGenerate> teraGen = dlloader.DLGetInstance();
//
//	teraGen.get()->Create();
//}

int main(int argc, char ** argv) {
    Cruthu::Config conf(argv[1]);

    std::vector<std::string> sharedLibraryNames;
    sharedLibraryNames.push_back(conf.GetConf(Cruthu::Config::Index::TERA));
    sharedLibraryNames.push_back(conf.GetConf(Cruthu::Config::Index::INDEXER));

    std::vector<std::string> LD_LIBRARY_PATHS;
    LD_LIBRARY_PATHS.push_back("/lib");
    LD_LIBRARY_PATHS.push_back("/usr/lib");

    std::vector<std::string> env_l;
    env_l = Cruthu::split(std::getenv("LD_LIBRARY_PATH"), ':');
    if(!env_l.empty()) {
        LD_LIBRARY_PATHS.insert(std::end(LD_LIBRARY_PATHS), std::begin(env_l), std::end(env_l));
    }

    std::vector<std::string> sharedLibraryPaths;
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
                    if(so.filename() == sharedLibraryName) {
                        sharedLibraryPaths.push_back(so);
                    }
                }
            }
        }catch(std::filesystem::filesystem_error err) {
            continue;
        }
    }

    std::sort(sharedLibraryPaths.begin(), sharedLibraryPaths.end());
    sharedLibraryPaths.erase(unique(sharedLibraryPaths.begin(), sharedLibraryPaths.end()), sharedLibraryPaths.end());
    for(const auto sharedLibraryPath : sharedLibraryPaths) {
        std::cout << sharedLibraryPath << std::endl;
    }

    return EXIT_SUCCESS;
}
