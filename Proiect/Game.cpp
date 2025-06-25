#include "Game.h"
#include <iostream>
#include <fstream>

Game::Game() {
	music = LoadMusicStream("Sounds/music.mp3");
	alienExplosionSound = LoadSound("Sounds/alien_explosion.ogg");
	spaceshipExplosionSound = LoadSound("Sounds/spaceship_explosion.wav");
	PlayMusicStream(music);
	InitGame();
}

Game::~Game() {
	Alien::UnloadImages();
	UnloadMusicStream(music);
	UnloadSound(alienExplosionSound);
	UnloadSound(spaceshipExplosionSound);
}

//metoda care va desena obiectele jocului pe ecran
void Game::Draw() {
	spaceship.Draw();

	for (auto& laser : spaceship.lasers) {
		laser.Draw();
	}

	for (auto& obstacle : obstacles) {
		obstacle.Draw();
	}

	for (auto& alien : aliens) {
		alien.Draw();
	}

	for (auto& laser : alienLasers) {
		laser.Draw();
	}

	mysteryship.Draw();
}

//metoda care va actualiza pozitia obiectelor jocului pe ecran
void Game::Update() {
	if (run) {
		double currentTime = GetTime();
		if (currentTime - timeLastSpawn > mysteryShipSpawnInterval) {
			mysteryship.Spawn();
			timeLastSpawn = GetTime();
			mysteryShipSpawnInterval = GetRandomValue(10, 20);
		}

		for (auto& laser : spaceship.lasers) {
			laser.Update();
		}

		MoveAliens();
		AlienShootLaser();

		for (auto& laser : alienLasers) {
			laser.Update();
		}

		DeleteInactiveLasers();
		mysteryship.Update();
		CheckForCollisions();
	}
	else {
		if (IsKeyDown(KEY_ENTER)) {
			Reset();
			InitGame();
		}
	}
}

//metoda care va controla miscarile navei spatiale in functie de tastele apasate de catre utilizator
void Game::HandleInput() {
	if (run) {
		if (IsKeyDown(KEY_LEFT)) {
			spaceship.MoveLeft();
		}
		else if (IsKeyDown(KEY_RIGHT)) {
			spaceship.MoveRight();
		}
		else if (IsKeyDown(KEY_SPACE)) {
			spaceship.FireLaser();
		}
	}
}

//metoda care va sterge razele laser care au iesit din ecran
void Game::DeleteInactiveLasers() {
	for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();) {
		if (!it->active) {
			it = spaceship.lasers.erase(it);
		}
		else {
			++it;
		}
	}

	for (auto it = alienLasers.begin(); it != alienLasers.end();) {
		if (!it->active) {
			it = alienLasers.erase(it);
		}
		else {
			++it;
		}
	}
}

//metoda care va crea obstacolele
std::vector<Obstacle> Game::CreateObstacles() {
	int obstacleWidth = Obstacle::grid[0].size() * 3;
	float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;

	for (int i = 0; i < 4; i++) {
		float offsetX = (i + 1) * gap + i * obstacleWidth;
		obstacles.push_back(Obstacle({ offsetX, float(GetScreenHeight() - 200) }));
	}
	return obstacles;
}

//metoda care va crea inamicii
std::vector<Alien> Game::CreateAliens() {
	std::vector<Alien> aliens;
	for (int row = 0; row < 5; row++) {
		for (int column = 0; column < 11; column++) {
			
			int alienType;
			if (row == 0) {
				alienType = 3;
			}
			else if (row == 1 || row == 2) {
				alienType = 2;
			}
			else {
				alienType = 1;
			}

			float x = 75 + column * 55;
			float y = 110 + row * 55;
			aliens.push_back(Alien(alienType, { x, y }));
		}
	}
	return aliens;
}

//metoda care va muta inamicii
void Game::MoveAliens() {
	for (auto& alien : aliens) {
		if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25) {
			aliensDirection = -1;
			MoveDownAliens(4);
		}
		if (alien.position.x < 25) {
			aliensDirection = 1;
			MoveDownAliens(4);
		}

		alien.Update(aliensDirection);
	}
}

//metoda care va muta inamicii cu un rand mai jos
void Game::MoveDownAliens(int distance) {
	for (auto& alien : aliens) {
		alien.position.y += distance;
	}
}

//metoda care va lansa razele laser din inamici
void Game::AlienShootLaser() {
	double currentTime = GetTime();
	if (currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty()) {
		int randomIndex = GetRandomValue(0, aliens.size() - 1);
		Alien& alien = aliens[randomIndex];
		alienLasers.push_back(Laser({ alien.position.x + alien.alienImages[alien.type - 1].width / 2,
									  alien.position.y + alien.alienImages[alien.type - 1].height }, 6));
		timeLastAlienFired = GetTime();
	}
}

//metoda care va verifica coliziunile obiectelor din joc
void Game::CheckForCollisions() {

	//Spaceship Lasers
	for (auto& laser : spaceship.lasers) {
		auto it = aliens.begin();
		while (it != aliens.end()) {
			if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
				PlaySound(alienExplosionSound);
				if (it->type == 1) {
					score += 100;
				}
				else if (it->type == 2) {
					score += 200;
				}
				else if (it->type == 3) {
					score += 300;
				}
				CheckForHighscore();
				it = aliens.erase(it);
				laser.active = false;
			}
			else {
				++it;
			}
		}

		for (auto& obstacle : obstacles) {
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end()) {
				if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
					it = obstacle.blocks.erase(it);
					laser.active = false;
				}
				else {
					++it;
				}
			}
		}

		if (CheckCollisionRecs(mysteryship.getRect(), laser.getRect())) {
			mysteryship.alive = false;
			laser.active = false;
			score += 500;
			CheckForHighscore();
			PlaySound(alienExplosionSound);
		}
	}

	//Alien Lasers
	for (auto& laser : alienLasers) {
		if (CheckCollisionRecs(laser.getRect(), spaceship.getRect())) {
			PlaySound(spaceshipExplosionSound);
			laser.active = false;
			lives--;
			if (lives == 0) {
				GameOver();
			}
		}

		for (auto& obstacle : obstacles) {
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end()) {
				if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
					it = obstacle.blocks.erase(it);
					laser.active = false;
				}
				else {
					++it;
				}
			}
		}
	}

	//Alien Collision with Obstacle
	for (auto& alien : aliens) {
		for (auto& obstacle : obstacles) {
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end()) {
				if (CheckCollisionRecs(it->getRect(), alien.getRect())) {
					it = obstacle.blocks.erase(it);
				}
				else {
					it++;
				}
			}
		}

		if (CheckCollisionRecs(alien.getRect(), spaceship.getRect())) {
			GameOver();
		}
	}
}

//metoda care va finaliza jocul
void Game::GameOver() {
	run = false;
}

//metoda care va initializa obiectele jocului
void Game::InitGame() {
	obstacles = CreateObstacles();
	aliens = CreateAliens();
	aliensDirection = 1;
	timeLastAlienFired = 0.0;
	timeLastSpawn = 0.0;
	lives = 3;
	score = 0;
	highscore = LoadHighscoreFromFile();
	run = true;
	mysteryShipSpawnInterval = GetRandomValue(10, 20);
}

//metoda care va reseta jocul
void Game::Reset() {
	spaceship.Reset();
	aliens.clear();
	alienLasers.clear();
	obstacles.clear();
}

//metoda care va compara cel mai mare scor salvat cu scorul actual
void Game::CheckForHighscore() {
	if (score > highscore) {
		highscore = score;
		SaveHighscoreToFile(highscore);
	}
}

//metoda care va salva cel mai mare scor
void Game::SaveHighscoreToFile(int highscore) {
	std::ofstream highscoreFile("highscore.txt");
	if (highscoreFile.is_open()) {
		highscoreFile << highscore;
		highscoreFile.close();
	}
	else {
		std::cerr << "Failed to save highscore to file" << std::endl;
	}
}

//metoda care va afisa cel mai mare scor
int Game::LoadHighscoreFromFile() {
	int loadedHighscore = 0;
	std::ifstream highscoreFile("highscore.txt");
	if (highscoreFile.is_open()) {
		highscoreFile >> loadedHighscore;
		highscoreFile.close();
	}
	else {
		std::cerr << "Failed to load highscore from file." << std::endl;
	}
	return loadedHighscore;
}