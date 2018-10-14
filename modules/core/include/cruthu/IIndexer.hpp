#ifndef CRUTHU_IINDEXER_HPP
#define CRUTHU_IINDEXER_HPP

#include <cruthu/ITera.hpp>

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/sink.h>

namespace cruthu {
class IIndexer {
public:
    virtual ~IIndexer() = default;

    virtual void Index(std::shared_ptr<cruthu::ITera> tera) = 0;
    virtual void SetSink(std::shared_ptr<spdlog::sinks::sink> sink, spdlog::level::level_enum level) = 0;
};
} // namespace cruthu
#endif
