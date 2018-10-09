#ifndef CRUTHU_INDEXER_HPP
#define CRUTHU_INDEXER_HPP

#include <cruthu/IIndexer.hpp>
#include <cruthu/Point.hpp>

#include <vector>
#include <memory>
#include <random>

namespace Cruthu {
class Indexer : public IIndexer {
public:
    Indexer() = default;
    ~Indexer() = default;

    virtual std::vector<std::shared_ptr<Cruthu::Point>> Index(std::shared_ptr<Cruthu::Point> point);
    virtual std::vector<std::shared_ptr<Cruthu::Point>> Index(std::vector<std::shared_ptr<Cruthu::Point>> points);
};

extern "C" {
	Cruthu::Indexer * allocator() {
		return new Cruthu::Indexer();
	}

	void deleter(Cruthu::Indexer * ptr) {
		delete ptr;
	}
}
} // namespace Cruthu
#endif
