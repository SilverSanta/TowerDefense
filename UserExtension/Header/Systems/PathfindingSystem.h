#pragma once
#include <iostream>
#include "mfk.h"
#include "UserNamespace.h"
#include <unordered_map>
#include <vector>

// FORWARD DECLARATIONS
class EntitiesManager;
class ComponentsManager;
class NodeComponent;
class SystemsManager;
struct SDL_Renderer;
struct NodeData;
class TransformComponent;


class PathfindingSystem
{
public:
	PathfindingSystem(ComponentsManager* componentsmanager, EntitiesManager* entitiesmanager, SystemsManager* systemsmanager);
	~PathfindingSystem();

	void _Get_NodesFromGameState(std::vector<uint64_t>& m_Nodes);
	void _Set_NeighboursForNode_All(std::vector<uint64_t>& m_Nodes);
	void _Set_PathForUnitToTargetAndMove(uint64_t AiControlledUnitId, uint64_t StartingNodeId, uint64_t TargetNodeId, std::vector<std::pair<int,int>>&Path);
	std::pair<bool, int> _Calculate_Path(uint64_t StartingNodeEntityID, uint64_t DestinationNodeEntityID, std::vector<std::pair<int, int>>& path, bool bIsIdealPath, bool bStop1CellBeforeTarget);
	std::pair<uint64_t, int> _Calculate_PathToBarricade(uint64_t StartingNodeEntityID, uint64_t UnreachableDestinationNodeEntityID, std::vector<std::pair<int, int>>& path, bool bStop1CellBeforeTarget);
	uint64_t _SelectClosestNodefromCoordinates(std::pair<int, int> coordinates, int unitvercticaloffsetfromnode);
	uint64_t _SelectClosestNodefromEntity(uint64_t EntityID, int unitvercticaloffsetfromnode);
	

private:
	void _Set_NodesUnderTower(std::vector<uint64_t>& NodesUnderTower, uint64_t TowerID);
	void _Set_NeighboursForNode(uint64_t NodeID, std::vector<uint64_t>& m_Nodes);
	void _Calculate_Costs_GHF(uint64_t CurrentNodeEntityID, uint64_t DestinationNodeEntityID, NodeData* OriginNode, int& G, int& H, int& F);
	
	void _SelectCurrentNodeDataAndDeleteFromOpenList(NodeData& CurrentNodeData, std::unordered_map<uint64_t, NodeData>& MapOfOpenNodeData);
	NodeData _SelectReversedNodeData(uint64_t originnodedataid, std::unordered_map<uint64_t, NodeData>& MapOfClosedNodeData);

	void _ReversalOfPath(std::vector<std::pair<int, int>>& Path);
	void _SimplificationOfPath(std::vector<std::pair<int, int>>& Path);


	void _ChangeNode_ToClosed(NodeData* nodedata);
	void _ChangeNode_ToOpen(NodeData* nodedata);
	void _ChangeNode_ToPath(NodeData* nodedata);


private:
	std::vector<uint64_t> m_NodesFromGameState;
	std::vector<uint64_t> m_TowerNodesFromGameState;

	EntitiesManager* m_Manager_Entities;
	ComponentsManager* m_Manager_Components;
	SystemsManager* m_Manager_Systems;	
};
