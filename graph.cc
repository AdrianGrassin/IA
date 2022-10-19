#include "graph.h"

Graph::Graph(std::ifstream &file) {
  file >> num_vertices;
  mat_ad.resize(num_vertices);
  for (int i = 0; i < num_vertices; i++) {
    mat_ad[i].resize(num_vertices);
  }
  for (int i = 0; i < num_vertices; i++) {
    for (int j = i; j < num_vertices; j++) {
      if (i == j) {
        mat_ad[i][j] = 0;
        continue;
      }
      int weight;
      std::string str;
      file >> str;
      weight = std::stoi(str);
      mat_ad[i][j] = weight;
      mat_ad[j][i] = mat_ad[i][j];

    }
  }
}

Graph::~Graph() {
  for (int i = 0; i < num_vertices; i++) {
    mat_ad[i].clear();
  }
  mat_ad.clear();
}

void Graph::print() const {
  std::cout << "Graph G:" << std::endl;

  for (int i = 0; i < num_vertices; i++) {
    for (int j = 0; j < num_vertices; j++) {
      std::cout << std::setw(3) << mat_ad[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void Graph::bfs(int v1, int v2) const {
  if (v1 < 0 || v1 >= num_vertices || v2 < 0 || v2 >= num_vertices) {
    std::cout << "Nodo no valido" << std::endl;
    return;
  }

  std::set<int> visitados;
  std::vector<int> padre(num_vertices, -1);

  std::queue<int> cola;
  int distancia = 0;
  int c_visitados = 0;
  int c_generados = 0;

  // nodo padre
  padre[v1] = v1;
  cola.push(v1);
  while (!cola.empty()) {
    int nodo = cola.front();
    c_visitados++;
    visitados.insert(nodo);
    if (nodo == v2) {
      break;
    }
    for (int i = 0; i < num_vertices; i++) {
      if (mat_ad[nodo][i] != -1 && visitados.count(i) == 0) {
        cola.push(i);
        padre[i] = nodo;
        c_generados++;  // los nodos generados no incluyen repeticiones
      }
    }
    cola.pop();
  }

  int nodo = v2;
  std::stack<int> camino;
  do {
    camino.push(nodo + 1);
    distancia += mat_ad[nodo][padre[nodo]];
    nodo = padre[nodo];

    if (nodo == -1) {
      std::cout << "No hay camino entre los nodos: [" << v1 << "] y [" << v2 << "]" << std::endl;
      return;
    }
  } while ((nodo != v1));
  camino.push(v1 + 1);

  std::string str;
  while (!camino.empty()) {
    str += std::to_string(camino.top());
    camino.pop();
    if (!camino.empty()) {
      str += " -> ";
    }
  }

  std::ofstream file;
  file.open("output.csv", std::ios::app);
  file << v1 + 1 << "," << v2 + 1 << "," <<  str << "," << distancia << "," << c_visitados << "," << c_generados << "," << std::endl;
  file.flush();
  file.close();


  std::cout << std::endl;
  std::cout << "Camino: " << str << std::endl;
  std::cout << "Distancia: " << distancia << std::endl;
  std::cout << "Nodos visitados: " << c_visitados << std::endl;
  std::cout << "Nodos generados: " << c_generados << std::endl;

}

int Graph::getNumVertex() const {
  return num_vertices;
}



