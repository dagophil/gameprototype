#include "Opponent.h"
#include "TopManager.h"
#include "GraphicManager.h"
#include "PhysicsManager.h"
#include "MotionState.h"
#include "AStar.h"
#include "Player.h"
#include <OGRE/OgreQuaternion.h>

Opponent::Opponent(const std::string & MeshName, const ObjectType & type)
    : m_type(type), m_caught(false)
{
    Ogre::SceneManager* sceneManager = TopManager::Instance()->getGraphicManager()->getSceneManager();

    // Create the collision model (bounding box)
	std::vector<Ogre::Vector3> waypoints = TopManager::Instance()->getWaypoints();
	int randomstart = rand() % waypoints.size();
	m_SceneNode = sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(2*(waypoints.at(randomstart))));

    //    Ogre::Entity* collEnt = sceneManager->createEntity("boundingBox.mesh");
    //    m_SceneNode->attachObject(collEnt);

    m_SceneNode->yaw(Ogre::Radian(Ogre::Math::PI));
    m_SceneNode->pitch(Ogre::Radian(Ogre::Math::PI/2));

    Ogre::MeshPtr MeshPtr = Ogre::Singleton<Ogre::MeshManager>::getSingletonPtr()->load("Cube.mesh", "Map");
    MeshStrider* Strider = new MeshStrider(MeshPtr.get());
    btCollisionShape* CollisionShape = new btBvhTriangleMeshShape(Strider,true,true);
    btTransform Transform;
    Transform.setIdentity();
    Transform.setOrigin(btVector3(0,0,0));
    btScalar mass(0.);
    btVector3 localInertia(0,0,0);
    MotionState* motionState = new MotionState(Transform, m_SceneNode);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,motionState,CollisionShape,localInertia);
    btRigidBody* body = new btRigidBody(rbInfo);
    body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
    TopManager::Instance()->getPhysicsManager()->getDynamicsWorld()->addRigidBody(body);
    setRigidBody(body);
    setSceneNode(m_SceneNode);
    body->setUserPointer(this);

    // Create the drawing model.
    m_Entity = sceneManager->createEntity(MeshName);
    Ogre::SceneNode* drawNode = m_SceneNode->createChildSceneNode(Ogre::Vector3(0, 0, 0));
    m_Entity->setCastShadows(true);
    drawNode->attachObject(m_Entity);
    drawNode->pitch(-Ogre::Radian(Ogre::Math::PI/2));
    drawNode->yaw(-Ogre::Radian(Ogre::Math::PI));
}

void Opponent::findPath()
{
    // Create path with AStar algorithm
    Ogre::Vector3 position = this->getSceneNode()->getPosition() / 2;

    std::cout << "Start position: " << position << std::endl;

    Graph* graph = TopManager::Instance()->getGraph();
    const Graph::Node & start(graph->getNearestNode(position));
    std::cout << "Start node: " << start << std::endl;

    const std::vector<Graph::Node> & nodes = graph->getNodes();

    // generate random number and goal node
    int random = rand() % nodes.size() + 1;
    const Graph::Node & goal = nodes.at(random);
    std::cout << "Goal node: " << goal << std::endl;

    AStar astar(graph);
    m_path = astar.findPath(start, goal);
}

void Opponent::CollideWith(const ObjectType & type)
{
	this->setY(-50);
	
	if (m_caught == false) {
		Player* player = TopManager::Instance()->getPlayer();
		player->addOpponent();
		m_caught = true;
	}
}

void Opponent::update(const float & timestep)
{
	// Nach rechts drehen.
    this->roll(Ogre::Degree(timestep*100));

    // Get next waypoint and position.
	Graph::Node current_node = m_path.back();
	Ogre::Vector3 position = this->getSceneNode()->getPosition() / 2;
    position.y = 0;

    // Get the movement vector.
    Ogre::Vector3 delta = current_node - position;

    // Next waypoint is close, remove it from the current path.
    if (delta.length() < 2) {
        m_path.pop_back();
    }

    // Scale delta (here: move 4 units per second).
    delta = 4 * delta.normalisedCopy() * timestep;

    // Move.
    translate(delta.x, delta.y, delta.z);

    if (m_path.empty()) {
		findPath();
	}
}

void Opponent::translateLocal(const Ogre::Vector3 & dir)
{
    Ogre::Quaternion quat = m_SceneNode->convertLocalToWorldOrientation(m_SceneNode->getOrientation());
    Ogre::Vector3 vec = quat * dir;
    this->translate(vec.x, vec.y, vec.z);
}

GameObject::ObjectType Opponent::getType()
{
    return m_type;
}

void Opponent::ShowYourself(){}

void Opponent::PlayCollisionAnimation(){}
