/*
 * SortedList.cpp
 *
 */

#include "SortedList.h"

SortedList::SortedList() {}

void SortedList::add(Graph::Node* node, float weight)
{
    if (m_list.empty())
    {
        // The list is empty, so no sorting necessary.
        m_list.push_back(NodeDistPair(node, weight));
    }
    else
    {
        // Find the place to insert the new node using binary search.
        size_t left = 0;
        size_t right = m_list.size()-1;
        while (left != right)
        {
            size_t current = (left+right)/2;
            if (m_list[current].second <= weight)
                right = current;
            else
                left = current+1;
        }
        if (m_list[left].second > weight)
            ++left;

        m_list.insert(m_list.begin() + left, NodeDistPair(node, weight));
    }
}

Graph::Node* SortedList::popNode() {
    Graph::Node* node = m_list.back().first;
    m_list.pop_back();
    return node;
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
