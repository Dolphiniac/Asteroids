#pragma once
#include "Game/GameObject.hpp"

#include <vector>


//-----------------------------------------------------------------------------------------------
enum AsteroidSize;


//-----------------------------------------------------------------------------------------------
class Asteroid : public GameObject
{
public:
	Asteroid();
	Asteroid(Vector2 initialPos, AsteroidSize size);
	AsteroidSize GetSize() const { return m_size; }
	void Render() const;

private:
	void InitializeAsteroid(Vector2 initialPos, AsteroidSize size);
	void InitializeAsteroid(AsteroidSize size);

private:
	AsteroidSize					m_size;
	std::vector<Vector2>			m_vertices;
};