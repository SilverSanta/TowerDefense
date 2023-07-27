#pragma once
#include <iostream>
#include "mfk.h"
#include "UserNamespace.h"
#include <unordered_map>

// FORWARD DECLARATIONS
class EntitiesManager;
class ComponentsManager;
class CameraComponent;
class TransformComponent;
class StateSystem;
class StateComponent;



class ImportAndProcessDataSystem
{
public:
	ImportAndProcessDataSystem(ComponentsManager* componentsmanager, EntitiesManager* entitiesmanager, StateSystem* statesystem);
	~ImportAndProcessDataSystem();


	template<class T>
	static T _InterpretData(char* data, std::unordered_map<char, T>& mapper)
	{
		if (mapper.find(*data) == mapper.end())
		{
			return user::TileType::_ERROR;
		}
		else
		{
			return mapper.at(*data);
		}
	}

	template<class T>
	static int _Get_MatrixVolume(std::vector<std::vector<T>>& matrix)
	{
		int counter = 0;
		for (auto& line : matrix)
		{
			for (auto& position : line)
			{
				counter++;
			}
		}

		return counter;
	}

	template<class T>
	static std::vector<int> _EstablishWaveThreshholds(std::vector<std::vector<T>>& matrix, int numberofportals)
	{
		std::vector<int> Threshholds;
		
	
		int rolling = 0;
		for (auto& line : matrix)
		{
			int counter = 0;

			for (auto& position : line)
			{
				counter++;
			}
			rolling += counter * numberofportals;

			Threshholds.push_back(rolling);
		}

		return Threshholds;
	}

	static std::vector<std::vector<char>> _CellData(std::vector<std::vector<char>> originaldata);
	static void _IntroduceBorderBetweenLandAndFlowTiles(std::vector<std::vector<char>>& data, std::unordered_map<char, user::TileType> mapper);
	static void _IntroduceMountainSmoothing(std::vector<std::vector<char>>& celldata, std::unordered_map<char, user::TileType> mapper);
	static std::vector<int> _ImportDataVectorFromTextFile(std::string filepath);
	static std::vector<std::vector<char>> _ImportMatrixFromTextFile(std::string filepath);
	void _PrintData(std::vector<std::vector<char>>& data);
	int _Get_NumberOfLevels();

	static bool _IsWater(user::TileType Type);
	static bool _IsLand(user::TileType Type);

	static int _Get_Position(int row, int column, int rowwidth);
	static int _Get_Row(int position, int rowwidth);
	static int _Get_Column(int position, int rowwidth);


private:
	EntitiesManager* m_Manager_Entities;
	ComponentsManager* m_Manager_Components;
	StateSystem* m_System_State;
};
