#ifndef CRUTHU_NODE_HPP
#define CRUTHU_NODE_HPP

#include <string>
#include <memory>
#include <vector>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

namespace cruthu {
class Node {
public:
    Node() : mTag(boost::uuids::random_generator()()) {};
    Node(cruthu::Node const & rhs) : mTag(rhs.mTag), mNeighbors(rhs.mNeighbors) {};
    ~Node() = default;

    boost::uuids::uuid GetTag();
    bool operator==(cruthu::Node const& rhs) const;
    void operator=(cruthu::Node const& rhs);

    void SetNeighbor(std::shared_ptr<cruthu::Node> neighbor);
    bool RemoveNeighbor(std::shared_ptr<cruthu::Node> neighbor);
    std::vector<std::shared_ptr<cruthu::Node>> GetNeighbors();
    std::shared_ptr<cruthu::Node> GetSignificantNode();

    void SetHeight(double height);
    double GetHeight();
    std::string to_string();

private:
    boost::uuids::uuid mTag;
    double mHeight;
    std::vector<std::shared_ptr<cruthu::Node>> mNeighbors;
};
} // namespace cruthu
#endif
