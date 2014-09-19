#ifndef SORTEDLIST_H_
#define SORTEDLIST_H_

#include <vector>
#include <OgreVector3.h>

#include "Graph.h"

/**
 * @class SortedList
 * @brief SortedList for nodes
 */

class SortedList{

public:

    typedef std::pair<Graph::Node, float> NodeDistPair;

    SortedList(const Graph::Node & goal);

    void add(const Graph::Node & node);

    NodeDistPair popNode();

    const std::vector<NodeDistPair> & getList();

    int getIndex(const Graph::Node & node);

    void remove_at(size_t i);

private:

    std::vector<NodeDistPair> m_list;
    Graph::Node m_goal;

};


#endif /* SORTEDLIST_H_ */
