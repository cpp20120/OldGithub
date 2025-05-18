#include <iostream>
#include <queue>
#include <vector>

template <typename Graph> void bfs(const Graph &graph, std::size_t start) {
  std::vector<bool> visited(graph.size(), false);
  std::queue<std::size_t> queue;

  queue.push(start);

  while (!queue.empty()) {
    std::size_t current = queue.front();
    queue.pop();

    if (!visited[current]) {
      std::cout << "Visited node: " << current << std::endl;
      visited[current] = true;

      for (std::size_t neighbor : graph[current]) {
        if (!visited[neighbor]) {
          queue.push(neighbor);
        }
      }
    }
  }
}

int main() {
  std::vector<std::vector<std::size_t>> graph = {{1, 2}, {0, 3, 4}, {0, 5},
                                                 {1},    {1},       {2}};

  bfs(graph, 0);

  return 0;
}
