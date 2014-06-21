#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <OgreVector3.h>
#include <map>


/**
 * @class Graph
 * @brief Graph structure
 */

class Graph{

	typedef Ogre::Vector3 Node;
	typedef std::vector<Node>::iterator vecIter;

public: 
	Graph (std::vector<Ogre::Vector3> wayPoints) {
		nodes = wayPoints;

		for (vecIter iter = nodes.begin(); iter != nodes.end(); ++iter) {
			std::vector<Node> temp;
			for (vecIter iter2 = nodes.begin(); iter2 != nodes.end(); ++iter2) {
				if ( (*iter) != (*iter2) ) {
					if ( (*iter).distance(*iter2) <= 3 ) {
						temp.push_back(*iter2);
					}
				}
			}

			std::vector<double> index(3);
			for (int i=0; i<3; i++) {
				index[i] = (*iter)[i];
			}
			
			std::pair<std::vector<double>, std::vector<Node> > val(index, temp);
			neighbors.insert(val);
		}

	}

	std::vector<Node> getNeighbors(Node v) {
		std::vector<double> index(3);
		for (int i=0; i<3; i++) {
			index[i] = v[i];
		}
		return neighbors[index];
	}

	Node getNearestNode(Ogre::Vector3 p) {

		std::cout << std::endl;
		std::cout << nodes.size() << std::endl;
		std::cout << std::endl;

		std::cout << nodes.front() << std::endl;

		Node current;
		/*
		for (vecIter iter = nodes.begin(); iter != nodes.end(); ++iter) {
			
			if (p.distance(current) > p.distance((*iter)) ) {
				current = (*iter);
			}
		}
		*/
		return current;
	}

	std::vector<Node> getNodes() {
		return nodes;
	}

private:
	std::vector<Node> nodes;
	std::map< std::vector<double>, std::vector<Node> > neighbors;


};

#endif /* GRAPH_H_ */

