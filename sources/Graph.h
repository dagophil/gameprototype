/*
 * Graph.h
 *
 */

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

public: 

    typedef Ogre::Vector3 Node;

    /**
     * @brief PRECISION precision of rounded double values
     */
    static const unsigned int PRECISION = 4;

    /**
     * @brief constructor
     * @param wayPoints : list of waypoints to build the graph
     */
    Graph(std::vector<Ogre::Vector3> wayPoints);

    /**
     * @brief destructor
     */
    ~Graph();

    /**
     * @brief getNeighbors get the neighbor nodes of the given node
     * @param v : neighbor
     * @return neighbors of v
     */
    std::vector<Node*> getNeighbors(Node v);

    /**
     * @brief getNearestNode finds the nearest node of p
     * @param p : the vector3 to find the nearest node of
     * @return nearest node of p
     */
    Node* getNearestNode(Ogre::Vector3 p);

    /**
     * @brief getNodes
     * @return
     */
    std::vector<Node*> getNodes();

private:

    /**
     * @brief findIndex construct map index of a node
     * @param node
     * @return map index of node
     */
    std::vector<long> findIndex(Node node);

    std::vector<Node*> nodes;
    std::map< std::vector<long> , std::vector<Node*> > neighbors;

};

#endif /* GRAPH_H_ */

