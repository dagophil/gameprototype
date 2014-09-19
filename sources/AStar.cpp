/*
 * AStar.cpp
 *
 */

#include "AStar.h"

AStar::AStar (Graph* graph, const Graph::Node & start, const Graph::Node & goal)
    : m_graph(graph), m_start(start), m_goal(goal)
{}

void AStar::findPath()
{
    typedef Graph::Node Node;

    std::cout << "called findPath()" << std::endl;
    SortedList open;
    SortedList close;

    m_start.setWeight(0);
    open.add(&m_start, m_goal.distance(m_start));

    int c = 0;
    while (!open.getList().empty())
    {
        c++;
        // Get node with smallest heuristic distance to goal and remove it from open list.
        Node* current_node = open.popNode();

        // Check if the goal was reached.
        if (current_node->distance(m_goal) < 1)
        {
            std::cout << "Sie haben das Ziel nach " << c << " Iterationen erreicht!" << std::endl;
            m_goal.setParent(current_node->getParent());
            break;
        }

        // Add current node to closed list (weight is not important in closed list).
        close.add(current_node, 0);

        // Get the neighbors.
        const std::vector<Node*> & neighbors = m_graph->getNeighbors(*current_node);
        for (std::vector<Node*>::const_iterator iter = neighbors.begin(); iter != neighbors.end(); ++iter)
        {
            Node* neighbor = *iter;

            // Neighbors in the closed list are already finished.
            int cFound = close.getIndex(*neighbor);
            if (cFound > 0)
                continue;

            // Compute heuristic distance to goal.
            float heuristicDist = current_node->getWeight() + neighbor->distance(*current_node);

            // Check if a better path was found for the neighbor.
            int oFound = open.getIndex(*neighbor);
            if (oFound == -1 || heuristicDist < neighbor->getWeight())
            {
                neighbor->setParent(current_node);
                neighbor->setWeight(heuristicDist);
                if (oFound == -1)
                {
                    open.add(neighbor, heuristicDist + m_goal.distance(*neighbor));
                }
            }
        }
    }
}

std::vector<Graph::Node> AStar::getPath() {
    std::vector<Graph::Node> solution;
    Graph::Node* p = &m_goal;

    while ( p != 0 )
    {
        solution.push_back(*p);
        std::cout << "p: " << *p << std::endl;
        p = p->getParent();
    }

    std::cout << "Path successfully created." << std::endl;
    return solution;
}
