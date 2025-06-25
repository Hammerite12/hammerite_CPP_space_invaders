#include "Block.h"

Block::Block(Vector2 position) {
	this->position = position;
}

//metoda care va desena blocurile obstacolelor pe ecran
void Block::Draw() {
	DrawRectangle(position.x, position.y, 3, 3, { 127, 106, 79, 255 });
}

//metoda care va adauga coliziune blocurilor
Rectangle Block::getRect() {
	Rectangle rect;
	rect.x = position.x;
	rect.y = position.y;
	rect.width = 3;
	rect.height = 3;
	return rect;
}