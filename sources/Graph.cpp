/*
 * Graph.cpp
 *
 */

#include "Graph.h"

Graph::Graph(const std::vector<Ogre::Vector3> & wayPoints)
{
    typedef std::vector<Node>::iterator NodeIter;
    typedef std::pair<std::vector<long>, std::vector<Node*> > IndexNeighborPair;

    // Add the waypoints to the node list.
    for (size_t i=0; i<wayPoints.size(); ++i)
    {
        m_nodes.push_back(Node(wayPoints[i], 0));
    }
    std::cout << std::endl << "nodes.size() in constructor :  " << m_nodes.size() << std::endl << std::endl;

    // Find the neighbors of each node.
    for (NodeIter iter = m_nodes.begin(); iter != m_nodes.end(); ++iter)
    {
        std::vector<Node*> neighbors;
        for (NodeIter iter2 = m_nodes.begin(); iter2 != m_nodes.end(); ++iter2)
        {
            if ( (*iter) != (*iter2) )
            {
                if ((*iter).distance(*iter2) <= 3)
                {
                    neighbors.push_back(&(*iter2));
                }
            }
        }
        m_neighbors.insert(IndexNeighborPair(findIndex(*iter), neighbors));
    }
}

Graph::~Graph() {}

const std::vector<Graph::Node*> & Graph::getNeighbors(const Graph::Node & v)
{
    return m_neighbors[findIndex(v)];
}

const Graph::Node & Graph::getNearestNode(const Ogre::Vector3 & p)
{
    size_t nearest = 0;
    float currentDist = p.distance(m_nodes[0]);
    for (size_t i = 1; i < m_nodes.size(); ++i)
    {
        if (currentDist > p.distance(m_nodes[i]))
        {
            nearest = i;
            currentDist = p.distance(m_nodes[i]);
        }
    }
    return m_nodes.at(nearest);
}

const std::vector<Graph::Node> & Graph::getNodes()
{
    return m_nodes;
}

std::vector<long> Graph::findIndex(const Graph::Node & node)
{
    std::vector<long> index(3);
    for (int i=0; i<3; ++i)
    {
        index[i] = node[i]*pow((float)10, (float)Graph::PRECISION);
    }
    return index;
}
