#ifndef CRUTHU_ITERA_HPP
#define CRUTHU_ITERA_HPP

#include <cruthu/Node.hpp>

#include <memory>
#include <vector>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/sink.h>

namespace cruthu {
class ITera {
public:
    std::vector<std::shared_ptr<cruthu::Node>> Nodes;
    std::vector<std::shared_ptr<cruthu::Node>> IndexedNodes;
    std::shared_ptr<cruthu::Node> SignificantNode;

    virtual ~ITera() = default;

    virtual void SetSink(std::shared_ptr<spdlog::sinks::sink> sink, spdlog::level::level_enum level) = 0;
    virtual std::shared_ptr<cruthu::Node> GetIndexedNode() = 0;
};
} // namespace cruthu
#endif
