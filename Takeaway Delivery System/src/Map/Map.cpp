#include "Map.h"
Map::Map()
{
}
void Map::loadMap(MapData mapData) {
	m_mapData = mapData;
}

ShortestPath Map::floyd(std::string start, std::string end) {
	int i{}, j{}, k{};
	
	m_path.resize(m_mapData.map.size(), std::vector<int>(m_mapData.map.size(), -1));
	m_D.resize(m_mapData.map.size(), std::vector<double>(m_mapData.map.size(), INT_MAX));
	std::vector<std::string>path;//Â·¾¶»ØËÝ
	for (i = 0; i < m_mapData.map.size(); i++)
	{
		m_D[i][i] = 0;
	}
	for (i = 0; i < m_mapData.map.size(); i++)
		for (j = 0; j < m_mapData.map.size(); j++)
		{
			if (m_mapData.arcs[i][j] != 0)
			{
				m_D[i][j] = m_mapData.arcs[i][j];
				m_path[i][j] = i;
			}
		}
	for (k = 0; k < m_mapData.map.size(); k++)
		for (i = 0; i < m_mapData.map.size(); i++)
			for (j = 0; j < m_mapData.map.size(); j++)
				if (m_D[i][k] + m_D[k][j] < m_D[i][j])
				{
					m_D[i][j] = m_D[i][k] + m_D[k][j];
					m_path[i][j] = m_path[k][j];
				}
	auto m = m_mapData.myMap.find(start);
	auto n = m_mapData.myMap.find(end);
	float dist = m_D[m->second][n->second];
	int recent = n->second;
	while (recent != -1)
	{
		path.push_back(m_mapData.map[recent]);
		if (recent == m->second)
			break;
		recent = m_path[m->second][recent];
	}
	std::reverse(path.begin(), path.end());
	std::stringstream ss;
	for(size_t i=0;i< path.size();i++)
	{
		if (i > 0)
			ss << "->";
		ss << path[i];
	}
	return { ss.str(), dist };
}