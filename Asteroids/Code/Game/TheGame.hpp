#pragma once

#include <set>
#include <vector>


//-----------------------------------------------------------------------------------------------
const int OFFSET_FROM_WINDOWS_DESKTOP = 50;
const int WINDOW_PHYSICAL_WIDTH = 1600;
const int WINDOW_PHYSICAL_HEIGHT = 900;
const double VIEW_LEFT = 0.0;
const double VIEW_RIGHT = 1600.0;
const double VIEW_BOTTOM = 0.0;
const double VIEW_TOP = VIEW_RIGHT * static_cast<double>(WINDOW_PHYSICAL_HEIGHT) / static_cast<double>(WINDOW_PHYSICAL_WIDTH);


//-----------------------------------------------------------------------------------------------
class TheGame;
class GameObject;
class Vector2;
class Bullet;
class Asteroid;
class Ship;
class UFO;
class Number;


//-----------------------------------------------------------------------------------------------
extern TheGame *g_theGame;


//-----------------------------------------------------------------------------------------------
enum AsteroidSize {SMALL, MEDIUM, LARGE};


//-----------------------------------------------------------------------------------------------
typedef unsigned int SoundID;


//-----------------------------------------------------------------------------------------------
class TheGame
{
public:
	TheGame();

	void	SpawnShip();
	void	SpawnAsteroid();
	void	SpawnAsteroid(const Vector2& initialPos, AsteroidSize size);
	void	SpawnChildAsteroids(const Vector2& initialPos, AsteroidSize size);
	void	SpawnUFO();
	void	DeleteAsteroid();
	void	HandleHotKeys();
	void	XboxRespond();
	void	KeyboardRespond();
	void	Update(float deltaSeconds);
	void	AsteroidCollide();
	void	Render() const;
	void	FirePlayerBullet();
	void	FireEnemyBullet(const Vector2& position);
	void	ShakeScreen(float deltaSeconds);
	void	SetShakeMagnitude(float newMagnitude);
	void	StartLevel();
	void	ShipBulletCollide();
	void	UFOBulletCollide();
	Vector2 GetPlayerPosition() const;
	void UpdateUFOTimer(float deltaSeconds);
	void RenderGUI() const;
	void LoseLife();
	void UpdateScore() const;
public:
	bool						m_isQuitting;

private:
	float						m_timeSinceLastUFO;
	float						m_timeBetweenUFOs;
	float						m_shakeMagnitude;
	std::set<GameObject*>		m_entities;
	std::set<Asteroid*>			m_asteroids;
	std::set<Bullet*>			m_playerBullets;
	std::set<Bullet*>			m_enemyBullets;
	std::vector<Ship*>			m_lives;
	std::vector<Number*>		m_score;
	Ship*						m_ship;
	UFO*						m_ufo;
	int							m_levelAsteroids;
	SoundID						m_laser;
	SoundID						m_espload;
	SoundID						m_shipEspload;

	unsigned int				m_points;
};