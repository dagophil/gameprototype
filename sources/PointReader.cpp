/*
 * PointReader.cpp
 *
 */

#include <fstream>
#include <string>
#include "PointReader.h"

PointReader::PointReader(const char* filename)
{
    FILE* f;
    std::string l;
    char line[80];
    f = fopen(filename,"r");
    if(f == 0)
    {
        fprintf(stderr, "Error reading file: %s\n", filename);
        return;
    }
    Ogre::Vector3 temp;
    while (fgets(line, 80, f))
    {
        temp.x = atof(strtok( line,", "));
        temp.y=0;
        temp.z = atof(strtok( NULL," "));
        wayPoints.push_back(temp);
    }
    graph = new Graph(wayPoints);
}

PointReader::~PointReader()
{
    delete graph;
}

std::vector<Ogre::Vector3> PointReader::getWayPoints()
{
    return wayPoints;
}

Graph* PointReader::getGraph()
{
    return graph;
}
