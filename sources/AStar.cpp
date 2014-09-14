/*
 * AStar.cpp
 *
 */

#include "AStar.h"

AStar::AStar (Graph* g, Graph::Node* s, Graph::Node* e) {
		graph = g;
		start = s;
		start->parent = start;
		goal = e;
}

void AStar::findPath() {
		SortedList* open = new SortedList(goal);
		SortedList* close = new SortedList(goal);

	    open->add(start);

		Graph::Node* temp = open->getList().back().first;

		while (open->getList().size() > 0) {
			Graph::Node* current_node = open->popNode();

			if (current_node->distance(*goal) < 1) {
				std::cout << std::endl;
				std::cout << "Sie haben das Ziel erreicht!" << *current_node << std::endl;
				std::cout << *start << std::endl;
				std::cout << std::endl;

				goal->parent = current_node->parent;
				break;
			}

			std::vector< Graph::Node* > successors = graph->getNeighbors(*current_node);

			for (std::vector<Graph::Node*>::iterator iter = successors.begin(); iter != successors.end(); ++iter) {

		//		int oFound = open
			}

		}
}
