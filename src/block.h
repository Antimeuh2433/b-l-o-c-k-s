// B-L-0-C-K-S - Proof of Concept block game inspired by Tetris
// Copyright (C) 2020  Justin BAX and Chris YANG
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef BLOCK_H
#define BLOCK_H
#endif

#include <SFML/Graphics.hpp>

class Block {
  public:
    Block();
    void die();
    sf::Sprite sprite;
    bool inRow;
    bool exists;
};

class Piece {
  public:
    Piece(short int, std::vector<Piece>*, sf::Texture*, sf::RenderWindow*);
    void updateSize(sf::RenderWindow*);
    void rotateClockwise(std::vector<Piece>*);
    void rotateCounterClockwise(std::vector<Piece>*);
    bool isInRow(int, std::vector<int>*);
    bool isInRow(int);
    bool testRotation(int[], int[], int, int, bool, bool, std::vector<Piece>*);
    Block blocks[4];
  private:
    short int num;
    short int state;
};