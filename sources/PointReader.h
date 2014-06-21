/*
 * PointReader.h
 *
 */

#ifndef POINTREADER_H_
#define POINTREADER_H_

#include <vector>
#include <OgreVector3.h>
#include "Graph.h"

/**
 * @class PointReader
 * @brief PointReader reads waypoints from a .txt file
 */

class PointReader
{
public:

    PointReader(const char* filename);

    std::vector<Ogre::Vector3> getWayPoints();
	
    Graph* getGraph();

    virtual ~PointReader();

private:

	std::vector<Ogre::Vector3> wayPoints;

	Graph* graph; 
};

#endif /* POINTREADER_H_ */
