#include "grid.hpp"

#include <vector>
#include <iostream>
#include <bitset>
#include <cstdlib>

void Tile::observe_value(unsigned long value) {
  domain_ = (1UL << value);
}

void Tile::eliminate_value(unsigned long value) {
  domain_ &= ~(1UL << value);
}

unsigned long Tile::get_domain() const {
  return domain_;
}

void Grid::observe_tile_random(unsigned long x, unsigned long y) {
  if (x >= width_ || y >= height_) {
    throw std::out_of_range("Grid::observe_tile_random: coordinates out of range");
  }

  unsigned long value = static_cast<unsigned long>(rand()) % cells_;
  observe_tile(x, y, value);
}

void Grid::observe_tile(unsigned long x, unsigned long y, unsigned long value) {
  if (x >= width_ || y >= height_) {
    throw std::out_of_range("Grid::observe_tile: coordinates out of range");
  }

  if (value >= cells_) {
    throw std::out_of_range("Grid::observe_tile: value out of range");
  }
  
  data_[y][x].observe_value(value);
  propogate_constraints(x, y, value);
}

void Grid::propogate_constraints(unsigned long x, unsigned long y, unsigned long value) {
  for (const auto& constraint : constraints_) {
    if (constraint.from_value != value) {
      continue;
    }

    unsigned long nx = x;
    unsigned long ny = y;

    switch (constraint.direction) {
      case UP:
        if (y == 0) continue;
        ny = y - 1;
        break;
      case DOWN:
        if (y + 1 >= height_) continue;
        ny = y + 1;
        break;
      case LEFT:
        if (x == 0) continue;
        nx = x - 1;
        break;
      case RIGHT:
        if (x + 1 >= width_) continue;
        nx = x + 1;
        break;
    }

    data_[ny][nx].eliminate_value(constraint.to_value);
  }

  // round 2 of propogation checks if there are any constrains with
  // the value as to_value, and eliminates from the original tile
  for (const auto& constraint : constraints_) {
    if (constraint.to_value != value) {
      continue;
    }

    unsigned long nx = x;
    unsigned long ny = y;

    switch (constraint.direction) {
      case UP:
        if (y == 0) continue;
        ny = y + 1;
        break;
      case DOWN:
        if (y + 1 >= height_) continue;
        ny = y - 1;
        break;
      case LEFT:
        if (x == 0) continue;
        nx = x + 1;
        break;
      case RIGHT:
        if (x + 1 >= width_) continue;
        nx = x - 1;
        break;
    }

    data_[ny][nx].eliminate_value(constraint.from_value);
  }
}

void Grid::print_grid() const {
  for (unsigned long y = 0; y < height_; ++y) {
    for (unsigned long x = 0; x < width_; ++x) {
      std::bitset<4> bits(data_[y][x].get_domain());
      std::cout << "(" << x << ", " << y << "): " << bits << "  ";
    }
    std::cout << std::endl;
  }
}

