#pragma once
#include <raylib.h>

//clasa blocurilor care vor alcatui obstacolul
class Block {
private:
	Vector2 position;					//pozitia blocului

public:
	Block(Vector2 position);

	void Draw();
	Rectangle getRect();
};