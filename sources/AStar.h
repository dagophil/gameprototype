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

    AStar (Graph* graph, const Graph::Node & start, const Graph::Node & goal);

	void findPath();

    std::vector<Graph::Node> getPath();

private:

    Graph* m_graph;
    Graph::Node m_start;
    Graph::Node m_goal;
};

#endif /* ASTAR_H_ */
