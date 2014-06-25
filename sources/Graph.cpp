/*
 * Graph.cpp
 *
 */

#include "Graph.h"

Graph::Graph(std::vector<Ogre::Vector3> wayPoints)
{
    typedef std::vector<Node*>::iterator NodeIter;

    for (size_t i=0; i<wayPoints.size(); ++i)
    {
        nodes.push_back(new Node(wayPoints[i]));
    }
    std::cout << "nodes.size() in constructor :  " << nodes.size() << std::endl;

    for (NodeIter iter = nodes.begin(); iter != nodes.end(); ++iter)
    {
        std::vector<Node*> temp;
        for (NodeIter iter2 = nodes.begin(); iter2 != nodes.end(); ++iter2)
        {
            if ( (**iter) != (**iter2) )
            {
                if ( (*iter)->distance(**iter2) <= 3 )
                {
                    temp.push_back(*iter2);
                }
            }
        }
        neighbors.insert( std::pair< std::vector<long>, std::vector<Node*> >(findIndex(**iter), temp) );
    }
}

Graph::~Graph()
{
    nodes.clear();
    neighbors.clear();
}

std::vector< Graph::Node* > Graph::getNeighbors(Graph::Node v)
{
    return neighbors[findIndex(v)];
}

Graph::Node* Graph::getNearestNode(Ogre::Vector3 p)
{
    Graph::Node* current = nodes.front();
    double currentDist = p.distance(*current);
    for (std::vector<Node*>::iterator iter = nodes.begin(); iter != nodes.end(); ++iter) {

       if (currentDist > p.distance(**iter)) {
           current = (*iter);
           currentDist = p.distance(**iter);
       }
    }
    return current;
}

std::vector<Graph::Node*> Graph::getNodes()
{
    return nodes;
}

std::vector<long> Graph::findIndex(Graph::Node node)
{
    std::vector<long> index(3);
    for (int i=0; i<3; ++i)
    {
        index[i] = node[i]*pow((double)10, (double)Graph::PRECISION);
    }
    return index;
}
