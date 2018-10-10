#ifndef CRUTHU_TERA_HPP
#define CRUTHU_TERA_HPP

#include <cruthu/ITera.hpp>
#include <cruthu/IIndexer.hpp>
#include <cruthu/Node.hpp>

#include <vector>
#include <memory>
#include <random>

namespace cruthu {
class Tera : public ITera {
public:
    Tera() : mNodesSet(false), mSignificantNodeSet(false) {};
    ~Tera() = default;

    virtual void SetIndexer(std::shared_ptr<cruthu::IIndexer> indexer) ;
    virtual void SetNodes(std::vector<std::shared_ptr<cruthu::Node>> nodes);
    virtual void SetSignificantNode(std::shared_ptr<cruthu::Node> significantNode);
    virtual void IndexNodes();
    virtual const std::vector<std::shared_ptr<cruthu::Node>> & GetNodes();
    virtual std::shared_ptr<cruthu::Node> GetIndexedNode();

private:
    bool mNodesSet;
    bool mSignificantNodeSet;
    std::shared_ptr<cruthu::Node> mSignificant;
    std::vector<std::shared_ptr<cruthu::Node>> mNodes;
    std::vector<std::shared_ptr<cruthu::Node>> mIndexedNodes;

    std::shared_ptr<cruthu::IIndexer> mIndexer;
};

extern "C" {
	cruthu::Tera * allocator() {
		return new cruthu::Tera();
	}

	void deleter(cruthu::Tera * ptr) {
		delete ptr;
	}
}
} // namespace cruthu
#endif
