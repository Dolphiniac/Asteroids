#include "Game/Asteroid.hpp"
#include "Game/TheGame.hpp"
#include "Engine/Math/MathUtils.hpp"
#include "Engine/Renderer/GLRenderer.hpp"
#include "Engine/Core/EngineSystemManager.hpp"

#include <math.h>
#include <cstdlib>
#include <ctime>


//-----------------------------------------------------------------------------------------------
const int SIDES_PER_ASTEROID = 15;
const float DEFAULT_RENDER_RADIUS_ASTEROID = DEFAULT_RENDER_RADIUS + 7.5f;


//-----------------------------------------------------------------------------------------------
Asteroid::Asteroid()
{
	InitializeAsteroid(LARGE);
}


//-----------------------------------------------------------------------------------------------
Asteroid::Asteroid(Vector2 initialPos, AsteroidSize size)
{
	InitializeAsteroid(initialPos, size);
}


//-----------------------------------------------------------------------------------------------
void Asteroid::InitializeAsteroid(Vector2 initialPos, AsteroidSize size)
{
	m_size = size;
	m_angularVelocity = static_cast <float> (rand() % 100 - 50);

	float stepRadians = 2.f * pi / static_cast <float> (SIDES_PER_ASTEROID);
	float currentRadians = 0.f;
	float drawRadius;

	switch (m_size)
	{
	case LARGE:
		m_renderRadius = drawRadius = DEFAULT_RENDER_RADIUS_ASTEROID;
		m_points = 20;
		break;
	case MEDIUM:
		m_renderRadius = drawRadius = DEFAULT_RENDER_RADIUS_ASTEROID / 2.f;
		m_points = 50;
		break;
	case SMALL:
	default:
		m_renderRadius = drawRadius = DEFAULT_RENDER_RADIUS_ASTEROID / 4.f;
		m_points = 100;
	}

	Vector2 startVertex(m_renderRadius * cos(0.f), m_renderRadius * sin(0.f));
	m_vertices.push_back(startVertex);

	Vector2 vertex;
	int i;
	for (i = 1; i < SIDES_PER_ASTEROID; i++, currentRadians += stepRadians)
	{
		float currentRadius = drawRadius + static_cast <float> (rand() % 12 - 6);
		if (m_renderRadius < currentRadius)
			m_renderRadius = currentRadius;
		vertex.SetXY(currentRadius * cos(currentRadians), currentRadius * sin(currentRadians));
		m_vertices.push_back(vertex);
	}
	m_vertices.push_back(startVertex);

	m_physicsRadius = drawRadius + ((m_renderRadius - drawRadius) / 2.f);

	m_position.SetXY(initialPos.x, initialPos.y);

	int polarDegrees = rand();
	if (polarDegrees % 90 < 5)
	{
		polarDegrees += 45;
	}

	float polarRadians = static_cast <float> (polarDegrees)* DEG2RAD;

	float speed = 175.f;
	m_velocity.SetXY(speed * cos(polarRadians), speed * sin(polarRadians));
}


void Asteroid::InitializeAsteroid(AsteroidSize size)
{
	switch (rand() % 4)
	{
	case 0:
		m_position.SetXY(0.f - m_renderRadius, static_cast <float> (rand() % WINDOW_PHYSICAL_HEIGHT));
		break;
	case 1:
		m_position.SetXY(WINDOW_PHYSICAL_WIDTH + m_renderRadius, static_cast <float> (rand() % WINDOW_PHYSICAL_HEIGHT));
		break;
	case 2:
		m_position.SetXY(static_cast <float> (rand() % WINDOW_PHYSICAL_WIDTH), 0.f - m_renderRadius);
		break;
	case 3:
		m_position.SetXY(static_cast <float> (rand() % WINDOW_PHYSICAL_WIDTH), WINDOW_PHYSICAL_HEIGHT + m_renderRadius);
		break;
	}

	InitializeAsteroid(m_position, size);
}


//-----------------------------------------------------------------------------------------------
void Asteroid::Render() const
{
	The.Renderer->PushView();
	The.Renderer->TranslateView(m_position);
	The.Renderer->RotateView(m_orientation);

	for (auto vectorIter = m_vertices.begin(); vectorIter != m_vertices.end(); vectorIter++)
	{
		Vector2 currentVertex = *vectorIter;
		auto secondVectorIter = vectorIter;
		secondVectorIter++;
		Vector2 secondVertex;
		if (secondVectorIter == m_vertices.end())
			break;

		secondVertex = *secondVectorIter;

		The.Renderer->DrawLine(currentVertex, secondVertex, WHITE, WHITE);

	}
	The.Renderer->PopView();
}