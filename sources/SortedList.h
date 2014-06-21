#ifndef SORTEDLIST_H_
#define SORTEDLIST_H_

#include <vector>
#include <OgreVector3.h>

/**
 * @class SortedList
 * @brief SortedList for nodes
 */

class SortedList{

public: 
	SortedList(Ogre::Vector3 e) {
		goal = e;
	}

	void add(Ogre::Vector3 n) {
		
		double dist = n.distance(goal);

		if (list.size() == 0) {
			list.push_back(std::pair<Ogre::Vector3, double> (n, dist));
		}
		else {
			for (int i = 0; i < list.size(); i++) {
				if (list[i].second < dist) {
					list.insert(list.begin() + i, std::pair<Ogre::Vector3, double> (n, dist));
					break;
				}
				if ( i + 1 == list.size() ) {
					list.push_back(std::pair<Ogre::Vector3, double> (n, dist));
				}
			}
		}
	}

	Ogre::Vector3 popNode() {
		std::pair<Ogre::Vector3, double> temp;
		temp = list.back();
		Ogre::Vector3 temp1 = temp.first;
		list.pop_back();
		return temp1;
	}

	std::vector<std::pair<Ogre::Vector3, double>> getList() {
		return list;
	}

private:
	std::vector<std::pair<Ogre::Vector3, double>> list;
	Ogre::Vector3 goal;

};

#endif SORTEDLIST_H_