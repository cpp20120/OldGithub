#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <algorithm>

struct Node {
    int x, y;
    double f, g, h;
    int parentIndex;  // Index of the parent in the vector

    Node(int x, int y, int parentIndex) : x(x), y(y), f(0), g(0), h(0), parentIndex(parentIndex) {}

    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

double calculateHeuristic(int x, int y, int goalX, int goalY) {
    return std::abs(x - goalX) + std::abs(y - goalY);
}

bool isValid(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

std::vector<std::pair<int, int>> reconstructPath(const std::vector<Node>& nodes, int currentIndex) {
    std::vector<std::pair<int, int>> path;
    while (currentIndex != -1) {
        path.emplace_back(nodes[currentIndex].x, nodes[currentIndex].y);
        currentIndex = nodes[currentIndex].parentIndex;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<std::pair<int, int>> astar(std::vector<std::vector<int>>& grid, int startX, int startY, int goalX, int goalY) {
    int rows = grid.size();
    int cols = grid[0].size();

    std::vector<Node> openSet;
    std::unordered_map<int, int> openSetLookup;
    std::vector<bool> closedSet(rows * cols, false);

    openSet.emplace_back(startX, startY, -1);
    openSetLookup[startX * cols + startY] = 0;

    while (!openSet.empty()) {
        auto currentIt = std::min_element(openSet.begin(), openSet.end(), [](const Node& a, const Node& b) {
            return a.f > b.f;
        });

        Node current = *currentIt;
        openSet.erase(currentIt);
        openSetLookup.erase(current.x * cols + current.y);

        closedSet[current.x * cols + current.y] = true;

        if (current.x == goalX && current.y == goalY) {
            return reconstructPath(openSet, openSet.size() - 1);
        }

        const int dx[] = {1, 0, -1, 0};
        const int dy[] = {0, 1, 0, -1};

        for (int i = 0; i < 4; ++i) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (isValid(newX, newY, rows, cols) && grid[newX][newY] == 0) {
                int neighborKey = newX * cols + newY;
                if (!closedSet[neighborKey]) {
                    double tentativeG = current.g + 1.0;

                    auto it = openSetLookup.find(neighborKey);

                    if (it == openSetLookup.end() || tentativeG < openSet[it->second].g) {
                        Node neighbor(newX, newY, static_cast<int>(openSet.size()) - 1);
                        neighbor.g = tentativeG;
                        neighbor.h = calculateHeuristic(newX, newY, goalX, goalY);
                        neighbor.f = neighbor.g + neighbor.h;

                        if (it != openSetLookup.end()) {
                            openSet[it->second] = neighbor; // Update existing node
                        } else {
                            openSet.push_back(neighbor);
                            openSetLookup[neighborKey] = openSet.size() - 1;
                        }
                    }
                }
            }
        }
    }

    return {};
}

int main() {
    // Example usage
    std::vector<std::vector<int>> grid = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0}
    };

    int startX = 0;
    int startY = 0;
    int goalX = 4;
    int goalY = 4;

    std::vector<std::pair<int, int>> path = astar(grid, startX, startY, goalX, goalY);

    if (path.empty()) {
        std::cout << "No path found.\n";
    } else {
        std::cout << "Path found:\n";
        for (const auto& point : path) {
            std::cout << "(" << point.first << ", " << point.second << ")\n";
        }
    }

    return 0;
}
