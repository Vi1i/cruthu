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
    ~Point() = default;

    boost::uuids::uuid GetTag();
    bool operator==(Cruthu::Point const& rhs) const;

    void SetNeighbor(std::shared_ptr<Cruthu::Point> neighbor);
    std::vector<std::shared_ptr<Cruthu::Point>> GetNeighbors();

private:
    boost::uuids::uuid mTag;
    std::vector<std::shared_ptr<Cruthu::Point>> mNeighbors;
};
} // namespace Cruthu
#endif
