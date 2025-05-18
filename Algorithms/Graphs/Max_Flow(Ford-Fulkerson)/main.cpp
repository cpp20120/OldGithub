#include <iostream>
#include <limits>
#include <queue>
#include <vector>

struct Edge {
  int to, capacity, flow;
  Edge *residual;

  Edge(int to, int capacity)
      : to(to), capacity(capacity), flow(0), residual(nullptr) {}
};

class MaxFlowGraph {
public:
  MaxFlowGraph(int n) : n(n), adj_list(n) {}

  void addEdge(int from, int to, int capacity) {
    Edge *forward_edge = new Edge(to, capacity);
    Edge *backward_edge = new Edge(from, 0);

    forward_edge->residual = backward_edge;
    backward_edge->residual = forward_edge;

    adj_list[from].push_back(forward_edge);
    adj_list[to].push_back(backward_edge);
  }

  int findMaxFlow(int source, int sink) {
    int max_flow = 0;
    std::vector<Edge *> parent(n);

    while (bfs(source, sink, parent)) {
      int path_flow = std::numeric_limits<int>::max();

      for (int v = sink; v != source; v = parent[v]->residual->to) {
        path_flow = std::min(path_flow, parent[v]->capacity - parent[v]->flow);
      }

      for (int v = sink; v != source; v = parent[v]->residual->to) {
        parent[v]->flow += path_flow;
        parent[v]->residual->flow -= path_flow;
      }

      max_flow += path_flow;
    }

    // Clean up allocated memory
    for (auto &edges : adj_list) {
      for (Edge *edge : edges) {
        delete edge;
      }
    }

    return max_flow;
  }

private:
  int n;
  std::vector<std::vector<Edge *>> adj_list;

  bool bfs(int source, int sink, std::vector<Edge *> &parent) {
    fill(parent.begin(), parent.end(), nullptr);
    std::vector<bool> visited(n, false);
    std::queue<int> q;
    q.push(source);
    visited[source] = true;

    while (!q.empty()) {
      int u = q.front();
      q.pop();

      for (Edge *edge : adj_list[u]) {
        if (!visited[edge->to] && edge->capacity > edge->flow) {
          parent[edge->to] = edge;
          q.push(edge->to);
          visited[edge->to] = true;
        }
      }
    }

    return visited[sink];
  }
};

int main() {
  // Example usage
  int num_nodes = 6;
  MaxFlowGraph graph(num_nodes);

  graph.addEdge(0, 1, 16);
  graph.addEdge(0, 2, 13);
  graph.addEdge(1, 2, 10);
  graph.addEdge(2, 1, 4);
  graph.addEdge(1, 3, 12);
  graph.addEdge(2, 4, 14);
  graph.addEdge(3, 2, 9);
  graph.addEdge(3, 5, 20);
  graph.addEdge(4, 3, 7);
  graph.addEdge(4, 5, 4);

  int source = 0;
  int sink = 5;

  int max_flow = graph.findMaxFlow(source, sink);

  std::cout << "Maximum Flow: " << max_flow << std::endl;

  return 0;
}
