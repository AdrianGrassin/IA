#include <iostream>
#include "graph.h"

int main(int argc, char *argv[]) {

  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <input_file>" << std::endl;
    return 0;
  }

  std::ifstream file(argv[1]);
  if (!file) {
    std::cout << "File " << argv[1] << " does not exist." << std::endl;
    return 0;
  }

  Graph G(file);
  G.print();
  int v1 = 0;
  int v2 = 0;
  std::cout << "Introduce dos nodos del grafo del 1 al " << G.getNumVertex() << ":" <<std::endl;
  std::cin >> v1 >> v2;
  std::cout << std::endl;
  G.bfs(v1 - 1, v2 - 1);
  std::cout << std::endl;
  G.dijkstra(v1 - 1, v2 - 1);

  return 0;
}
