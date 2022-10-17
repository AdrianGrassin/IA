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
    cout << "Nodo invalido" << endl;
    return;
  }

  std::cout << "BFS desde el nodo " << v1 + 1 << " hasta el nodo " << v2 + 1 << std::endl;

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
    cout << "No hay camino desde el nodo " << v1 + 1 << " hast el nodo " << v2 + 1 << endl;
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
  cout << "Camino encontrado: ";
  for (int i : path) {
    cout << "->" <<  i + 1;
  }
  cout << endl;
  cout << "Coste total: " << cost[v2] << endl;

}

int Graph::getNumVertex() const {
  return numVertex;
}
void Graph::dijkstra(int v1, int v2) const {
    if (v1 < 0 || v2 < 0 || v1 >= numVertex || v2 >= numVertex) {
        cout << "Nodo invalido" << endl;
        return;
    }
    std::cout << "Dijkstra desde el nodo " << v1 + 1 << " hasta el nodo " << v2 + 1 << std::endl;

    vector<int> visited(numVertex, 0);
    vector<int> parent(numVertex, -1);
    vector<int> cost(numVertex, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push(make_pair(0, v1));
    cost[v1] = 0;
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (visited[u] == 1) {
        continue;
        }
        visited[u] = 1;
        for (int i = 0; i < numVertex; i++) {
        if (adjMatrix[u][i] != -1 && visited[i] == 0) {
            if (cost[u] + adjMatrix[u][i] < cost[i]) {
            cost[i] = cost[u] + adjMatrix[u][i];
            parent[i] = u;
            pq.push(make_pair(cost[i], i));
            }
        }
        }
    }
    if (visited[v2] == 0) {
        cout << "No hay camino desde el nodo " << v1 + 1 << " hasta el nodo " << v2 + 1 << endl;
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
    cout << "Camino minimo encontrado: ";
    for (int i : path) {
        cout << "->" <<  i + 1;
    }
    cout << endl;
    cout << "Coste total: " << cost[v2] << endl;

}
void Graph::bellmanFord(int v1, int v2) const {
    if (v1 < 0 || v2 < 0 || v1 >= numVertex || v2 >= numVertex) {
        cout << "Invalid vertex" << endl;
        return;
    }
    std::cout << "Bellman Ford from " << v1 + 1 << " to " << v2 + 1 << std::endl;

    vector<int> parent(numVertex, -1);
    vector<int> cost(numVertex, INT_MAX);
    cost[v1] = 0;
    for (int i = 0; i < numVertex - 1; i++) {
        for (int u = 0; u < numVertex; u++) {
        for (int v = 0; v < numVertex; v++) {
            if (adjMatrix[u][v] != -1) {
            if (cost[u] + adjMatrix[u][v] < cost[v]) {
                cost[v] = cost[u] + adjMatrix[u][v];
                parent[v] = u;
            }
            }
        }
        }
    }
    for (int u = 0; u < numVertex; u++) {
        for (int v = 0; v < numVertex; v++) {
        if (adjMatrix[u][v] != -1) {
            if (cost[u] + adjMatrix[u][v] < cost[v]) {
            cout << "There is a negative cycle" << endl;
            return;
            }
        }
        }
    }
    if (cost[v2] == INT_MAX) {
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




