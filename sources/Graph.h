/*
 * Graph.h
 *
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <OGRE/OgreVector3.h>
#include <map>

/**
 * @class Graph
 * @brief Graph structure
 */
class Graph
{

public: 

    class Node : public Ogre::Vector3
    {

    public:

        Node() {}

        Node(const Ogre::Vector3 & n, Node* parent = 0, float weight = 10e10)
        {
            this->x = n.x;
            this->y = n.y;
            this->z = n.z;
            m_parent = parent;
            m_weight = weight;
        }

        Node* getParent() const {
            return m_parent;
        }

        void setParent(Node* parent) {
            m_parent = parent;
        }

        float getWeight() const {
            return m_weight;
        }

        void setWeight(float weight) {
            m_weight = weight;
        }

    private:

        Node* m_parent;
        float m_weight;

    };

    /**
     * @brief PRECISION precision of rounded double values
     */
    static const unsigned int PRECISION = 4;

    /**
     * @brief constructor
     * @param wayPoints : list of waypoints to build the graph
     */
    Graph(const std::vector<Ogre::Vector3> & wayPoints);

    /**
     * @brief destructor
     */
    ~Graph();

    /**
     * @brief getNeighbors get the neighbor nodes of the given node
     * @param v : neighbor
     * @return neighbors of v
     */
    const std::vector<Node*> & getNeighbors(const Node & v);

    /**
     * @brief getNearestNode finds the nearest node of p
     * @param p : the vector3 to find the nearest node of
     * @return nearest node of p
     */
    const Node & getNearestNode(const Ogre::Vector3 & p);

    /**
     * @brief getNodes
     * @return
     */
    const std::vector<Node> & getNodes();

    /**
     * @brief resets the nodes (parents and weights)
     */
    void resetNodes();

private:

    /**
     * @brief findIndex construct map index of a node
     * @param node
     * @return map index of node
     */
    std::vector<long> findIndex(const Node & node);

    std::vector<Node> m_nodes;
    std::map<std::vector<long> , std::vector<Node*> > m_neighbors;

};

#endif /* GRAPH_H_ */

