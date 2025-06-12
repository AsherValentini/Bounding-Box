#pragma once
#include <utility>

class Box {

public:
  Box(std::pair<int, int> tl, std::pair<int, int> br) : tl_(tl), br_(br) {

    std::cout << "[Box] created with top left coordinates x: " << tl_.first << " y: " << tl_.second
              << " and bottom right coordinates x: " << br_.first << " y: " << br_.second << "\n";
  }

  std::pair<int, int> topLeft() const { return tl_; }

  std::pair<int, int> bottomRight() const { return br_; }

  bool overlap(const Box& other) const {
    return !(this->br_.first < other.topLeft().first || this->br_.second < other.topLeft().second ||
             this->tl_.first > other.bottomRight().first ||
             this->tl_.second > other.bottomRight().second);
  }

private:
  std::pair<int, int> tl_;
  std::pair<int, int> br_;
};
