#ifndef CRUTHU_TERA_HPP
#define CRUTHU_TERA_HPP

#include <cruthu/ITera.hpp>
#include <cruthu/IIndexer.hpp>
#include <cruthu/Point.hpp>

#include <vector>
#include <memory>
#include <random>

namespace Cruthu {
class Tera : public ITera {
public:
    Tera() = default;
    ~Tera() = default;

    virtual void SetIndexer(std::shared_ptr<Cruthu::IIndexer> indexer) ;
    virtual void IndexPoints();
    virtual const std::vector<std::shared_ptr<Cruthu::Point>> & GetPoints();
    virtual std::shared_ptr<Cruthu::Point> GetIndexedPoint();

private:
    std::vector<std::shared_ptr<Cruthu::Point>> mPoints;
    std::vector<std::shared_ptr<Cruthu::Point>> mIndexedPoints;

    std::shared_ptr<Cruthu::IIndexer> mIndexer;
};

extern "C" {
	Cruthu::Tera * allocator() {
		return new Cruthu::Tera();
	}

	void deleter(Cruthu::Tera * ptr) {
		delete ptr;
	}
}
} // namespace Cruthu
#endif
