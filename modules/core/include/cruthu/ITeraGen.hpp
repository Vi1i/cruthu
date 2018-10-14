#ifndef CRUTHU_ITERAGEN_HPP
#define CRUTHU_ITERAGEN_HPP

#include <cruthu/ITera.hpp>

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/sink.h>

namespace cruthu {
class ITeraGen {
public:
    virtual ~ITeraGen() = default;

    virtual void Create(std::shared_ptr<cruthu::ITera> tera) = 0;
    virtual void SetSink(std::shared_ptr<spdlog::sinks::sink> sink, spdlog::level::level_enum level) = 0;
};
} // namespace cruthu
#endif

