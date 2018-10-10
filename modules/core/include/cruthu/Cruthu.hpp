#ifndef CRUTHU_CRUTHU_HPP
#define CRUTHU_CRUTHU_HPP

#include <cruthu/Settings.hpp>

#include <string>

namespace cruthu {
    class  Cruthu {
    public:
    	Cruthu();
    	~Cruthu() = default;

        bool SetConfigFileName(std::string configFileName);
        bool SetConfigFilePath(std::string configFilePath);

        bool Initialize();
        bool Run();
    private:
        std::string mConfigFileName;
        std::string mConfigFilePath;

        bool CreateDefaultConfigFile();
        bool ParseConfig();
        bool FindLibraries();
        cruthu::Settings mSettings;
    };
}
#endif
