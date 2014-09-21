/*
 * AStar.cpp
 *
 */

#include "AStar.h"
#include "SortedList.h"

AStar::AStar (Graph* graph)
    : m_graph(graph)
{}

std::vector<Graph::Node> AStar::findPath(Graph::Node start, Graph::Node goal)
{
    typedef Graph::Node Node;

    // Reset the nodes.
    m_graph->resetNodes();
    start.setParent(0);
    start.setWeight(0);
    goal.setParent(0);
    goal.setWeight(10e10);

    // Create open and closed list.
    SortedList open;
    std::vector<Graph::Node*> close;
    open.add(&start, goal.distance(start));

    while (!open.getList().empty())
    {
        // Get node with smallest heuristic distance to goal and remove it from open list.
        Node* current_node = open.popNode();

        // Check if the goal was reached.
        if (current_node->distance(goal) < 1)
        {
            goal.setParent(current_node->getParent());
            break;
        }

        // Add current node to closed list (weight is not important in closed list).
        close.push_back(current_node);

        // Get the neighbors.
        const std::vector<Node*> & neighbors = m_graph->getNeighbors(*current_node);
        for (std::vector<Node*>::const_iterator iter = neighbors.begin(); iter != neighbors.end(); ++iter)
        {
            Node* neighbor = *iter;

            // Neighbors in the closed list are already finished.
            int cFound = -1;
            for (size_t i = 0; i < close.size(); ++i) {
                if (*(close[i]) == *neighbor) {
                    cFound = i;
                    break;
                }
            }


            //int cFound = close.getIndex(*neighbor);
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
                    open.add(neighbor, heuristicDist + goal.distance(*neighbor));
                }
            }
        }
    }

    // Create the vector with the shortest path.
    std::vector<Graph::Node> solution;
    Graph::Node* p = &goal;
    while ( p != 0 )
    {
        solution.push_back(*p);
        p = p->getParent();
    }
	
    return solution;
}
