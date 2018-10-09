#ifndef CRUTHU_POINT_HPP
#define CRUTHU_POINT_HPP

#include <string>
#include <memory>
#include <vector>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

namespace Cruthu {
class Point {
public:
    Point() : mTag(boost::uuids::random_generator()()) {};
    Point(Cruthu::Point const & rhs) : mTag(rhs.mTag), mNeighbors(rhs.mNeighbors) {};
    ~Point() = default;

    boost::uuids::uuid GetTag();
    bool operator==(Cruthu::Point const& rhs) const;
    void operator=(Cruthu::Point const& rhs);

    void SetNeighbor(std::shared_ptr<Cruthu::Point> neighbor);
    bool RemoveNeighbor(std::shared_ptr<Cruthu::Point> neighbor);
    std::vector<std::shared_ptr<Cruthu::Point>> GetNeighbors();
    std::shared_ptr<Cruthu::Point> GetSignificantPoint();

private:
    boost::uuids::uuid mTag;
    std::vector<std::shared_ptr<Cruthu::Point>> mNeighbors;
};
} // namespace Cruthu
#endif
