#ifndef NODE_H
#define NODE_H


#include <utility>
#include "iostream"
#include "memory"

using uchar = unsigned char;

class Node{
public:
    using pointer = std::shared_ptr<Node>;
    [[nodiscard]] int get_freq() const {
        return frequency;
    }

    explicit Node(int freq) : frequency(freq) {}

    void code(std::string& c) {
        code_string = c;
    }
    pointer left{nullptr};
    pointer right{nullptr};
    pointer parent{nullptr};
    Node() = default;
    Node(uchar uch, int f) : ch(uch), frequency(f) {}

    [[nodiscard]] bool is_leaf() const {
        return left == nullptr && right == nullptr;
    }

    [[nodiscard]] uchar get_byte() const{
        return ch;
    }
private:
    uchar ch{0};
    int frequency{0};
    std::string code_string;
};

struct Compar{
    bool operator()(const Node::pointer& a, const Node::pointer& b) const{
        return a->get_freq() > b->get_freq();
    }
};

#endif // NODE_H
