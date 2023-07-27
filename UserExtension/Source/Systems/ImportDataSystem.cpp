#pragma once

#include <fstream>
#include <sstream>

#include "ImportDataSystem.h"
#include "UserExtension.h"


ImportAndProcessDataSystem::ImportAndProcessDataSystem(ComponentsManager* componentsmanager, EntitiesManager* entitiesmanager, StateSystem* statesystem)
{
	m_Manager_Entities = entitiesmanager;
	m_Manager_Components = componentsmanager;
	m_System_State = statesystem;
}
ImportAndProcessDataSystem::~ImportAndProcessDataSystem(){}

void ImportAndProcessDataSystem::_PrintData(std::vector<std::vector<char>>& data)
{
	for (auto& vectorofdata : data)
	{
		for (auto character : vectorofdata)
		{
			std::cout << character;
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}
std::vector<std::vector<char>> ImportAndProcessDataSystem::_ImportMatrixFromTextFile(std::string filepath)
{
	std::vector<std::vector<char>> matrix;

	std::ifstream infile(filepath);

	std::string line;

	while (std::getline(infile, line))
	{
		std::vector<char> thislinetomatrix;
		for (auto& character : line)
		{
			thislinetomatrix.push_back(character);
		}
		matrix.push_back(thislinetomatrix);
	}

	return matrix;
}
std::vector<int> ImportAndProcessDataSystem::_ImportDataVectorFromTextFile(std::string filepath)
{
	std::vector<int> Vector;

	std::ifstream infile(filepath);

	std::string line;

	while (std::getline(infile, line))
	{
		int intvalue = std::stoi(line);
		Vector.push_back(intvalue);
	}

	return Vector;
}
int ImportAndProcessDataSystem::_Get_NumberOfLevels()
{
	int m_NumberOfLevels;
	std::string Path = "Assets/Levels/_Levels.txt";

	std::ifstream infile(Path);
	std::string line;

	while (std::getline(infile, line))
	{
		int intvalue = std::stoi(line);
		m_NumberOfLevels = intvalue;
	}

	return m_NumberOfLevels;
}

std::vector<std::vector<char>> ImportAndProcessDataSystem::_CellData(std::vector<std::vector<char>> originaldata)
{
	std::vector<std::vector<char>> celldata;
		
	for (auto& row : originaldata)
	{
		std::vector<char> newrow;
		for (auto& position : row)
		{
			newrow.push_back(position);
			newrow.push_back(position);
		}
		celldata.push_back(newrow);
		celldata.push_back(newrow);
	}		

	return celldata;
}

void ImportAndProcessDataSystem::_IntroduceBorderBetweenLandAndFlowTiles(std::vector<std::vector<char>>& data, std::unordered_map<char, user::TileType> mapper)
{
	for (int i = 1; i < data.size() - 1; i++)
	{
		for (int j = 1; j < data[i].size() - 1; j++)
		{	
			if(_IsWater(_InterpretData(&data[i][j], mapper)) == true)
			{
				if (_IsLand(_InterpretData(&data[i - 1][j - 1], mapper)) == true) { data[i][j] = '-'; }
				else if (_IsLand(_InterpretData(&data[i - 1][j], mapper)) == true) { data[i][j] = '-'; }
				else if (_IsLand(_InterpretData(&data[i - 1][j + 1], mapper)) == true) { data[i][j] = '-'; }
				else if (_IsLand(_InterpretData(&data[i][j - 1], mapper)) == true) { data[i][j] = '-'; }
				else if (_IsLand(_InterpretData(&data[i][j + 1], mapper)) == true) { data[i][j] = '-'; }
				else if (_IsLand(_InterpretData(&data[i + 1][j - 1], mapper)) == true) { data[i][j] = '-'; }
				else if (_IsLand(_InterpretData(&data[i + 1][j], mapper)) == true) { data[i][j] = '-'; }
				else if (_IsLand(_InterpretData(&data[i + 1][j + 1], mapper)) == true) { data[i][j] = '-'; }
			}
		}
	}	
}
void ImportAndProcessDataSystem::_IntroduceMountainSmoothing(std::vector<std::vector<char>>& celldata, std::unordered_map<char, user::TileType> mapper)
{
	for (int i = 2; i < celldata.size() - 2; i++)
	{
		for (int j = 2; j < celldata[i].size(); j++)
		{
			bool changechar = false;
			if (_InterpretData(&celldata[i][j], mapper) == user::TileType::LAND)
			{
				// M?M
				// ?L?
				// M??
				if (_InterpretData(&celldata[i - 1][j - 1], mapper) == user::TileType::MOUNTAIN && _InterpretData(&celldata[i - 1][j + 1], mapper) == user::TileType::MOUNTAIN && _InterpretData(&celldata[i + 1][j - 1], mapper) == user::TileType::MOUNTAIN)
				{ 
					// -M-					
					// M-L
					// -LL
					if (_InterpretData(&celldata[i - 1][j], mapper) == user::TileType::MOUNTAIN &&
						_InterpretData(&celldata[i][j - 1], mapper) == user::TileType::MOUNTAIN &&
						_InterpretData(&celldata[i][j + 1], mapper) == user::TileType::LAND &&
						_InterpretData(&celldata[i + 1][j], mapper) == user::TileType::LAND &&
						_InterpretData(&celldata[i + 1][j + 1], mapper) == user::TileType::LAND)
					{
						changechar = true;
					}
				}

				// M?M
				// ?L?
				// ??M
				else if(_InterpretData(&celldata[i - 1][j - 1], mapper) == user::TileType::MOUNTAIN && _InterpretData(&celldata[i - 1][j + 1], mapper) == user::TileType::MOUNTAIN && _InterpretData(&celldata[i + 1][j + 1], mapper) == user::TileType::MOUNTAIN)
				{
					// -M-					
					// L-M
					// LL-
					if (_InterpretData(&celldata[i - 1][j], mapper) == user::TileType::MOUNTAIN &&
						_InterpretData(&celldata[i][j - 1], mapper) == user::TileType::LAND &&
						_InterpretData(&celldata[i][j + 1], mapper) == user::TileType::MOUNTAIN &&
						_InterpretData(&celldata[i + 1][j - 1], mapper) == user::TileType::LAND &&
						_InterpretData(&celldata[i + 1][j], mapper) == user::TileType::LAND)
					{
						changechar = true;
					}
				}

				// M??
				// ?L?
				// M?M
				else if (_InterpretData(&celldata[i - 1][j - 1], mapper) == user::TileType::MOUNTAIN && _InterpretData(&celldata[i + 1][j - 1], mapper) == user::TileType::MOUNTAIN && _InterpretData(&celldata[i + 1][j + 1], mapper) == user::TileType::MOUNTAIN)
				{
					// -LL					
					// M-L
					// -M-
					if (_InterpretData(&celldata[i - 1][j], mapper) == user::TileType::LAND &&
						_InterpretData(&celldata[i - 1][j + 1], mapper) == user::TileType::LAND &&
						_InterpretData(&celldata[i][j - 1], mapper) == user::TileType::MOUNTAIN &&
						_InterpretData(&celldata[i][j + 1], mapper) == user::TileType::LAND &&
						_InterpretData(&celldata[i + 1][j], mapper) == user::TileType::MOUNTAIN)
					{
						changechar = true;
					}
				}

				// ??M
				// ?L?
				// M?M
				else if (_InterpretData(&celldata[i - 1][j + 1], mapper) == user::TileType::MOUNTAIN && _InterpretData(&celldata[i + 1][j - 1], mapper) == user::TileType::MOUNTAIN && _InterpretData(&celldata[i + 1][j + 1], mapper) == user::TileType::MOUNTAIN)
				{
					// LL-					
					// L-M
					// -M-
					if (_InterpretData(&celldata[i - 1][j - 1], mapper) == user::TileType::LAND &&
						_InterpretData(&celldata[i - 1][j], mapper) == user::TileType::LAND &&
						_InterpretData(&celldata[i][j - 1], mapper) == user::TileType::LAND &&
						_InterpretData(&celldata[i][j + 1], mapper) == user::TileType::MOUNTAIN &&
						_InterpretData(&celldata[i + 1][j], mapper) == user::TileType::MOUNTAIN)
					{
						changechar = true;
					}
				}
			}

			if (changechar == true)
			{
				celldata[i][j] = 'M';
			}
		}
	}






}

bool ImportAndProcessDataSystem::_IsWater(user::TileType Type)
{
	bool isWater;

	switch (Type)
	{
	case user::TileType::WORLD_EDGE:
	case user::TileType::FLOWING:
	case user::TileType::FLOWING_BORDER:
		isWater = true;
		break;

	default:
		isWater = false;
		break;
	}

	return isWater;
}
bool ImportAndProcessDataSystem::_IsLand(user::TileType Type)
{
	bool isLand;

	switch (Type)
	{
	case user::TileType::LAND:
	case user::TileType::MOUNTAIN:
	case user::TileType::SPAWN_POINT:
	case user::TileType::TOWER:
	case user::TileType::TREE:
		isLand = true;
		break;

	default:
		isLand = false;
		break;
	}

	return isLand;
}

int ImportAndProcessDataSystem::_Get_Position(int row, int column, int rowwidth)
{
	return row * rowwidth + column;
}
int ImportAndProcessDataSystem::_Get_Row(int position, int rowwidth)
{
	return position / rowwidth;
}
int ImportAndProcessDataSystem::_Get_Column(int position, int rowwidth)
{
	return position % rowwidth;
}


