#ifndef CRUTHU_ITERA_HPP
#define CRUTHU_ITERA_HPP

#include <cruthu/IIndexer.hpp>
#include <cruthu/Node.hpp>

#include <memory>
#include <vector>

namespace cruthu {
class ITera {
public:
    virtual ~ITera() = 0;

    virtual void SetIndexer(std::shared_ptr<cruthu::IIndexer> indexer) = 0;
    virtual void SetNodes(std::vector<std::shared_ptr<cruthu::Node>> nodes) = 0;
    virtual void SetSignificantNode(std::shared_ptr<cruthu::Node> significantNode) = 0;
    virtual void IndexNodes() = 0;
    virtual const std::vector<std::shared_ptr<cruthu::Node>> & GetNodes() = 0;
    virtual std::shared_ptr<cruthu::Node> GetIndexedNode() = 0;
};
} // namespace cruthu
#endif
