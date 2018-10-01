#ifndef CRUTHU_POINT_HPP
#define CRUTHU_POINT_HPP

#include <memory>

namespace Cruthu {
class Point {
public:
    Point() = default;
    ~Point() = default;

private:
    std::shared_ptr<Cruthu::Point> mAlpha;
    std::shared_ptr<Cruthu::Point> mBeta;
    std::shared_ptr<Cruthu::Point> mGamma;
    std::shared_ptr<Cruthu::Point> mDelta;
    std::shared_ptr<Cruthu::Point> mEpsilon;
};
} // namespace Cruthu
#endif
