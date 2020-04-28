#ifndef HEADER_H
#define HEADER_H
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
    Piece(short int num, std::vector<Piece>* pieceVec, sf::Texture tile);
    void rotate(std::vector<Piece>* pieceVec);
    bool isInRow(int y, std::vector<int>* spritesInRowPos);
    bool isInRow(int y);
    Block blocks[4];
  private:
    short int num;
    short int state;
};