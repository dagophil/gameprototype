/*
 * SortedList.cpp
 *
 */

#include "SortedList.h"

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

int SortedList::getIndex(Graph::Node* n) {
	
	int index = -1;

	std::cout << list.size() << std::endl;

	for (int i = 0; i < list.size(); i++) {
		if (list[i].first == n) {
			index = i;
		}
	}

	return index;
}

void SortedList::remove(int x) {

	for (int i = 0; i < list.size(); i++) {
		if (i == x) {
			list.erase(list.begin()+(x-1));
		}
	}
}