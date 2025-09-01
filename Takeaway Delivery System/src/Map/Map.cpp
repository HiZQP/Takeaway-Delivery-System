#include "Map.h"
Map::Map()
{
}
void Map::loadMap(MapData mapData) {
	m_mapData = mapData;
}

ShortestPath Map::floyd(std::string start, std::string end) {
    // 检查起点和终点是否存在
    auto startIt = m_mapData.myMap.find(start);
    auto endIt = m_mapData.myMap.find(end);

    if (startIt == m_mapData.myMap.end() || endIt == m_mapData.myMap.end()) {
        return { "起点或终点不存在", -1 };
    }

    int startIndex = startIt->second;
    int endIndex = endIt->second;

    // 检查索引是否有效
    if (startIndex < 0 || startIndex >= static_cast<int>(m_mapData.map.size()) ||
        endIndex < 0 || endIndex >= static_cast<int>(m_mapData.map.size())) {
        return { "无效的地点索引", -1 };
    }

    int size = m_mapData.map.size();

    // 初始化距离矩阵和路径矩阵
    m_D.resize(size, std::vector<float>(size, INT_MAX));
    m_path.resize(size, std::vector<int>(size, -1));

    // 初始化对角线
    for (int i = 0; i < size; i++) {
        m_D[i][i] = 0;
    }

    // 初始化直接连接的边
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (m_mapData.arcs[i][j] != 0) {
                m_D[i][j] = m_mapData.arcs[i][j];
                m_path[i][j] = i;
            }
        }
    }

    // Floyd算法核心
    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                // 防止整数溢出
                if (m_D[i][k] != INT_MAX && m_D[k][j] != INT_MAX) {
                    if (m_D[i][k] + m_D[k][j] < m_D[i][j]) {
                        m_D[i][j] = m_D[i][k] + m_D[k][j];
                        m_path[i][j] = m_path[k][j];
                    }
                }
            }
        }
    }

    // 检查路径是否存在
    if (m_D[startIndex][endIndex] == INT_MAX) {
        return { "路径不存在", -1 };
    }

    // 回溯路径
    std::vector<std::string> path;
    int current = endIndex;

    while (current != -1) {
        path.push_back(m_mapData.map[current]);
        if (current == startIndex) {
            break;
        }
        current = m_path[startIndex][current];

        // 防止无限循环
        if (path.size() > size) {
            return { "路径回溯错误", -1 };
        }
    }

    std::reverse(path.begin(), path.end());

    std::stringstream ss;
    for (size_t i = 0; i < path.size(); i++) {
        if (i > 0) {
            ss << "->";
        }
        ss << path[i];
    }

    return { ss.str(), m_D[startIndex][endIndex] };
}