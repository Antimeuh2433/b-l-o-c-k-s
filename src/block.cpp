#include "block.h"
#include <SFML/Graphics.hpp>

Block::Block() {
  this->sprite.setScale(4, 4);
  this->inRow = false;
  this->exists = true;
}

void Block::die() {
  this->exists = false;
  this->inRow = false;
  this->sprite.setPosition(10000, 10000);
  this->sprite.setScale(0, 0);
}

Piece::Piece(short int num, std::vector<Piece>* pieceVec, sf::Texture* tile) : num(num) { 
  bool shapes[7][8] = {	
	  {false, true, false, false, true, true, true, false}, // T
	  {false, false, true, false, true, true, true, false}, // L
	  {true, false, false, false, true, true, true, false}, // J
	  {false, true, true, false, false, true, true, false}, // O
	  {true, true, false, false, false, true, true, false}, // Z
	  {false, true, true, false, true, true, false, false}, // S
	  {true, true, true, true, false, false, false, false} // I
  };	

  std::vector<sf::Color> colors = {
    sf::Color(128,0,128),
    sf::Color(255,165,0),
    sf::Color::Blue,sf::Color::Yellow,
    sf::Color::Red, sf::Color::Green,
    sf::Color::Cyan
  };	

  this->state = 0;
  short int a = 0;
  for (int i = 0; i < 8; i++) {
    if (shapes[num][i]) {
      Block &block = this->blocks[a];
      block.sprite.setColor(colors[num]);
      if (i < 4) {
        block.sprite.setPosition(i * 64 + 192, 0);
        block.sprite.setTexture(*tile);
      } else {
        block.sprite.setPosition((i - 4) * 64 + 192, 64);
        block.sprite.setTexture(*tile);
      }
      a++;
    }
  }
}

void Piece::rotateClockwise(std::vector<Piece>* pieceVec) {
  if (this->num == 3) {
    //case O
    return;
  }
  sf::Vector2f center;
  if (this->num == 0 or this->num == 1 or this->num == 2 or this->num == 4) {
    //case T, J, L, Z
    center = this->blocks[2].sprite.getPosition();
  } else if (this->num == 5) {
    //case S
    center = this->blocks[3].sprite.getPosition();
  } else if (this->num == 6) {
    //case I
    center = sf::Vector2f(this->blocks[2].sprite.getPosition().x - 32, this->blocks[2].sprite.getPosition().y - 32);
    switch (this->state) {
      case 0:
        center.y += 64;
        break;
      case 1:
        break;
      case 2:
        center.x += 64;
        break;
      case 3:
        center.x += 64;
        center.y += 64;
        break;
    }
  }
  bool canRotate = true;
  short int newX[4], newY[4];
  sf::Vector2f currentPos, otherTilePos;
  for (int i = 0; i < 4; i++) {
    currentPos = this->blocks[i].sprite.getPosition();
    newX[i] = center.x - currentPos.y + center.y;
    newY[i] = center.y + currentPos.x - center.x;
    if (newX[i] < 0 or newX[i] > 640 or newY[i] < 0 or newY[i] > 1280) {
      canRotate = false;
      break;
    }
    for (int j = 1; j < (*pieceVec).size(); j++) {
      for (int k = 0; k < 4; k++) {
        Piece &otherPiece = (*pieceVec)[j];
        otherTilePos = otherPiece.blocks[k].sprite.getPosition();
        if (otherTilePos.x == newX[i] and otherTilePos.y == newY[i]) {
          canRotate = false;
          break;
        }
      }
    }
  }
  if (canRotate) {
    this->state--;
    if (this->state == -1) {
      this->state = 4;
    }
    for (int i = 0; i < 4; i++) {
      this->blocks[i].sprite.setPosition(sf::Vector2f(newX[i], newY[i]));
    }
  }
}

void Piece::rotateCounterClockwise(std::vector<Piece>* pieceVec) {
  if (this->num == 3) {
    //case O
    return;
  }
  sf::Vector2f center;
  if (this->num == 0 or this->num == 1 or this->num == 2 or this->num == 4) {
    //case T, J, L, Z
    center = this->blocks[2].sprite.getPosition();
  } else if (this->num == 5) {
    //case S
    center = this->blocks[3].sprite.getPosition();
  } else if (this->num == 6) {
    //case I
    center = sf::Vector2f(this->blocks[2].sprite.getPosition().x - 32, this->blocks[2].sprite.getPosition().y - 32);
    switch (this->state) {
      case 0:
        center.y += 64;
        break;
      case 1:
        break;
      case 2:
        center.x += 64;
        break;
      case 3:
        center.x += 64;
        center.y += 64;
        break;
    }
  }
  bool canRotate = true;
  short int newX[4], newY[4];
  sf::Vector2f currentPos, otherTilePos;
  for (int i = 0; i < 4; i++) {
    currentPos = this->blocks[i].sprite.getPosition();
    newX[i] = center.x + currentPos.y - center.y;
    newY[i] = center.y - currentPos.x + center.x;
    if (newX[i] < 0 or newX[i] > 640 or newY[i] < 0 or newY[i] > 1280) {
      canRotate = false;
      break;
    }
    for (int j = 1; j < (*pieceVec).size(); j++) {
      for (int k = 0; k < 4; k++) {
        Piece &otherPiece = (*pieceVec)[j];
        otherTilePos = otherPiece.blocks[k].sprite.getPosition();
        if (otherTilePos.x == newX[i] and otherTilePos.y == newY[i]) {
          canRotate = false;
          break;
        }
      }
    }
  }
  if (canRotate) {
    this->state--;
    if (this->state == -1) {
      this->state = 4;
    }
    for (int i = 0; i < 4; i++) {
      this->blocks[i].sprite.setPosition(sf::Vector2f(newX[i], newY[i]));
    }
  }
}

bool Piece::isInRow(int y, std::vector<int>* spritesInRowPos) {
  for (int i = 0; i < 4; i++) {
    this->blocks[i].inRow = false;
    if (this->blocks[i].sprite.getPosition().y == 64 * y and this->blocks[i].exists) {
      this->blocks[i].inRow = true;
      (*spritesInRowPos).push_back(i);
    } else {
      this->blocks[i].inRow = false;
    }
  }
  for (int i = 0; i < 4; i++) {
    if (this->blocks[i].inRow) {
      return true;
    }
  }
  return false;
}

bool Piece::isInRow(int y) {
  for (int i = 0; i < 4; i++) {
    if (this->blocks[i].sprite.getPosition().y == 64 * i and this->blocks[i].exists) {
      this->blocks[i].inRow = true;
    } else {
      this->blocks[i].inRow = false;
    }
  }
  for (int i = 0; i < 4; i++) {
    if (this->blocks[i].inRow) {
      return true;
    }
  }
  return false;
}