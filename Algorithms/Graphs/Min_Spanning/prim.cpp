#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using pii = std::pair<int, int>;

class PrimMST {
public:
  PrimMST(int vertices) : V(vertices) { adj.resize(V); }

  void addEdge(int u, int v, int weight) {
    adj[u].emplace_back(v, weight);
    adj[v].emplace_back(u, weight);
  }

  int findMST() {
    int totalWeight = 0;
    std::vector<bool> inMST(V, false);
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq; // {weight, vertex}

    // Start from vertex 0
    pq.push({0, 0});

    while (!pq.empty()) {
      int u = pq.top().second;
      int weight = pq.top().first;
      pq.pop();

      if (inMST[u])
        continue;

      inMST[u] = true;
      totalWeight += weight;

      for (const auto &edge : adj[u]) {
        int v = edge.first;
        int w = edge.second;
        if (!inMST[v]) {
          pq.push({w, v});
        }
      }
    }

    return totalWeight;
  }

private:
  int V;                   // Number of vertices
  std::vector<std::vector<pii>> adj; // Adjacency list
};

int main() {
  int V = 5; // Number of vertices
  PrimMST graph(V);

  // Adding edges with weights
  graph.addEdge(0, 1, 2);
  graph.addEdge(0, 3, 6);
  graph.addEdge(1, 2, 3);
  graph.addEdge(1, 3, 8);
  graph.addEdge(1, 4, 5);
  graph.addEdge(2, 4, 7);
  graph.addEdge(3, 4, 9);

  int totalWeight = graph.findMST();
  std::cout << "Total Weight of Minimum Spanning Tree: " << totalWeight << std::endl;

  return 0;
}
