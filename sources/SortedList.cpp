/*
 * SortedList.cpp
 *
 */

#include "SortedList.h"

SortedList::SortedList() {}

void SortedList::add(Graph::Node* node, float weight) {
    if (m_list.empty()) {
        // The list is empty, so no sorting necessary.
        m_list.push_back(NodeDistPair(node, weight));
    }
    else {
        // Find the place to insert the new node.
        for (size_t i = 0; i < m_list.size(); i++) {
            if (m_list[i].second < weight) {
                m_list.insert(m_list.begin() + i, NodeDistPair(node, weight));
                break;
            }
            if ( i + 1 == m_list.size() ) {
                m_list.push_back(NodeDistPair(node, weight));
                break;
            }
        }
    }
}

Graph::Node* SortedList::popNode() {
        NodeDistPair temp = m_list.back();
        m_list.pop_back();
        return temp.first;
}

const std::vector<SortedList::NodeDistPair> & SortedList::getList() {
        return m_list;
}

int SortedList::getIndex(const Graph::Node & node) {
    int index = -1;
    for (size_t i = 0; i < m_list.size(); i++) {
        if (*(m_list[i].first) == node) {
			index = i;
		}
	}
	return index;
}

void SortedList::remove_at(size_t i) {
    m_list.erase(m_list.begin()+i);
}
