#include "Alien.h"

Texture2D Alien::alienImages[3] = {};

Alien::Alien(int type, Vector2 position) {
	this->type = type;
	this->position = position;

	if (alienImages[type - 1].id == 0) {
		switch (type) {
			case 1:
				alienImages[0] = LoadTexture("Graphics/alien_1.png");
				break;
			case 2:
				alienImages[1] = LoadTexture("Graphics/alien_2.png");
				break;
			case 3:
				alienImages[2] = LoadTexture("Graphics/alien_3.png");
				break;
			default:
				alienImages[0] = LoadTexture("Graphics/alien_1.png");
				break;
		}
	}
}

//metoda care va desena inamicii pe ecran
void Alien::Draw() {
	DrawTextureV(alienImages[type - 1], position, WHITE);
}

//metoda care va returna varianta inamicului
int Alien::GetType() {
	return type;
}

//metoda care va sterge imaginile inamicilor din memoria computer-ului cand fereastra va fi inchisa
void Alien::UnloadImages() {
	for (int i = 0; i < 3; i++) {
		UnloadTexture(alienImages[i]);
	}
}

//metoda care va actualiza pozitia inamicilor pe ecran
void Alien::Update(int direction) {
	position.x += direction;
}

//metoda care va adauga coliziune inamicilor
Rectangle Alien::getRect() {
	return { position.x, position.y, float(alienImages[type - 1].width), float(alienImages[type - 1].height) };
}