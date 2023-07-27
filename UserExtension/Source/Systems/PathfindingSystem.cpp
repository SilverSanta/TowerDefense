#pragma once

#include "PathfindingSystem.h"
#include "UserExtension.h"
#include "UserBlueprints.h"


struct NodeData
{
	NodeData()
	{
		NodeEntityId = 0;
		OriginNodeEntityId = NULL;

		int G = 0;
		int H = 0;
		int F = 0;
	}
	NodeData(uint64_t nodeentityid, uint64_t originnodeentityid)
	{
		NodeEntityId = nodeentityid;
		OriginNodeEntityId = originnodeentityid;

		int G = 0;
		int H = 0;
		int F = 0;
	}

	uint64_t NodeEntityId;
	uint64_t OriginNodeEntityId;
	int G;
	int H;
	int F;
};

PathfindingSystem::PathfindingSystem(ComponentsManager* componentsmanager, EntitiesManager* entitiesmanager, SystemsManager* systemsmanager)
{
	m_Manager_Entities = entitiesmanager;
	m_Manager_Components = componentsmanager;
	m_Manager_Systems = systemsmanager;
}
PathfindingSystem::~PathfindingSystem() {}


void PathfindingSystem::_Get_NodesFromGameState(std::vector<uint64_t>& m_Nodes)
{
	m_NodesFromGameState = m_Nodes;
}
void PathfindingSystem::_Set_NeighboursForNode_All(std::vector<uint64_t>& m_Nodes)
{
	for (auto& nodefromrepo : m_Nodes)
	{
		Entity* NodeEntityPtr = m_Manager_Entities->_Get_EntityById(nodefromrepo);
		NodeComponent* NodeEntity_NodeComponentPtr = m_Manager_Components->_Get_ComponentPtrFromId(NodeEntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::NODE), m_Manager_Components->m_Components_Node);

		_Set_NeighboursForNode(nodefromrepo, m_Nodes);
	}
}
void PathfindingSystem::_Set_PathForUnitToTargetAndMove(uint64_t AiControlledUnitId, uint64_t StartingNodeId, uint64_t TargetNodeId, std::vector<std::pair<int, int>>& Path)
{
	Entity* UnitEntity_Ptr = m_Manager_Entities->_Get_EntityById(AiControlledUnitId);
	MovementComponent* UnitMovementPtr = m_Manager_Components->_Get_ComponentPtrFromId(UnitEntity_Ptr->_Get_ComponentIdFromEntityByType(user::ComponentType::MOVEMENT), m_Manager_Components->m_Components_Movement);
	TransformComponent* UnitTransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(UnitEntity_Ptr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);
	StateComponent* UnitStatePtr = m_Manager_Components->_Get_ComponentPtrFromId(UnitEntity_Ptr->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE), m_Manager_Components->m_Components_State);
	UnitMovementPtr->m_MovementPath = Path;
	m_Manager_Systems->m_System_Action->_Action_WalkTo(UnitMovementPtr, UnitTransformPtr, UnitStatePtr, UnitMovementPtr->m_MovementPath.at(0).first, UnitMovementPtr->m_MovementPath.at(0).second);
}
std::pair<bool, int> PathfindingSystem::_Calculate_Path(uint64_t StartingNodeEntityID, uint64_t DestinationNodeEntityID, std::vector<std::pair<int, int>>& path, bool bIsIdealPath, bool bStop1CellBeforeTarget)
{
	// ESTABLISHING INITIAL POSITIONS
	Entity* StartingNodeEntityPtr = m_Manager_Entities->_Get_EntityById(StartingNodeEntityID);
	NodeComponent* StartingNode_NodeComponentPtr = m_Manager_Components->_Get_ComponentPtrFromId(StartingNodeEntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::NODE), m_Manager_Components->m_Components_Node);
	Entity* DestinationNodeEntityPtr = m_Manager_Entities->_Get_EntityById(DestinationNodeEntityID);
	NodeComponent* DestinationNode_NodeComponentPtr = m_Manager_Components->_Get_ComponentPtrFromId(DestinationNodeEntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::NODE), m_Manager_Components->m_Components_Node);


	// CREATION OF MAPS
	std::unordered_map<uint64_t, NodeData>  MapOfOpenNodes;  // KEY: NodeEntityID
	std::unordered_map<uint64_t, NodeData>  MapOfClosedNodes;  // KEY: NodeEntityID


	// IF DESTINATION IS STARTING POINT
	if (StartingNodeEntityID == DestinationNodeEntityID)
	{
		path = std::vector<std::pair<int, int>>();
		return std::make_pair(true, 0);
	}


	// START -> start with the starting node and set booleans
	NodeData StartingNodeData = NodeData(StartingNodeEntityID, 0);
	_Calculate_Costs_GHF(StartingNodeEntityID, DestinationNodeEntityID, nullptr, StartingNodeData.G, StartingNodeData.H, StartingNodeData.F);
	MapOfOpenNodes.insert(std::make_pair(StartingNodeData.NodeEntityId, StartingNodeData));
	bool bDestinationNotReached = true;
	bool bDestinationCanBeReached = true;

	int TotalDistance = 0;
	// ACTUAL LOOP
	while (bDestinationNotReached == true && bDestinationCanBeReached == true)
	{
		NodeData CurrentNodeData;
		_SelectCurrentNodeDataAndDeleteFromOpenList(CurrentNodeData, MapOfOpenNodes);
		MapOfClosedNodes.insert(std::make_pair(CurrentNodeData.NodeEntityId, CurrentNodeData));
		//_ChangeNode_ToClosed(&CurrentNodeData);


		// DESTINATION REACHED
		if (CurrentNodeData.NodeEntityId == DestinationNode_NodeComponentPtr->Get_OwnerId())
		{
			bool bJobIsDone = false;
			NodeData ReversedNodeData = CurrentNodeData;
			TotalDistance = ReversedNodeData.F;
			//_ChangeNode_ToPath(&ReversedNodeData);
			while (bJobIsDone == false)
			{
				Entity* ReversedNodeEntityDataPtr = m_Manager_Entities->_Get_EntityById(ReversedNodeData.NodeEntityId);
				TransformComponent* ReversedNode_TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(ReversedNodeEntityDataPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);

				if (ReversedNodeData.OriginNodeEntityId != NULL)
				{
					if (ReversedNodeData.NodeEntityId != DestinationNodeEntityID || bStop1CellBeforeTarget == false)
					{
						//_ChangeNode_ToPath(&ReversedNodeData);
						path.push_back(std::make_pair((int)ReversedNode_TransformPtr->m_X, (int)ReversedNode_TransformPtr->m_Y));
						ReversedNodeData = _SelectReversedNodeData(ReversedNodeData.OriginNodeEntityId, MapOfClosedNodes);
					}
					else
					{
						ReversedNodeData = _SelectReversedNodeData(ReversedNodeData.OriginNodeEntityId, MapOfClosedNodes);
					}
				}
				else
				{
					//(&ReversedNodeData);
					path.push_back(std::make_pair((int)ReversedNode_TransformPtr->m_X, (int)ReversedNode_TransformPtr->m_Y));
					bJobIsDone = true;
				}
			}

			bDestinationNotReached = false;
		}

		// LOOP CONTINUES
		else
		{
			Entity* CurrentNodeEntityDataPtr = m_Manager_Entities->_Get_EntityById(CurrentNodeData.NodeEntityId);
			NodeComponent* CurrentNodeComponentPtr = m_Manager_Components->_Get_ComponentPtrFromId(CurrentNodeEntityDataPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::NODE), m_Manager_Components->m_Components_Node);
			TransformComponent* CurrentNodeTransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(CurrentNodeEntityDataPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);


			// DIAGONAL AVAILABILITY CHECK ONLY
			bool N_IsAvailable = false;
			bool S_IsAvailable = false;
			bool W_IsAvailable = false;
			bool E_IsAvailable = false;

			for (auto& NeighbourID : CurrentNodeComponentPtr->m_NeighbouringNodesID)
			{
				Entity* NeighbourEntityDataPtr = m_Manager_Entities->_Get_EntityById(NeighbourID);
				NodeComponent* NeighbourNodeComponentPtr = m_Manager_Components->_Get_ComponentPtrFromId(NeighbourEntityDataPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::NODE), m_Manager_Components->m_Components_Node);
				TransformComponent* NeighbourNodeTransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(NeighbourEntityDataPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);

				if (NeighbourNodeComponentPtr->m_bIsPassableByUnits == true || bIsIdealPath == true || NeighbourNodeComponentPtr->Get_OwnerId() == DestinationNodeEntityID)
				{
					mfk::NormalVector2D NormalVectorBetweenNeighbourAndCurrentNode(NeighbourNodeTransformPtr->m_X - CurrentNodeTransformPtr->m_X, NeighbourNodeTransformPtr->m_Y - CurrentNodeTransformPtr->m_Y);

					if (NormalVectorBetweenNeighbourAndCurrentNode.x < -0.9f) { W_IsAvailable = true; }
					else if (NormalVectorBetweenNeighbourAndCurrentNode.x > 0.9f) { E_IsAvailable = true; }
					else if (NormalVectorBetweenNeighbourAndCurrentNode.y < -0.9f) { N_IsAvailable = true; }
					else if (NormalVectorBetweenNeighbourAndCurrentNode.y > 0.9f) { S_IsAvailable = true; }
				}
			}


			// ACTUAL LOOP
			for (auto& NeighbourID : CurrentNodeComponentPtr->m_NeighbouringNodesID)
			{
				Entity* NeighbourEntityDataPtr = m_Manager_Entities->_Get_EntityById(NeighbourID);
				NodeComponent* NeighbourNodeComponentPtr = m_Manager_Components->_Get_ComponentPtrFromId(NeighbourEntityDataPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::NODE), m_Manager_Components->m_Components_Node);
				TransformComponent* NeighbourNodeTransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(NeighbourEntityDataPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);

				bool bIsDirectionallyAcceptable = false;
				mfk::NormalVector2D NormalVectorBetweenNeighbourAndCurrentNode(NeighbourNodeTransformPtr->m_X - CurrentNodeTransformPtr->m_X, NeighbourNodeTransformPtr->m_Y - CurrentNodeTransformPtr->m_Y);

				if (NormalVectorBetweenNeighbourAndCurrentNode.x < -0.9f ||
					NormalVectorBetweenNeighbourAndCurrentNode.x > 0.9f ||
					NormalVectorBetweenNeighbourAndCurrentNode.y < -0.9f ||
					NormalVectorBetweenNeighbourAndCurrentNode.y > 0.9f)
				{
					bIsDirectionallyAcceptable = true; // basically -> this is orthogonal
				}
				else if (NormalVectorBetweenNeighbourAndCurrentNode.x < -0.5f && NormalVectorBetweenNeighbourAndCurrentNode.y < -0.5f && N_IsAvailable == true && W_IsAvailable == true) { bIsDirectionallyAcceptable = true; }
				else if (NormalVectorBetweenNeighbourAndCurrentNode.x < -0.5f && NormalVectorBetweenNeighbourAndCurrentNode.y > +0.5f && S_IsAvailable == true && W_IsAvailable == true) { bIsDirectionallyAcceptable = true; }
				else if (NormalVectorBetweenNeighbourAndCurrentNode.x > 0.5f && NormalVectorBetweenNeighbourAndCurrentNode.y < -0.5f && N_IsAvailable == true && E_IsAvailable == true) { bIsDirectionallyAcceptable = true; }
				else if (NormalVectorBetweenNeighbourAndCurrentNode.x > 0.5f && NormalVectorBetweenNeighbourAndCurrentNode.y > +0.5f && S_IsAvailable == true && E_IsAvailable == true) { bIsDirectionallyAcceptable = true; }
				else
				{
					bIsDirectionallyAcceptable = false;
				}

				if ((NeighbourNodeComponentPtr->m_bIsPassableByUnits == true && bIsDirectionallyAcceptable == true) || bIsIdealPath == true || NeighbourNodeComponentPtr->Get_OwnerId() == DestinationNodeEntityID)
				{
					NodeData NeighbourData = NodeData(NeighbourID, CurrentNodeData.NodeEntityId);
					_Calculate_Costs_GHF(NeighbourID, DestinationNodeEntityID, &CurrentNodeData, NeighbourData.G, NeighbourData.H, NeighbourData.F);

					// (1) Check if neighbouring node is NEW to the open list and is not PRESENT in the closed list
					bool bIsInTheOpenList;
					bool bIsInTheClosedList;

					if (MapOfOpenNodes.find(NeighbourData.NodeEntityId) == MapOfOpenNodes.end()) { bIsInTheOpenList = false; }
					else { bIsInTheOpenList = true; }

					if (MapOfClosedNodes.find(NeighbourData.NodeEntityId) == MapOfClosedNodes.end()) { bIsInTheClosedList = false; }
					else { bIsInTheClosedList = true; }

					// (2) If the neighbouring node IS in the list - check if this path is better (
					if (bIsInTheOpenList == true)
					{
						if (NeighbourData.F < MapOfOpenNodes.at(NeighbourData.NodeEntityId).F)
						{
							MapOfOpenNodes.at(NeighbourData.NodeEntityId) = NeighbourData;
						}
					}
					else if (bIsInTheClosedList == false)
					{
						MapOfOpenNodes.insert(std::make_pair(NeighbourData.NodeEntityId, NeighbourData));
						//_ChangeNode_ToOpen(&NeighbourData);
					}
				}
			}
		}

		// UNREACHABLE
		if (MapOfOpenNodes.size() == 0 && CurrentNodeData.NodeEntityId != StartingNodeData.NodeEntityId) { return std::make_pair(false, NULL); }
	}

	_ReversalOfPath(path);
	//SimplificationOfPath(path);
	return std::make_pair(true, TotalDistance);
}
std::pair<uint64_t, int> PathfindingSystem::_Calculate_PathToBarricade(uint64_t StartingNodeEntityID, uint64_t UnreachableDestinationNodeEntityID, std::vector<std::pair<int, int>>& path, bool bStop1CellBeforeTarget)
{	
	// (1) Calculate ideal path
	std::vector<std::pair<int, int>> IdealPathToTarget;

	std::pair<bool,int> UnreachablePath = _Calculate_Path(StartingNodeEntityID, UnreachableDestinationNodeEntityID, IdealPathToTarget, true, true);

	if (UnreachablePath.first == false)
	{		
		return std::make_pair(false,NULL);
	}	

	// (2) Check collisions along the ideal path with barricades - stop when encountering one of them
	bool bBarricadeNotFound = true;
	int counter = 0;
	uint64_t BarricadeId;
	uint64_t BarricadeNodeId;
	while (counter < IdealPathToTarget.size() && bBarricadeNotFound)
	{
		std::unique_ptr<CollisionComponent> Collider = std::make_unique<CollisionComponent>();		
		{
			Collider->m_CollisionShape = Shape::m_CollisionBox;
			Collider->m_CollisionBox.w = 16;
			Collider->m_CollisionBox.h = 16;
			Collider->m_CollisionBox.x = IdealPathToTarget.at(counter).first - 8;
			Collider->m_CollisionBox.y = IdealPathToTarget.at(counter).second - 8;		
		}
		CollisionComponent* CollisionPtr = &(*Collider);

		std::vector<CollisionComponent*> Collisions = m_Manager_Systems->m_System_Collision->_CollisionList_CollidingComponentsFromLayerToLayer(CollisionPtr, user::CollisionProfile::STRUCTURE, user::CollisionProfile::TRAP);
	
		if (Collisions.size() != 0)
		{
			for (auto& Collision : Collisions)
			{
				Entity* CollidingEntityPtr = m_Manager_Entities->_Get_EntityById(Collision->Get_OwnerId());

				if (CollidingEntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::BARRICADE) != NULL)
				{
					BarricadeId = CollidingEntityPtr->_Get_EntityId();
					bBarricadeNotFound = false;
				}				
			}
		}
		
		counter++;

		Collider.reset();
	}
	if (bBarricadeNotFound)
	{
		return std::make_pair(NULL, NULL);
	}
	else
	{
		// (4) Produce the path
		BarricadeNodeId = _SelectClosestNodefromEntity(BarricadeId, 0);

		Entity* BarricadeNodeEntityPtr = m_Manager_Entities->_Get_EntityById(BarricadeNodeId);
		TransformComponent* BarricadeNode_TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(BarricadeNodeEntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);
		std::pair<bool, int> PathToBarricade = _Calculate_Path(StartingNodeEntityID, BarricadeNodeId, path, true, true);

		return std::make_pair(BarricadeId, PathToBarricade.second);
	}
}

void PathfindingSystem::_Set_NodesUnderTower(std::vector<uint64_t>& NodesUnderTower, uint64_t TowerID)
{
	Entity* TowerEntityPtr = m_Manager_Entities->_Get_EntityById(TowerID);
	CollisionComponent* Tower_CollisionPtr = m_Manager_Components->_Get_ComponentPtrFromId(TowerEntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::COLLISION1), m_Manager_Components->m_Components_Collision);

	std::vector<CollisionComponent*> ListOfColliders = m_Manager_Systems->m_System_Collision->_CollisionList_CollidingComponentsFromLayerToLayer(Tower_CollisionPtr, user::CollisionProfile::NODE, user::CollisionProfile::_NONE);

	for (auto& Collider : ListOfColliders)
	{
		NodesUnderTower.push_back(Collider->m_OwnerId);
	}
	m_TowerNodesFromGameState = NodesUnderTower;
}

uint64_t PathfindingSystem::_SelectClosestNodefromCoordinates(std::pair<int,int> coordinates, int unitvercticaloffsetfromnode)
{	
	int ActualPosition_X = coordinates.first;
	int ActualPosition_Y = coordinates.second - unitvercticaloffsetfromnode;

	uint64_t ClosestNode = m_NodesFromGameState.at(0);
	Entity* ClosestNodeEntity_Ptr = m_Manager_Entities->_Get_EntityById(ClosestNode);
	TransformComponent* ClosestNode_TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(ClosestNodeEntity_Ptr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);

	int ClosestDistanceSqrd = (int)(std::pow(ActualPosition_X - ClosestNode_TransformPtr->m_X, 2) + std::pow(ActualPosition_Y - ClosestNode_TransformPtr->m_Y, 2));

	for (auto& NodeId : m_NodesFromGameState)
	{
		Entity* NodeEntity_Ptr = m_Manager_Entities->_Get_EntityById(NodeId);
		TransformComponent* Node_TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(NodeEntity_Ptr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);

		int NodeDistanceSqrd = (int)(std::pow(ActualPosition_X - Node_TransformPtr->m_X, 2) + std::pow(ActualPosition_Y - Node_TransformPtr->m_Y, 2));

		if (NodeDistanceSqrd < ClosestDistanceSqrd)
		{
			ClosestNode = NodeId;
			ClosestDistanceSqrd = NodeDistanceSqrd;
		}
	}

	return ClosestNode;
}
uint64_t PathfindingSystem::_SelectClosestNodefromEntity(uint64_t EntityID, int unitvercticaloffsetfromnode)
{
	Entity* UnitEntity_Ptr = m_Manager_Entities->_Get_EntityById(EntityID);
	TransformComponent* Unit_TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(UnitEntity_Ptr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);
	int UnitActualPosition_X = Unit_TransformPtr->m_X;
	int UnitActualPosition_Y = Unit_TransformPtr->m_Y - unitvercticaloffsetfromnode;

	uint64_t ClosestNode = m_NodesFromGameState.at(0); 
	Entity* ClosestNodeEntity_Ptr = m_Manager_Entities->_Get_EntityById(ClosestNode);
	TransformComponent* ClosestNode_TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(ClosestNodeEntity_Ptr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);

	int ClosestDistanceSqrd = (int)(std::pow(UnitActualPosition_X - ClosestNode_TransformPtr->m_X, 2) + std::pow(UnitActualPosition_Y - ClosestNode_TransformPtr->m_Y, 2));

	for (auto& NodeId : m_NodesFromGameState)
	{
		Entity* NodeEntity_Ptr = m_Manager_Entities->_Get_EntityById(NodeId);
		TransformComponent* Node_TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(NodeEntity_Ptr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);

		int NodeDistanceSqrd = (int)(std::pow(UnitActualPosition_X - Node_TransformPtr->m_X, 2) + std::pow(UnitActualPosition_Y - Node_TransformPtr->m_Y, 2));

		if (NodeDistanceSqrd < ClosestDistanceSqrd)
		{
			ClosestNode = NodeId;
			ClosestDistanceSqrd = NodeDistanceSqrd;
		}
	}

	return ClosestNode;
}

void PathfindingSystem::_Calculate_Costs_GHF(uint64_t CurrentNodeEntityID, uint64_t DestinationNodeEntityID,NodeData* OriginNode, int& G, int& H, int& F)
{
	Entity* CurrentNodeEntityPtr = m_Manager_Entities->_Get_EntityById(CurrentNodeEntityID);
	TransformComponent* CurrentNodeTransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(CurrentNodeEntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);

	Entity* DestinationNodeEntityPtr = m_Manager_Entities->_Get_EntityById(DestinationNodeEntityID);
	TransformComponent* DestinationTransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(DestinationNodeEntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);
		
	int newG, newH, newF;

	// Calculate G - distance between from START, through ORIGIN and CURRENT
	if (OriginNode == nullptr)
	{
		newG = 0;
	}
	else
	{
		Entity* OriginNodeEntityPtr = m_Manager_Entities->_Get_EntityById(OriginNode->NodeEntityId);
		TransformComponent* OriginNodeTransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(OriginNodeEntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);

		int DistanceG_X = (int)abs(CurrentNodeTransformPtr->m_X - OriginNodeTransformPtr->m_X);
		int DistanceG_Y = (int)abs(CurrentNodeTransformPtr->m_Y - OriginNodeTransformPtr->m_Y);
		int DiagonalGDistance = (int)(std::min(DistanceG_X, DistanceG_Y) * 1.40625f);
		int OrtogonalGDistance = abs(DistanceG_X - DistanceG_Y);
		//std::cout << "ORIGIN NODE: " << OriginNode->NodeEntityId << ", X: " << OriginNode->NodeTransformPtr->X << ", Y: " << OriginNode->NodeTransformPtr->Y << ", CURRENT X: " << CurrentNodeTransformPtr->X << ", Y: " << CurrentNodeTransformPtr->Y << std::endl;
		newG = OriginNode->G + DiagonalGDistance + OrtogonalGDistance;
	}	

	// Calculate H - distance between CURRENT and END
	int Distance_X = (int)abs(CurrentNodeTransformPtr->m_X - DestinationTransformPtr->m_X);
	int Distance_Y = (int)abs(CurrentNodeTransformPtr->m_Y - DestinationTransformPtr->m_Y);
	int DiagonalDistance = (int)(std::min(Distance_X, Distance_Y) * 1.40625f);
	int OrtogonalDistance = abs(Distance_X - Distance_Y);

	newH = DiagonalDistance + OrtogonalDistance;
	
	// Calculate F - sum of G and H
	newF = newG + newH;

	G = newG;
	H = newH;
	F = newF;
}
void PathfindingSystem::_Set_NeighboursForNode(uint64_t NodeEntityID, std::vector<uint64_t>& ListOfNodeEntitiesID)
{
	std::vector<uint64_t> ListOfValidNeighbourEntityID;

	Entity* InspectedNodePtr = m_Manager_Entities->_Get_EntityById(NodeEntityID);
	TransformComponent* InspectedNode_TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(InspectedNodePtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);
	NodeComponent* InspectedNode_NodePtr = m_Manager_Components->_Get_ComponentPtrFromId(InspectedNodePtr->_Get_ComponentIdFromEntityByType(user::ComponentType::NODE), m_Manager_Components->m_Components_Node);

	// create collision component to check!
	std::shared_ptr<CollisionComponent> Node_ExtendedCollider = std::make_shared<CollisionComponent>();
	Node_ExtendedCollider->m_CollisionBox.w = 48;
	Node_ExtendedCollider->m_CollisionBox.h = 48;
	Node_ExtendedCollider->m_CollisionBox.x = (int)InspectedNode_TransformPtr->m_X - 24;
	Node_ExtendedCollider->m_CollisionBox.y = (int)InspectedNode_TransformPtr->m_Y - 24;
	Node_ExtendedCollider->m_CollisionShape = Shape::m_CollisionBox;

	bool N = false, S = false, W = false, E = false;
	std::vector <uint64_t> Buffer;

	for (auto& nodefromrepo : ListOfNodeEntitiesID)
	{
		Entity* NodeEntityPtr = m_Manager_Entities->_Get_EntityById(nodefromrepo);
		CollisionComponent* NodeEntity_CollisionPtr = m_Manager_Components->_Get_ComponentPtrFromId(NodeEntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::COLLISION1), m_Manager_Components->m_Components_Collision);

		bool bCollides = m_Manager_Systems->m_System_Collision->_CollisionCheck(Node_ExtendedCollider, NodeEntity_CollisionPtr);
		if (bCollides && InspectedNodePtr->m_Id != NodeEntityPtr->m_Id)
		{
			Buffer.push_back(NodeEntityPtr->_Get_EntityId());
		}
	}

	// (1) ACCEPT ALL VERTICAL AND HORIZONTAL
	for (auto& BufferEntry : Buffer)
	{
		Entity* BufferEntryNodePtr = m_Manager_Entities->_Get_EntityById(BufferEntry);
		TransformComponent* BufferEntry_TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(BufferEntryNodePtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);

		mfk::NormalVector2D VectorBetweenNodes;
		VectorBetweenNodes.NormalBetweenTwoPoints(InspectedNode_TransformPtr->m_X, InspectedNode_TransformPtr->m_Y, BufferEntry_TransformPtr->m_X, BufferEntry_TransformPtr->m_Y);

		// N
		if (VectorBetweenNodes.y < -0.9 && VectorBetweenNodes.y > -1.1)
		{
			ListOfValidNeighbourEntityID.push_back(BufferEntry);
			N = true;
		}
		// S
		else if (VectorBetweenNodes.y > 0.9 && VectorBetweenNodes.y < 1.1)
		{
			ListOfValidNeighbourEntityID.push_back(BufferEntry);
			S = true;
		}
		// W
		else if (VectorBetweenNodes.x < -0.9 && VectorBetweenNodes.x > -1.1)
		{
			ListOfValidNeighbourEntityID.push_back(BufferEntry);
			W = true;
		}
		// E
		else if (VectorBetweenNodes.x > 0.9 && VectorBetweenNodes.x < 1.1)
		{
			ListOfValidNeighbourEntityID.push_back(BufferEntry);
			E = true;
		}
	}

	// (2) CHECK DIAGONALS
	for (auto& BufferEntry : Buffer)
	{
		Entity* BufferEntryNodePtr = m_Manager_Entities->_Get_EntityById(BufferEntry);
		TransformComponent* BufferEntry_TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(BufferEntryNodePtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);

		mfk::NormalVector2D VectorBetweenNodes;
		VectorBetweenNodes.NormalBetweenTwoPoints(InspectedNode_TransformPtr->m_X, InspectedNode_TransformPtr->m_Y, BufferEntry_TransformPtr->m_X, BufferEntry_TransformPtr->m_Y);

		// NW
		if (VectorBetweenNodes.x < -0.5 && VectorBetweenNodes.y < -0.5 && N == true && W == true)
		{
			ListOfValidNeighbourEntityID.push_back(BufferEntry);
		}
		// NE
		else if (VectorBetweenNodes.x > 0.5 && VectorBetweenNodes.y < -0.5 && N == true && E == true)
		{
			ListOfValidNeighbourEntityID.push_back(BufferEntry);
		}
		// SW
		else if (VectorBetweenNodes.x < -0.5 && VectorBetweenNodes.y > 0.5 && S == true && W == true)
		{
			ListOfValidNeighbourEntityID.push_back(BufferEntry);
		}
		// SE
		else if (VectorBetweenNodes.x > 0.5 && VectorBetweenNodes.y > 0.5 && S == true && E == true)
		{
			ListOfValidNeighbourEntityID.push_back(BufferEntry);
		}
	}

	InspectedNode_NodePtr->m_NeighbouringNodesID = ListOfValidNeighbourEntityID;
}
void PathfindingSystem::_SelectCurrentNodeDataAndDeleteFromOpenList(NodeData& CurrentNodeData, std::unordered_map<uint64_t, NodeData>& MapOfOpenNodeData)
{
	if (MapOfOpenNodeData.size() != 0)
	{
		NodeData CurrentlyBestNodeData = MapOfOpenNodeData.begin()->second;

		for (auto& Entry : MapOfOpenNodeData)
		{
			if (CurrentlyBestNodeData.F == Entry.second.F)
			{
				if (CurrentlyBestNodeData.H > Entry.second.H)
				{
					CurrentlyBestNodeData = MapOfOpenNodeData.at(Entry.first);
				}
			}
			else if (CurrentlyBestNodeData.F > Entry.second.F)
			{
				CurrentlyBestNodeData = MapOfOpenNodeData.at(Entry.first);
			}
		}
		CurrentNodeData = CurrentlyBestNodeData;

		MapOfOpenNodeData.erase(CurrentlyBestNodeData.NodeEntityId);
	}
}
NodeData PathfindingSystem::_SelectReversedNodeData(uint64_t originnodedataid, std::unordered_map<uint64_t, NodeData>& MapOfClosedNodeData)
{
	NodeData NewReversedNodeData;
	bool bNotFound = true;
	uint64_t keytobedeleted;
	while(bNotFound)
	{
		for (auto& Entry : MapOfClosedNodeData)
		{
			if (originnodedataid == Entry.first)
			{
				NewReversedNodeData = MapOfClosedNodeData.at(Entry.first);
				keytobedeleted = Entry.first;
				bNotFound = false;
			}
		}
	}
	MapOfClosedNodeData.erase(keytobedeleted);

	return NewReversedNodeData;
}
void PathfindingSystem::_ReversalOfPath(std::vector<std::pair<int, int>>& Path)
{
	if (Path.size() > 1)
	{
		std::vector<std::pair<int, int>> Buffer;

		for (int i = (int)Path.size() - 1; i >= 0; i--)
		{
			Buffer.push_back(Path.at(i));
		}

		Path = Buffer;
	}
}
void PathfindingSystem::_SimplificationOfPath(std::vector<std::pair<int, int>>& Path)
{
	if(Path.size() > 2)
	{
		std::vector<std::pair<int, int>> BufferPath;

		// include first element
		BufferPath.push_back(Path.at(0));

		//check subsequent objects
		for (int i = 1; i < Path.size() - 1; i++)
		{
			mfk::NormalVector2D BackwardsVector((float)Path.at(i).first - (float)Path.at(i - 1).first, (float)Path.at(i).second - (float)Path.at(i - 1).second);
			mfk::NormalVector2D ForwardsVector((float)Path.at(i + 1).first - (float)Path.at(i).first, (float)Path.at(i + 1).second - (float)Path.at(i).second);

			if (ForwardsVector.x != BackwardsVector.x || ForwardsVector.y != BackwardsVector.y)
			{
				BufferPath.push_back(Path.at(i));
			}
		}
		BufferPath.push_back(Path.at(Path.size()-1));

		Path = BufferPath;
	}
}
void PathfindingSystem::_ChangeNode_ToClosed(NodeData* nodedata)
{
	if (m_Manager_Entities->_Get_EntityById(nodedata->NodeEntityId)->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE) != NULL)
	{
		StateComponent* NodeStatePtr = m_Manager_Components->_Get_ComponentPtrFromId(m_Manager_Entities->_Get_EntityById(nodedata->NodeEntityId)->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE), m_Manager_Components->m_Components_State);
		m_Manager_Systems->m_System_State->_ChangeCurrentState(NodeStatePtr, user::State::IDLE, user::SubState::IDLE_NODE_UNAVAILABLE, user::Direction::Facing_RIGHT);
	}
}
void PathfindingSystem::_ChangeNode_ToOpen(NodeData* nodedata)
{	
	if(m_Manager_Entities->_Get_EntityById(nodedata->NodeEntityId)->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE) != NULL)
	{
		StateComponent* NodeStatePtr = m_Manager_Components->_Get_ComponentPtrFromId(m_Manager_Entities->_Get_EntityById(nodedata->NodeEntityId)->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE), m_Manager_Components->m_Components_State);
		m_Manager_Systems->m_System_State->_ChangeCurrentState(NodeStatePtr, user::State::IDLE, user::SubState::IDLE_NODE_AVAILABLE, user::Direction::Facing_RIGHT);
	}
}
void PathfindingSystem::_ChangeNode_ToPath(NodeData* nodedata)
{
	if (m_Manager_Entities->_Get_EntityById(nodedata->NodeEntityId)->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE) != NULL)
	{
		StateComponent* NodeStatePtr = m_Manager_Components->_Get_ComponentPtrFromId(m_Manager_Entities->_Get_EntityById(nodedata->NodeEntityId)->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE), m_Manager_Components->m_Components_State);
		m_Manager_Systems->m_System_State->_ChangeCurrentState(NodeStatePtr, user::State::IDLE, user::SubState::IDLE_NODE_PATH, user::Direction::Facing_RIGHT);
	}
}
