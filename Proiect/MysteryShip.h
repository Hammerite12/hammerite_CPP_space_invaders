#pragma once
#include <raylib.h>

//clasa navei misterioase
class MysteryShip {
private: 
	Vector2 position;		//pozitia navei misterioase
	Texture2D image;		//imaginea 2D a navei misterioase
	int speed;				//viteza navei misterioase

public:
	bool alive;				//starea navei misterioase

	MysteryShip();
	~MysteryShip();

	void Update();
	void Draw();
	void Spawn();
	Rectangle getRect();
};