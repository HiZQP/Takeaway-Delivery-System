#pragma once
#include <unordered_map>
#include <vector>
#include <string>

struct MapData {
	std::unordered_map<std::string, int> myMap;//�ص���
	std::vector<std::vector<double>> arcs;//�ڽӾ��� 
	std::vector<std::string> map;//�ص�
};