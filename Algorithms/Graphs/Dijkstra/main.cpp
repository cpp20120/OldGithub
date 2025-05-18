#include <iostream>
#include <limits>
#include <queue>
#include <vector>

template <typename T>
using AdjacencyList = std::vector<std::vector<std::pair<int, T>>>;

template <typename T> void dijkstra(const AdjacencyList<T> &graph, int start) {
  int n = graph.size();
  std::vector<T> distance(n, std::numeric_limits<T>::max());
  distance[start] = 0;

  std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>,
                      std::greater<>>
      pq;
  pq.push({0, start});

  while (!pq.empty()) {
    auto [dist, node] = pq.top();
    pq.pop();

    if (dist > distance[node])
      continue;

    for (const auto &edge : graph[node]) {
      int neighbor = edge.first;
      T new_dist = dist + edge.second;

      if (new_dist < distance[neighbor]) {
        distance[neighbor] = new_dist;
        pq.push({new_dist, neighbor});
      }
    }
  }

  // Output distances
  for (int i = 0; i < n; ++i) {
    std::cout << "Distance from " << start << " to " << i << ": " << distance[i]
              << std::endl;
  }
}

int main() {
  AdjacencyList<int> graph = {{{1, 4}, {2, 1}}, {{0, 4}, {3, 2}, {4, 5}},
                              {{0, 1}, {5, 3}}, {{1, 2}, {4, 1}},
                              {{1, 5}, {3, 1}}, {{2, 3}, {4, 1}}};

  dijkstra(graph, 0);
  return 0;
}
