#pragma once

#include "UserNamespace.h"
#include <vector>
#include  <memory>

//FORWARD DECLARATIONS
class EntitiesManager;
class ComponentsManager;
class CollisionComponent;
class UserGameState;
class TransformComponent;

class CollisionSystem
{
public:
	CollisionSystem(ComponentsManager* componentsmanager, EntitiesManager* entitiesmanager);
	~CollisionSystem();
public:
	void _Update_CollisionShapePosition(CollisionComponent* m_CollisionShape, TransformComponent* CameraTransform);
	void _Update_AllCollisionShapePositions(TransformComponent* CameraTransform);
	bool _CollisionCheck_AllFromLayerToLayer(CollisionComponent* object, user::CollisionProfile firstprofile, user::CollisionProfile limitingprofile);
	std::vector<CollisionComponent*> _CollisionList_CollidingComponentsFromLayerToLayer(CollisionComponent* object, user::CollisionProfile firstprofile, user::CollisionProfile limitingprofile);



public:
	bool _CollisionCheck(CollisionComponent* c1, CollisionComponent* c2);
	bool _CollisionCheck(std::unique_ptr<CollisionComponent> c1, CollisionComponent* c2);
	bool _CollisionCheck(std::shared_ptr<CollisionComponent> c1, CollisionComponent* c2);

	void _CollisionCheck_Mouse(CollisionComponent* mousecollisioncomp);

private:
	bool _CollisionCheck_SquareSquare(CollisionComponent* c1, CollisionComponent* c2);
	bool _CollisionCheck_CircleCircle(CollisionComponent* c1, CollisionComponent* c2);
	bool _CollisionCheck_SquareCircle(CollisionComponent* c1, CollisionComponent* c2);





private:
	EntitiesManager* m_Manager_Entities;
	ComponentsManager* m_Manager_Components;
};
