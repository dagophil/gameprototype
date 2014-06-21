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

	AStar (Graph* g, Ogre::Vector3 s, Ogre::Vector3 e) {
		graph = g;
		start = s;
		goal = e;
	}

	void findPath() {
		SortedList* open = new SortedList(goal);
		SortedList* close = new SortedList(goal);

	    open->add(start);
	}

private:

	Graph* graph;
	std::vector<Ogre::Vector3> path;
	Ogre::Vector3 start;
	Ogre::Vector3 goal;
};

