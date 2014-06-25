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
	SortedList(Graph::Node* e);

	void add(Graph::Node* n);

	Graph::Node* popNode();

    std::vector<std::pair<Graph::Node*, double> > getList();

private:
    std::vector<std::pair<Graph::Node*, double> > list;
	Graph::Node* goal;

};


#endif /* SORTEDLIST_H_ */
