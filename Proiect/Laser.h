#pragma once
#include <raylib.h>

//clasa razei laser
class Laser {
private:
	Vector2 position;							//pozitia razei laser
	int speed;									//viteza razei laser

public:
	bool active;								//starea razei laser

	Laser(Vector2 position, int speed);

	void Draw();
	void Update();
	Rectangle getRect();
};
