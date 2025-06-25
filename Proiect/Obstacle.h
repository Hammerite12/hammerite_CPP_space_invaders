#pragma once
#include <vector>
#include "Block.h"

//clasa obstacolelor
class Obstacle {
private:

public:
	Obstacle(Vector2 position);

	void Draw();

	Vector2 position;									//pozitia obstacolului
	std::vector<Block> blocks;							//vectorul blocurilor care alcatuiesc obstacolul
	static std::vector<std::vector<int>> grid;			//matricea blocurilor care alcatuiesc obstacolul
};