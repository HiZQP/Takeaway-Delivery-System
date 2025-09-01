#pragma once
#include<iostream> 
#include <algorithm>
#include <climits>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <QObject>

#include "MapData.h"

struct ShortestPath {
	std::string path;
	float pathLength;
};

class Map : public QObject{
	Q_OBJECT

private:
	MapData m_mapData;
	std::vector<std::vector<int>> m_path;//路径前驱节点矩阵
	std::vector<std::vector<double>>m_D;//路径最短长度矩阵
	
public:
	Map();
	void loadMap(MapData mapData);
	ShortestPath floyd(std::string start, std::string end);
};

