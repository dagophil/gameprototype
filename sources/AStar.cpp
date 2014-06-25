/*
 * AStar.cpp
 *
 */

#include "AStar.h"

// TODO: Move function implementations from AStar.h to here.


AStar::AStar (Graph* g, Graph::Node* s, Graph::Node* e) {
		graph = g;
		start = s;
		goal = e;
}

void AStar::findPath() {
		SortedList* open = new SortedList(goal);
		SortedList* close = new SortedList(goal);

	    open->add(start);

		Graph::Node* temp = open->getList().back().first;

		while (open->getList().size() > 0) {
			Graph::Node* current_node = open->popNode();

			if (current_node == goal) {
				break;
			}

			std::vector< Graph::Node* > successors = graph->getNeighbors(*current_node);

			for (std::vector<Graph::Node*>::iterator iter = successors.begin(); iter != successors.end(); ++iter) {

			}

		}
}