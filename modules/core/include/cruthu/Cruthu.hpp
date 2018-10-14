#ifndef CRUTHU_CRUTHU_HPP
#define CRUTHU_CRUTHU_HPP

#include <cruthu/Settings.hpp>

#include <string>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/sink.h>

namespace cruthu {
class  Cruthu {
public:
	//Cruthu();
    Cruthu(std::shared_ptr<spdlog::sinks::sink> sink, spdlog::level::level_enum level);
	~Cruthu();

    bool SetConfigFileName(std::string configFileName);
    bool SetConfigFilePath(std::string configFilePath);

    bool Initialize();
    void Run();
private:
    std::string mConfigFileName;
    std::string mConfigFilePath;
    std::shared_ptr<spdlog::logger> mLogger;
    cruthu::Settings mSettings;

    bool CreateDefaultConfigFile();
    bool ParseConfig();
    bool FindLibraries();
    bool OpenLibraries();
    void CreateImage(std::shared_ptr<cruthu::ITera> tera);
};
}
#endif
