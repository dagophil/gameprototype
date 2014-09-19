/*
 * AStar.cpp
 *
 */

#include "AStar.h"

AStar::AStar (Graph* graph, const Graph::Node & start, const Graph::Node & goal)
    : m_graph(graph), m_start(start), m_goal(goal)
{
        m_start.setParent(&m_start);
}

void AStar::findPath()
{
    typedef SortedList::NodeDistPair NodeDistPair;
    typedef Graph::Node Node;

    std::cout << "called findPath()" << std::endl;
    SortedList open(m_goal);
    SortedList close(m_goal);

    open.add(m_start);

    while (!open.getList().empty())
    {
        NodeDistPair current_node = open.popNode();
        //std::cout << "Current node: " << *current_node.first << std::endl;

        if (current_node.first.distance(m_goal) < 1)
        {
            std::cout << "Sie haben das Ziel erreicht!" << std::endl << std::endl;
            m_goal.setParent(current_node.first.getParent());
            break;
        }

        // Create the list with successors.
        const std::vector<Node*> & neighbors = m_graph->getNeighbors(current_node.first);
        for (std::vector<Node*>::const_iterator iter = neighbors.begin(); iter != neighbors.end(); ++iter)
        {
            (*iter)->setParent(current_node.first.getParent());

            int oFound = open.getIndex(**iter);
            if (oFound > 0)
            {
                NodeDistPair existing_node = open.getList()[oFound];
                existing_node.second = current_node.second + current_node.first.distance(**iter);
                if (existing_node.second <= current_node.first.distance(m_goal))
                {
                    continue;
                }
            }

            int cFound = close.getIndex(**iter);
            if (cFound > 0)
            {
                NodeDistPair existing_node = close.getList()[cFound];
                existing_node.second = current_node.second + current_node.first.distance(**iter);
                if (existing_node.second <= current_node.first.distance(m_goal))
                {
                    continue;
                }
            }

            if (oFound != -1)
            {
                open.remove_at(oFound);
            }
            if (cFound != -1)
            {
                close.remove_at(cFound);
            }

            open.add(**iter);
        }

//        std::vector<Node> successors;
//        for (std::vector<Node*>::const_iterator iter = neighbors.begin(); iter != neighbors.end(); ++iter)
//        {
//            successors.push_back(Node(**iter, &(current_node.first)));
//        }

//        for (std::vector<Node>::iterator iter = successors.begin(); iter != successors.end(); ++iter)
//        {
//            int oFound = open.getIndex(*iter);
//            if (oFound > 0)
//            {
//                NodeDistPair existing_node = open.getList()[oFound];
//                existing_node.second = current_node.second + current_node.first.distance(*iter);
//                if (existing_node.second <= current_node.first.distance(m_goal))
//                {
//                    continue;
//                }
//            }

//            int cFound = close.getIndex(*iter);
//            if (cFound > 0)
//            {
//                NodeDistPair existing_node = close.getList()[cFound];
//                existing_node.second = current_node.second + current_node.first.distance(*iter);
//                if (existing_node.second <= current_node.first.distance(m_goal))
//                {
//                    continue;
//                }
//            }

//            if (oFound != -1)
//            {
//                open.remove_at(oFound);
//            }
//            if (cFound != -1)
//            {
//                close.remove_at(cFound);
//            }

//            //std::cout << "Now adding " << **iter << " to open list." << std::endl;
//            open.add(*iter);
//        }

        close.add(current_node.first);

//        std::cout << "finished one while iteration" << std::endl << std::endl;
    }
    std::cout << "finished findPath()" << std::endl;
}

std::vector<Graph::Node> AStar::getPath() {

    std::vector<Graph::Node> solution;
    Graph::Node p = m_goal;

    std::cout << "p: " << p << std::endl;
    std::cout << "parent: " << *p.getParent() << std::endl;


    return solution;

    //    Graph::Node p = m_goal;
    //	int x = 0;
    //	while(x < 10) {
    //		solution.push_back(p);

    //        std::cout << "distance: " << p.distance(m_start) << "  ";
    //        std::cout << "p: " << p << std::endl;
    //        p = *(p.getParent());
    //		x++;

    //	}

    //	return solution;
}

