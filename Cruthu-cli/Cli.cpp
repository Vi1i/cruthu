#include "Cruthu/Cruthu.hpp"
#include "Cruthu/IGenerate.hpp"
#include "Cruthu/DLLoader.hpp"

#include <dlfcn.h>

#include <cstdlib>
#include <iostream>

#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <filesystem>

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

void Generate(Cruthu::DLLoader<Cruthu::IGenerate>& dlloader) {
    std::shared_ptr<Cruthu::IGenerate> teraGen = dlloader.DLGetInstance();

	teraGen.get()->Create();
}

int main(int argc, char ** argv) {
    std::vector<std::string> CruthuSharedLibraryNames;
    CruthuSharedLibraryNames.push_back("libCruthuCoreTeraGenerate.so");
    std::vector<std::string> CruthuSharedLibraries;

    std::vector<std::string> LD_LIBRARY_PATHS;
    LD_LIBRARY_PATHS.push_back("/lib");
    LD_LIBRARY_PATHS.push_back("/usr/lib");

    std::vector<std::string> env_l;
    env_l = split(std::getenv("LD_LIBRARY_PATH"), ':');

    if(!env_l.empty()) {
        LD_LIBRARY_PATHS.insert(std::end(LD_LIBRARY_PATHS), std::begin(env_l), std::end(env_l));
    }

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
                for(const auto CruthuSharedLibraryName : CruthuSharedLibraryNames) {
                    if(so.filename() == CruthuSharedLibraryName) {
                        CruthuSharedLibraries.push_back(so);
                    }
                }
            }
        }catch(std::filesystem::filesystem_error err) {
            continue;
        }
    }

    for(const auto CruthuSharedLibrary : CruthuSharedLibraries) {
        Cruthu::DLLoader<Cruthu::IGenerate> dlloader(CruthuSharedLibrary);
        dlloader.DLOpenLib();
        Generate(dlloader);
        dlloader.DLCloseLib();
    }

    return EXIT_SUCCESS;
}
