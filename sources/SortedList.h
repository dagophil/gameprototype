#ifndef SORTEDLIST_H_
#define SORTEDLIST_H_

#include <vector>

#include "Graph.h"

/**
 * @class SortedList
 * @brief SortedList for nodes
 */

class SortedList{

public:

    typedef std::pair<Graph::Node*, float> NodeDistPair;

    SortedList();

    void add(Graph::Node* node, float weight);

    Graph::Node* popNode();

    const std::vector<NodeDistPair> & getList();

    int getIndex(const Graph::Node & node);

    void remove_at(size_t i);

private:

    std::vector<NodeDistPair> m_list;

};


#endif /* SORTEDLIST_H_ */
