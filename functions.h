#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "vector"
#include "queue"
#include "Node.h"


using std::vector;
using std::priority_queue;

using queue_t = priority_queue<Node::pointer, vector<Node::pointer>, Compar>;

void build_tree(queue_t& queue);

void fill_queue(vector<long long int>& frequency, queue_t& queue);


#endif // FUNCTIONS_H
