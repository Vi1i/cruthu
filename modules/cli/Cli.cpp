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

//void Run(std::shared_ptr<cruthu::DLLoader<cruthu::IIndexer>> indexerLoader, std::shared_ptr<cruthu::DLLoader<cruthu::ITera>> teraLoader, std::vector<std::shared_ptr<cruthu::Node>> nodes, std::shared_ptr<cruthu::Node> significantNode) {
//    std::shared_ptr<cruthu::IIndexer> indexer = indexerLoader.get()->DLGetInstance();
//    std::shared_ptr<cruthu::ITera> tera = teraLoader.get()->DLGetInstance();
//
//    tera.get()->SetIndexer(indexer);
//    tera.get()->SetNodes(nodes);
//    // TODO: (Vi1i) Need to implelment this...
//    //tera.get()->SetSignificantNode(significantNode);
//    tera.get()->IndexNodes();
//}
//
//std::vector<std::shared_ptr<cruthu::Node>> Generate(std::shared_ptr<cruthu::DLLoader<cruthu::ITeraGen>> dlloader) {
//    std::shared_ptr<cruthu::ITeraGen> teraGen = dlloader.get()->DLGetInstance();
//
//	return teraGen.get()->Create();
//}
//
//std::map<std::string, std::string> Search(std::vector<std::string> LD_LIBRARY_PATHS, std::map<std::string, std::string> sharedLibraryNames) {
//    std::map<std::string, std::string> sharedLibraryPaths;
//    for(const auto & elm : LD_LIBRARY_PATHS) {
//        if(elm.empty()) {
//            continue;
//        }
//        try {
//            for (auto & p : std::filesystem::recursive_directory_iterator(elm)) {
//                if(p.is_directory()) {
//                    continue;
//                }
//                auto so = p.path();
//                for(const auto sharedLibraryName :sharedLibraryNames) {
//                    if(so.filename() == sharedLibraryName.second) {
//                        sharedLibraryPaths[sharedLibraryName.first] = so;
//                    }
//                }
//            }
//        }catch(std::filesystem::filesystem_error err) {
//            continue;
//        }
//    }
//
//    return sharedLibraryPaths;
//}

int main(int argc, char ** argv) {
    auto log_level = spdlog::level::trace;
    auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto logger = std::make_shared<spdlog::logger>("Cruthu-Cli", sink);
    logger->set_level(log_level);
    logger->trace("Logger Initilized");

    cruthu::Cruthu world;

    world.SetSink(sink, log_level);

    if(!world.Initialize()) {
        logger->error("Cruthu initialization failed!");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

    //std::map<std::string, std::string> sharedLibraryNames;
    //sharedLibraryNames[cruthu::Config::Index::TERA] = conf.GetConf(cruthu::Config::Index::TERA);
    //sharedLibraryNames[cruthu::Config::Index::TERAGEN] = conf.GetConf(cruthu::Config::Index::TERAGEN);
    //sharedLibraryNames[cruthu::Config::Index::INDEXER] = conf.GetConf(cruthu::Config::Index::INDEXER);

    //std::vector<std::string> LD_LIBRARY_PATHS;
    //LD_LIBRARY_PATHS.push_back("/lib");
    //LD_LIBRARY_PATHS.push_back("/usr/lib");

    //std::vector<std::string> env_l;
    //env_l = cruthu::split(std::getenv("LD_LIBRARY_PATH"), ':');
    //if(!env_l.empty()) {
    //    LD_LIBRARY_PATHS.insert(std::end(LD_LIBRARY_PATHS), std::begin(env_l), std::end(env_l));
    //}

    //std::map<std::string, std::string> sharedLibraryPaths = Search(LD_LIBRARY_PATHS, sharedLibraryNames);
    //std::cout << "-----------------------------------------------------------------------------" << std::endl;
    //std::cout << "|" << std::internal << std::setw(10) << std::setfill(' ') << "PLUGIN";
    //std::cout << std::internal << std::setw(3) << " | ";
    //std::cout << std::left << std::setw(10) << std::setfill(' ') << "Path" << std::endl;
    //std::cout << "-----------------------------------------------------------------------------" << std::endl;
    //for(const auto sharedLibraryPath : sharedLibraryPaths) {
    //    std::cout <<"|" << std::right << std::setw(10) << std::setfill(' ') << sharedLibraryPath.first;
    //    std::cout << std::setw(3) << " | ";
    //    std::cout << std::left << std::setw(10) << std::setfill(' ') << sharedLibraryPath.second << std::endl;
    //}
    //std::cout << "-----------------------------------------------------------------------------" << std::endl;

    //std::shared_ptr<cruthu::DLLoader<cruthu::ITeraGen>> teragen;
    //std::shared_ptr<cruthu::DLLoader<cruthu::IIndexer>> indexer;
    //std::shared_ptr<cruthu::DLLoader<cruthu::ITera>> tera;
    //for(const auto sharedLibraryPath : sharedLibraryPaths) {
    //    if(sharedLibraryPath.first == cruthu::Config::Index::TERAGEN) {
    //        teragen = std::shared_ptr<cruthu::DLLoader<cruthu::ITeraGen>>(new cruthu::DLLoader<cruthu::ITeraGen>(sharedLibraryPath.second));
    //    }else if(sharedLibraryPath.first == cruthu::Config::Index::TERA) {
    //        tera = std::shared_ptr<cruthu::DLLoader<cruthu::ITera>>(new cruthu::DLLoader<cruthu::ITera>(sharedLibraryPath.second));
    //    }else if(sharedLibraryPath.first == cruthu::Config::Index::INDEXER) {
    //        indexer = std::shared_ptr<cruthu::DLLoader<cruthu::IIndexer>>(new cruthu::DLLoader<cruthu::IIndexer>(sharedLibraryPath.second));
    //    }else{
    //        std::cerr << "Note a recognized object" << std::endl;
    //    }
    //}
    //teragen.get()->DLOpenLib();
    //std::vector<std::shared_ptr<cruthu::Node>> nodes(Generate(teragen));
    //teragen.get()->DLCloseLib();

    //return EXIT_SUCCESS;
}
