#ifndef OPPONENT_H_
#define OPPONENT_H_

#include "GameMapObject.h"
#include "Graph.h"

/**
 * @class Opponent
 * @brief The Opponent class
 */
class Opponent : public GameObject
{

public:

    /**
     * @brief Opponent
     * @param MeshName name of the mesh
     * @param type of the object
     */
    Opponent(const std::string & MeshName, const ObjectType & type);

    /**
     * @brief CollideWith
     * @param type type of other object
     */
    void CollideWith(const ObjectType & type);

    /**
     * @brief update method, called every frame
     * @param timestep
     */
    void update(const float & timestep);

    /**
    * @brief getter for Object type
    * @return ObjectType
    */
    virtual ObjectType getType();

    /**
     * @brief not used
     */
    virtual void ShowYourself();

    /**
     * @brief plays animaion at collision
     *
     */
    virtual void PlayCollisionAnimation();

    /**
     * @brief converts the vector to the local coordinates
     */
    void translateLocal(const Ogre::Vector3 & dir);

    void findPath();

	/**
     * @brief setter for numOpp
     */
    void setRollSpeed(double speed);

private:

    ObjectType m_type;
	std::vector<Graph::Node> m_path;
	bool m_caught;
	double m_rollSpeed;

};

#endif // OPPONENT_H_
