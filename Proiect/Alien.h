#pragma once
#include <raylib.h>

//clasa inamicilor
class Alien {
private:

public:
	static Texture2D alienImages[3];			//imaginile 2D a inamicilor;
	int type;									//varianta inamicului
	Vector2 position;							//pozitia inamicului

	Alien(int type, Vector2 position);

	static void UnloadImages();
	void Update(int direction);
	void Draw();
	int GetType();
	Rectangle getRect();
};