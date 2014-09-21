#ifndef ASTAR_H_
#define ASTAR_H_

#include "Graph.h"
#include "SortedList.h"
#include <vector>
#include <OGRE/OgreVector3.h>
#include <map>

/**
 * @class AStar
 * @brief AStar algorithm to find the shortest path
 */


class AStar{

public: 

    AStar (Graph* graph);

    std::vector<Graph::Node> findPath(Graph::Node start, Graph::Node goal);

private:

    Graph* m_graph;
};

#endif /* ASTAR_H_ */
