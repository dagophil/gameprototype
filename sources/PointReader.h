#include <vector>
#include <OgreVector3.h>

#include <fstream>
#include <string>


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
	}

	inline std::vector<Ogre::Vector3> getWayPoints()
	{
		return wayPoints;
	}
	
private:
	std::vector<Ogre::Vector3> wayPoints;
};
