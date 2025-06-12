#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <queue>
#include <set>
#include "limits.h"
#include <algorithm>

#include "box.hpp"

std::ostream& operator<<(std::ostream& os, const Box& box) {

  os << "TL(" << box.topLeft().first << "," << box.topLeft().second << ")" << "BR("
     << box.bottomRight().first << "," << box.bottomRight().second << ")";

  return os;
}

std::unique_ptr<Box> createBox(std::pair<int, int> tl, std::pair<int, int> br) {
  auto box = std::make_unique<Box>(tl, br);
  return box;
}

void bfs(std::vector<std::unique_ptr<Box>>& results, int startNode,
         std::unordered_map<int, std::vector<int>>& graph, std::set<int>& visited,
         std::vector<std::unique_ptr<Box>>& boxes) {

  std::pair<int, int> TL_MIN{std::make_pair(INT_MAX, INT_MAX)};
  std::pair<int, int> BR_MAX{std::make_pair(INT_MIN, INT_MIN)};

  std::queue<int> q;
  q.push(startNode);
  visited.insert(startNode);

  while (!q.empty()) {

    int node = q.front();
    q.pop();

    // process something here probs getting the max and min tl and br elements

    TL_MIN.first = std::min(TL_MIN.first, boxes[node]->topLeft().first);
    TL_MIN.second = std::min(TL_MIN.second, boxes[node]->topLeft().second);
    BR_MAX.first = std::max(BR_MAX.first, boxes[node]->bottomRight().first);
    BR_MAX.second = std::max(BR_MAX.second, boxes[node]->bottomRight().second);

    for (auto& neighbors : graph[node]) {
      if (visited.find(neighbors) == visited.end()) {
        q.push(neighbors);
        visited.insert(neighbors);
      }
    }
  }

  auto box = createBox(TL_MIN, BR_MAX);
  results.push_back(std::move(box));
}

int main() {

  // create some mock boxes
  auto box1 = std::make_unique<Box>(std::pair{0, 0}, std::pair{2, 2});
  auto box2 = std::make_unique<Box>(std::pair{1, 1}, std::pair{4, 4});
  auto box3 = std::make_unique<Box>(std::pair{5, 2}, std::pair{9, 6});
  auto box4 = std::make_unique<Box>(std::pair{2, 1}, std::pair{11, 4});
  auto box5 = std::make_unique<Box>(std::pair{50, 50}, std::pair{60, 60});

  // store the mock boxes in our input list
  std::vector<std::unique_ptr<Box>> boxes;

  boxes.push_back(std::move(box1));
  boxes.push_back(std::move(box2));
  boxes.push_back(std::move(box3));
  boxes.push_back(std::move(box4));
  boxes.push_back(std::move(box5));

  // create a graph of overlaps
  std::unordered_map<int, std::vector<int>> graph;

  for (int i = 0; i < boxes.size(); ++i) {

    for (int j = 0; j < boxes.size(); ++j) {

      if (boxes[i]->overlap(*boxes[j])) {
        graph[i].push_back(j);
      }
    }
  }

  // merge overlapping boxes
  std::set<int> visited;
  std::vector<std::unique_ptr<Box>> results;

  for (auto& box : graph) {
    if (visited.find(box.first) == visited.end()) {
      bfs(results, box.first, graph, visited, boxes);
    }
  }

  // Input -> Output print
  std::cout << "Original unmerged box list: " << std::endl;
  for (auto& box : boxes) {
    std::cout << *box << std::endl;
  }
  std::cout << "New merged box list: " << std::endl;
  for (auto& box : results) {

    std::cout << *box << std::endl;
  }
  return 0;
}

