#ifndef CRUTHU_IINDEXER_HPP
#define CRUTHU_IINDEXER_HPP

#include <cruthu/Node.hpp>

#include <memory>
#include <vector>

namespace cruthu {
class IIndexer {
public:
    virtual ~IIndexer() = 0;
    virtual std::vector<std::shared_ptr<cruthu::Node>> Index(std::shared_ptr<cruthu::Node> node) = 0;
    virtual std::vector<std::shared_ptr<cruthu::Node>> Index(std::vector<std::shared_ptr<cruthu::Node>> nodes) = 0;
};
} // namespace cruthu
#endif
