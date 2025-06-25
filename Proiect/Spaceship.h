#pragma once
#include <raylib.h>
#include "Laser.h"
#include <vector>

//clasa navei spatiale:
class Spaceship {
private:
	Texture2D image;				//imaginea 2D a navei spatiale
	Vector2 position;				//pozitia navei spatiale
	double lastFireTime;			//timpul ultimului laser lansat de nava spatiala
	Sound laserSound;				//sunetul razei laser lansate de nava spatiala

public:
	Spaceship();
	~Spaceship();

	void Draw();
	void MoveLeft();
	void MoveRight();
	void FireLaser();
	void Reset();
	Rectangle getRect();

	std::vector<Laser> lasers;		//vectorul razelor laser
};