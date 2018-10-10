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
        bool SignificantPointIndex;
        bool IndexChain;
    };

    struct ITeraGen {
        std::string Name;
        std::string LibName;
        bool SignificantPointIndex;
    };

    struct IIndexer {
        std::string Name;
        std::string LibName;
        bool SignificantPointIndex;
    };

    struct IForma {
        std::string Name;
        std::string LibName;
    };

    ITera Tera;
    ITeraGen TeraGen;
    std::vector<IIndexer> Indexers;
    std::vector<IForma> Formas;
};
}
#endif
