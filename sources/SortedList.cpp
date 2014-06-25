/*
 * SortedList.cpp
 *
 */

#include "SortedList.h"

// TODO: Move function implementations from SortedList.h to here.

SortedList::SortedList(Graph::Node* e) {
		goal = e;
}

void SortedList::add(Graph::Node* n) {
		
		double dist = n->distance(*goal);

		if (list.size() == 0) {
			list.push_back(std::pair<Graph::Node*, double> (n, dist));
		}
		else {
			for (int i = 0; i < list.size(); i++) {
				if (list[i].second < dist) {
					list.insert(list.begin() + i, std::pair<Graph::Node*, double> (n, dist));
					break;
				}
				if ( i + 1 == list.size() ) {
					list.push_back(std::pair<Graph::Node*, double> (n, dist));
				}
			}
		}
}

Graph::Node* SortedList::popNode() {
		std::pair<Graph::Node*, double> temp;
		temp = list.back();
		Graph::Node* temp1 = temp.first;
		list.pop_back();
		return temp1;
}

std::vector<std::pair<Graph::Node*, double> > SortedList::getList() {
		return list;
}
