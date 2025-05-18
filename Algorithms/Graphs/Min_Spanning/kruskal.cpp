#include <algorithm>
#include <iostream>
#include <vector>


using edge = std::pair<int, std::pair<int, int>>;

class KruskalMST {
public:
  KruskalMST(int vertices) : V(vertices) { edges.clear(); }

  void addEdge(int u, int v, int weight) { edges.push_back({weight, {u, v}}); }

  int findMST() {
    int totalWeight = 0;
    std::sort(edges.begin(), edges.end());

    std::vector<int> parent(V);
    for (int i = 0; i < V; ++i)
      parent[i] = i;

    for (const auto &e : edges) {
      int u = e.second.first;
      int v = e.second.second;
      int weight = e.first;

      int setU = findSet(u, parent);
      int setV = findSet(v, parent);

      if (setU != setV) {
        totalWeight += weight;
        unionSets(setU, setV, parent);
      }
    }

    return totalWeight;
  }

private:
  int V;              // Number of vertices
  std::vector<edge> edges; // Edges with weights

  int findSet(int u, std::vector<int> &parent) {
    while (u != parent[u])
      u = parent[u];
    return u;
  }

  void unionSets(int u, int v, std::vector<int> &parent) { parent[u] = v; }
};

int main() {
  int V = 5; // Number of vertices
  KruskalMST graph(V);

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
