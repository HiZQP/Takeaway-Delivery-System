#pragma once
#include <unordered_map>
#include <vector>
#include <string>

struct MapData {
	std::unordered_map<std::string, int> myMap;//地点编号
	std::vector<std::vector<double>> arcs;//邻接矩阵 
	std::vector<std::string> map;//地点
};