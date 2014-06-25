#ifndef ASTAR_H_
#define ASTAR_H_

#include "Graph.h"
#include "SortedList.h"
#include <vector>
#include <OgreVector3.h>
#include <map>

/**
 * @class AStar
 * @brief AStar algorithm to find the shortest path
 */


class AStar{

public: 

	AStar (Graph* g, Graph::Node* s, Graph::Node* e);

	void findPath();

private:

	Graph* graph;
	std::vector<Ogre::Vector3> path;
	Graph::Node* start;
	Graph::Node* goal;
};

#endif /* ASTAR_H_ */
