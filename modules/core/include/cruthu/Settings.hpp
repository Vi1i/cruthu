#ifndef CRUTHU_SETTINGS_HPP
#define CRUTHU_SETTINGS_HPP

#include <cruthu/IDLLoader.hpp>
#include <cruthu/ITera.hpp>
#include <cruthu/ITeraGen.hpp>
#include <cruthu/IIndexer.hpp>
#include <cruthu/IForma.hpp>

#include <string>
#include <vector>
#include <memory>

namespace cruthu {
class Settings {
public:
    struct Cruthu {
        enum Types {
            STEP = 0,
            FULL = 1,
        };
        unsigned int ThreadCount;
        unsigned int Seed;
        cruthu::Settings::Cruthu::Types Type;
    };
    struct ITera {
        std::string Name;
        std::string LibName;
        std::string LibPath;
        std::shared_ptr<cruthu::IDLLoader<cruthu::ITera>> Factory;
    };

    struct ITeraGen {
        enum Types {
            D2 = 0,
            D3 = 1,
        };
        std::string Name;
        std::string LibName;
        std::string LibPath;
        cruthu::Settings::ITeraGen::Types Type;
        std::shared_ptr<cruthu::IDLLoader<cruthu::ITeraGen>> Factory;
    };

    struct IIndexer {
        std::string Name;
        std::string LibName;
        std::string LibPath;
        std::shared_ptr<cruthu::IDLLoader<cruthu::IIndexer>> Factory;
    };

    struct IForma {
        std::string Name;
        std::string LibName;
        std::string LibPath;
        unsigned int Steps;
        unsigned int Agents;
        unsigned int Iterations;
        bool Parallelizable;
        bool Parallelable;
        std::vector<std::string> IndexBefore;
        bool IndexRunning;
        std::vector<std::string> ExcludeGlobal;
        std::vector<std::string> ExcludeLocal;
        std::shared_ptr<cruthu::IDLLoader<cruthu::IForma>> Factory;
    };

    Cruthu CruthuS;
    ITera Tera;
    ITeraGen TeraGen;
    std::vector<IIndexer> Indexers;
    std::vector<IForma> Formas;
};
}
#endif
