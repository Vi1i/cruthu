#ifndef CRUTHU_IFORMA_HPP
#define CRUTHU_IFORMA_HPP

#include <cruthu/ITera.hpp>

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/sink.h>

namespace cruthu {
class IForma {
public:
    virtual ~IForma() = default;

    virtual void Modify(std::shared_ptr<cruthu::ITera> tera) = 0;
    virtual void Step(std::shared_ptr<cruthu::ITera> tera) = 0;
    virtual void SetSink(std::shared_ptr<spdlog::sinks::sink> sink, spdlog::level::level_enum level) = 0;
    virtual void SetSeed(unsigned int seed);

protected:
    std::shared_ptr<spdlog::logger> mLogger;
    unsigned int mSeed;
};
} // namespace cruthu
#endif

