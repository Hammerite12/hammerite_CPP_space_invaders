#pragma once
#include "Spaceship.h"
#include "Obstacle.h"
#include "Alien.h"
#include "MysteryShip.h"

//clasa jocului care va servi drept container pentru celelalte clase
class Game {
private:
	int aliensDirection;										//directia in care se vor deplasa inamicii
	constexpr static float alienLaserShootInterval = 0.35;		//intervalul dintre razele laser lansate de inamici
	float timeLastAlienFired;									//timpul ultimului laser lansat de inamici
	float mysteryShipSpawnInterval;								//intervalul dintre navele misterioase generate pe ecran
	float timeLastSpawn;										//timpul ultimei nave misterioase generate pe ecran
	Spaceship spaceship;										//nava spatiala
	MysteryShip mysteryship;									//nava misterioasa
	Sound alienExplosionSound;									//sunetul inamicului lovit de raza laser
	Sound spaceshipExplosionSound;								//sunetul navei spatiale lovita de raza laser
	std::vector<Obstacle> obstacles;							//vectorul obstacolelor
	std::vector<Alien> aliens;									//vectorul inamicilor
	std::vector<Laser> alienLasers;								//vectorul razelor laser lansate de inamici

	void DeleteInactiveLasers();
	void MoveAliens();
	void MoveDownAliens(int distance);
	void AlienShootLaser();
	void CheckForCollisions();
	void GameOver();
	void Reset();
	void InitGame();
	void CheckForHighscore();
	void SaveHighscoreToFile(int highscore);
	int LoadHighscoreFromFile();
	std::vector<Obstacle> CreateObstacles();
	std::vector<Alien> CreateAliens();

public:
	bool run;													//starea jocuilui
	int lives;													//vietile jucatorului
	int score;													//scorul jucatorului
	int highscore;												//cel mai mare scor
	Music music;												//melodia jocului

	Game();
	~Game();

	void Draw();
	void Update();
	void HandleInput();
};