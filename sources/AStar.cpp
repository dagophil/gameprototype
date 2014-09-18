/*
 * AStar.cpp
 *
 */

#include "AStar.h"

AStar::AStar (Graph* g, Graph::Node* s, Graph::Node* e)
{
		graph = g;
		start = s;
		start->parent = start;
		goal = e;
}

void AStar::findPath()
{
    SortedList* open = new SortedList(goal);
    SortedList* close = new SortedList(goal);

    open->add(start);

    while (open->getList().size() > 0)
    {
        Graph::Node* current_node = open->popNode();
        std::cout << "Current node: " << *current_node << std::endl;

        if (current_node->distance(*goal) < 1)
        {
            std::cout << "Sie haben das Ziel erreicht!" << std::endl << std::endl;
            goal->parent = current_node->parent;
            break;
        }

        const std::vector< Graph::Node* > & successors = graph->getNeighbors(*current_node);
        for (std::vector<Graph::Node*>::const_iterator iter = successors.begin(); iter != successors.end(); ++iter)
        {
            int oFound = open->getIndex(*iter);

            if (oFound > 0)
            {
                std:: pair<Graph::Node*, double> existing_node = open->getList()[oFound];
                if ( existing_node.second <= current_node->distance(*goal) )
                {
                    continue;
                }
            }

            int cFound = close->getIndex(*iter);
            if (cFound > 0)
            {
                std:: pair<Graph::Node*, double> existing_node = close->getList()[cFound];
                if ( existing_node.second <= current_node->distance(*goal) )
                {
                    continue;
                }
            }

            if (oFound != -1)
            {
                open->remove(oFound);
            }
            if (cFound != -1)
            {
                close->remove(cFound);
            }

            std::cout << "Now adding " << **iter << " to open list." << std::endl;
            open->add(*iter);

        }

        close->add(current_node);

        std::cout << "finished one while iteration" << std::endl << std::endl;
    }
    std::cout << "finished findPath()" << std::endl;
}
