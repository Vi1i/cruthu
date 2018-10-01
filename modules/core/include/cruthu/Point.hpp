#ifndef CRUTHU_POINT_HPP
#define CRUTHU_POINT_HPP

#include <string>
#include <memory>
#include <vector>

namespace Cruthu {
class Point {
public:
    Point() = default;
    ~Point() = default;

    void SetID(unsigned int id);
    unsigned int GetID();

    void SetNeighbor(std::shared_ptr<Cruthu::Point> neighbor);
    std::vector<std::shared_ptr<Cruthu::Point>> GetNeighbors();

private:
    unsigned int mID;
    std::vector<std::shared_ptr<Cruthu::Point>> mNeighbors;
};
} // namespace Cruthu
#endif
