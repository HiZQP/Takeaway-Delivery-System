#pragma once
#include<iostream> 
#include <algorithm>
#include <climits>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>

#include "MapData.h"

struct ShortestPath {
	std::string path;
	float pathLength;
};

class Map {
private:
	MapData m_mapData;
	std::vector<std::vector<int>> m_path;//路径前驱节点矩阵
	std::vector<std::vector<float>>m_D;//路径最短长度矩阵
	
public:
	Map();
	void loadMap(MapData mapData);
	ShortestPath floyd(std::string start, std::string end);
	MapData getMapData() const { return m_mapData; }
};

