#ifndef CRUTHU_TERA_CORE_HPP
#define CRUTHU_TERA_CORE_HPP

#include "Cruthu/IIndexer.hpp"
#include "Cruthu/Point.hpp"

#include <vector>
#include <memory>
#include <random>

namespace Cruthu {
class Indexer : public IIndexer {
public:
    Indexer() = default;
    ~Indexer() = default;

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

