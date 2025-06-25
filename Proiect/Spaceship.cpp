#include "spaceship.h"

Spaceship::Spaceship() {
	image = LoadTexture("Graphics/spaceship.png");
	position.x = (GetScreenWidth() - image.width) / 2;
	position.y = GetScreenHeight() - image.height - 100;
	lastFireTime = 0.0;
	laserSound = LoadSound("Sounds/laser.ogg");
}

Spaceship::~Spaceship() {
	UnloadTexture(image);
	UnloadSound(laserSound);
}

//metoda care va desena nava spatiala pe ecran
void Spaceship::Draw() {
	DrawTextureV(image, position, WHITE);
}

//metoda care va misca nava spatiala spre stanga
void Spaceship::MoveLeft() {
	position.x -= 7;
	if (position.x < 25) {
		position.x = 25;
	}
}

//metoda care va misca nava spatiala spre dreapta
void Spaceship::MoveRight() {
	position.x += 7;
	if (position.x > GetScreenWidth() - image.width - 25) {
		position.x = GetScreenWidth() - image.width - 25;
	}
}

//metoda care va lansa razele laser din nava spatiala
void Spaceship::FireLaser() {
	if (GetTime() - lastFireTime >= 0.35) {
		lasers.push_back(Laser({ position.x + image.width / 2 - 2, position.y }, -6));
		lastFireTime = GetTime();
		PlaySound(laserSound);
	}
}

//metoda care va adauga coliziune navei spatiale
Rectangle Spaceship::getRect() {
	return { position.x, position.y, float(image.width), float(image.height) };
}

//metoda care va reseta nava spatiala inainte de a incepe urmatorul joc
void Spaceship::Reset() {
	position.x = (GetScreenWidth() - image.width) / 2;
	position.y = GetScreenHeight() - image.height - 100;
	lasers.clear();
}