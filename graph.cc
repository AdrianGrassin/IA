#include <iomanip>
#include "graph.h"

Graph::Graph(std::ifstream &file) {
  file >> numVertex;
  adjMatrix.resize(numVertex);
  for (int i = 0; i < numVertex; i++) {
    adjMatrix[i].resize(numVertex);
  }
  for (int i = 0; i < numVertex; i++) {
    for (int j = i; j < numVertex; j++) {
      if (i == j) {
        adjMatrix[i][j] = 0;
        continue;
      }
      int weight;
      std::string str;
      file >> str;
      weight = std::stoi(str);
      adjMatrix[i][j] = weight;
      adjMatrix[j][i] = adjMatrix[i][j];

    }
  }
}

Graph::~Graph() {
  for (int i = 0; i < numVertex; i++) {
    adjMatrix[i].clear();
  }
  adjMatrix.clear();
}

void Graph::print() const {
  cout << "Graph G:" << endl;

  for (int i = 0; i < numVertex; i++) {
    for (int j = 0; j < numVertex; j++) {
      cout << setw(3) << adjMatrix[i][j] << " ";
    }
    cout << endl;
  }
}

void Graph::bfs(int v1, int v2) const {
  if (v1 < 0 || v2 < 0 || v1 >= numVertex || v2 >= numVertex) {
    cout << "Invalid vertex" << endl;
    return;
  }

  vector<int> visited(numVertex, 0);
  vector<int> parent(numVertex, -1);
  vector<int> cost(numVertex, 0);
  queue<int> q;
  q.push(v1);
  visited[v1] = 1;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < numVertex; i++) {
      if (adjMatrix[u][i] != -1 && visited[i] == 0) {
        q.push(i);
        visited[i] = 1;
        parent[i] = u;
        cost[i] = cost[u] + adjMatrix[u][i];
      }
    }
  }
  if (visited[v2] == 0) {
    cout << "There is no path from " << v1 + 1 << " to " << v2 + 1 << endl;
    return;
  }
  vector<int> path;
  int u = v2;
  while (parent[u] != -1) {
    path.push_back(u);
    u = parent[u];
  }

  path.push_back(v1);
  reverse(path.begin(), path.end());
  cout << "Path: ";
  for (int i : path) {
    cout << "->" <<  i + 1;
  }
  cout << endl;
  cout << "Total cost: " << cost[v2] << endl;

}

int Graph::getNumVertex() const {
  return numVertex;
}



