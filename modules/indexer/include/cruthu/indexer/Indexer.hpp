#ifndef CRUTHU_INDEXER_HPP
#define CRUTHU_INDEXER_HPP

#include <cruthu/IIndexer.hpp>
#include <cruthu/Node.hpp>

#include <vector>
#include <memory>
#include <random>

namespace cruthu {
class Indexer : public IIndexer {
public:
    Indexer() = default;
    ~Indexer() = default;

    virtual std::vector<std::shared_ptr<cruthu::Node>> Index(std::shared_ptr<cruthu::Node> node);
    virtual std::vector<std::shared_ptr<cruthu::Node>> Index(std::vector<std::shared_ptr<cruthu::Node>> nodes);
};

extern "C" {
	cruthu::Indexer * allocator() {
		return new cruthu::Indexer();
	}

	void deleter(cruthu::Indexer * ptr) {
		delete ptr;
	}
}
} // namespace cruthu
#endif
