#include <vector>
#include <OgreVector3.h>

#include <fstream>
#include <string>

#include "Graph.h"

/**
 * @class PointReader
 * @brief PointReader reads waypoints from a .txt file
 */

class PointReader
{
public:
    PointReader(const char* filename)
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
		
		std::vector<Ogre::Vector3> n = graph->getNeighbors(wayPoints[10]);
		std::cout << std::endl;
		std::cout << wayPoints[10] << std::endl;
		std::cout << std::endl;
		for (std::vector<Ogre::Vector3>::iterator iter = n.begin(); iter != n.end(); ++iter) {
			std::cout << *iter << std::endl;
		}
		std::cout << std::endl;
		

	}

	inline std::vector<Ogre::Vector3> getWayPoints()
	{
		return wayPoints;
	}
	
	virtual ~PointReader() {
		delete graph;
	}

private:
	std::vector<Ogre::Vector3> wayPoints;
	Graph* graph; 
};
