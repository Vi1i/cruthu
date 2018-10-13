#ifndef CRUTHU_SETTINGS_HPP
#define CRUTHU_SETTINGS_HPP

#include <string>
#include <vector>

namespace cruthu {
class Settings {
public:
    struct ITera {
        std::string Name;
        std::string LibName;
        std::string LibPath;
        bool SignificantPointIndex;
        bool IndexChain;
    };

    struct ITeraGen {
        std::string Name;
        std::string LibName;
        std::string LibPath;
        bool SignificantPointIndex;
    };

    struct IIndexer {
        std::string Name;
        std::string LibName;
        std::string LibPath;
        bool SignificantPointIndex;
    };

    struct IForma {
        std::string Name;
        std::string LibName;
        std::string LibPath;
    };

    ITera Tera;
    ITeraGen TeraGen;
    std::vector<IIndexer> Indexers;
    std::vector<IForma> Formas;
};
}
#endif
