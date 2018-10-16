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
    struct ITera {
        std::string Name;
        std::string LibName;
        std::string LibPath;
        std::shared_ptr<cruthu::IDLLoader<cruthu::ITera>> Factory;
    };

    struct ITeraGen {
        std::string Name;
        std::string LibName;
        std::string LibPath;
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
        std::string IndexBefore;
        std::shared_ptr<cruthu::IDLLoader<cruthu::IForma>> Factory;
    };

    ITera Tera;
    ITeraGen TeraGen;
    std::vector<IIndexer> Indexers;
    std::vector<IForma> Formas;
};
}
#endif
