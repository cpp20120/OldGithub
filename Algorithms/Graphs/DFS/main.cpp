#include <iostream>
#include <stack>
#include <vector>

template <typename Graph> void dfs(const Graph &graph, std::size_t start) {
  std::vector<bool> visited(graph.size(), false);
  std::stack<std::size_t> stack;

  stack.push(start);

  while (!stack.empty()) {
    std::size_t current = stack.top();
    stack.pop();

    if (!visited[current]) {
      std::cout << "Visited node: " << current << std::endl;
      visited[current] = true;

      for (std::size_t neighbor : graph[current]) {
        if (!visited[neighbor]) {
          stack.push(neighbor);
        }
      }
    }
  }
}

int main() {
  std::vector<std::vector<std::size_t>> graph = {{1, 2}, {0, 3, 4}, {0, 5},
                                                 {1},    {1},       {2}};

  dfs(graph, 0);

  return 0;
}
