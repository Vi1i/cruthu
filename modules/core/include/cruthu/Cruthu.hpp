#ifndef CRUTHU_CRUTHU_HPP
#define CRUTHU_CRUTHU_HPP

#include <cruthu/Settings.hpp>

#include <string>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/sink.h>

namespace cruthu {
    class  Cruthu {
    public:
    	Cruthu();
    	~Cruthu() = default;

        bool SetConfigFileName(std::string configFileName);
        bool SetConfigFilePath(std::string configFilePath);
        void SetSink(std::shared_ptr<spdlog::sinks::sink> sink, spdlog::level::level_enum level = spdlog::level::info);

        bool Initialize();
        bool Run();
    private:
        std::string mConfigFileName;
        std::string mConfigFilePath;
        std::shared_ptr<spdlog::logger> mLogger;

        bool CreateDefaultConfigFile();
        bool ParseConfig();
        bool FindLibraries();
        cruthu::Settings mSettings;
    };
}
#endif
