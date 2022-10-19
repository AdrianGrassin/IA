//
// Created by grass on 12/10/2022.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <set>
#include <stack>

class Graph {
 public:
  explicit Graph(std::ifstream& file);
  ~Graph();

  void print() const;
  void bfs(int v1, int v2) const;

  int getNumVertex() const;

 private:
  int num_vertices;
  std::vector<std::vector<int>> mat_ad;
};

#endif