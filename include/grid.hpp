#pragma once

#include <vector>
#include <iostream>

enum Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

// Constraint struct defines a rule that when a tile has from_value,
// the adjacent tile in the specified direction cannot have to_value.
// For example, if a tile has value 1 and there is a constraint
// {1, 2, RIGHT}, then the tile to the right cannot have value 2.
struct Constraint {
  unsigned long from_value;
  unsigned long to_value;
  Direction direction;
};

class Tile {
public:
  Tile(unsigned long cells): domain_((1UL << cells) - 1) {}

  void observe_value(unsigned long value);
  void eliminate_value(unsigned long value);
  unsigned long get_domain() const;

private:
  unsigned long domain_;
};

class Grid {
 public:
  Grid(unsigned long width, unsigned long height, unsigned long cells, std::vector<Constraint> constraints)
      :
    width_(width), height_(height), cells_(cells), data_(height, std::vector<Tile>(width, Tile(cells))), constraints_(constraints) {}

  void observe_tile(unsigned long x, unsigned long y, unsigned long value);
  void propogate_constraints(unsigned long x, unsigned long y, unsigned long value);
  void print_grid() const;

 private:
  unsigned long width_;
  unsigned long height_;
  unsigned long cells_;

  std::vector<std::vector<Tile>> data_;
  std::vector<Constraint> constraints_;
};
