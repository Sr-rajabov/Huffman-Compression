#include "functions.h"
#include <algorithm>

#include <iostream>

void fill_queue(vector<long long int>& frequency, queue_t& queue) {
    for_each(frequency.begin(), frequency.end(), [byte = uchar{0}, &queue](const auto& value) mutable {
        if (value != 0) {
            Node::pointer node = std::make_shared<Node>(byte, value);
            queue.push(node);
        }
        ++byte;
    });
}

void build_tree(queue_t& queue) {
    while(queue.size() > 1){
        Node::pointer x = queue.top();
        queue.pop();
        Node::pointer y = queue.top();
        queue.pop();

        Node::pointer z = std::make_shared<Node>(x->get_freq() + y->get_freq());
        z->left = x;
        z->right = y;
        x->parent = z;
        y->parent = z;
        queue.push(z);
    }
}
