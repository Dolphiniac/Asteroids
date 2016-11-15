#include "Game/UFO.hpp"
#include "Game/TheGame.hpp"
#include "Engine/Math/MathUtils.hpp"
#include "Engine/Renderer/GLRenderer.hpp"
#include "Engine/Core/EngineSystemManager.hpp"

#include <math.h>

#define STATIC


//-----------------------------------------------------------------------------------------------
STATIC const float UFO::kMinimumTimeBetweenFiring = 2.f;


//-----------------------------------------------------------------------------------------------
UFO::UFO()
: m_vertices(new Vector2[8])
, m_timeSinceLastFire(.75f)
, m_ID(The.Audio->CreateOrGetSound("Data/Audio/ufo.wav"))
, m_channel(The.Audio->PlaySound(m_ID))
{
	m_points = 500;
	m_channel->setMode(FMOD_LOOP_NORMAL);
	m_renderRadius = DEFAULT_RENDER_RADIUS;
	m_physicsRadius = m_renderRadius * .5f;
	float velX = 1600.f / 7.5f;
	switch (rand() % 2)
	{
	case 0:
		m_position.SetXY(0.f - m_renderRadius, static_cast <float> (rand() % WINDOW_PHYSICAL_HEIGHT));
		break;
	case 1:
		m_position.SetXY(WINDOW_PHYSICAL_WIDTH + m_renderRadius, static_cast <float> (rand() % WINDOW_PHYSICAL_HEIGHT));
		velX = -velX;
		break;
	}
	m_velocity.SetXY(velX, 0.f);

	Vector2 currentVertex;

	currentVertex.SetXY(m_renderRadius, 0.f);
	m_vertices[0] = currentVertex;

	currentVertex.SetXY(m_physicsRadius * cos(45.f * DEG2RAD), m_physicsRadius * sin(45.f * DEG2RAD));
	m_vertices[1] = currentVertex;

	currentVertex.SetXY(m_renderRadius * cos(75.f * DEG2RAD) * .75f, m_renderRadius * sin(75.f * DEG2RAD) * .75f);
	m_vertices[2] = currentVertex;

	currentVertex.SetXY(m_renderRadius * cos(105.f * DEG2RAD) * .75f, m_renderRadius * sin(105.f * DEG2RAD) * .75f);
	m_vertices[3] = currentVertex;

	currentVertex.SetXY(m_physicsRadius * cos(135.f * DEG2RAD), m_physicsRadius * sin(135.f * DEG2RAD));
	m_vertices[4] = currentVertex;

	currentVertex.SetXY(-m_renderRadius, 0.f);
	m_vertices[5] = currentVertex;

	currentVertex.SetXY(m_physicsRadius * cos(225.f * DEG2RAD), m_physicsRadius * sin(225.f * DEG2RAD));
	m_vertices[6] = currentVertex;

	currentVertex.SetXY(m_physicsRadius * cos(315.f * DEG2RAD), m_physicsRadius * sin(315.f * DEG2RAD));
	m_vertices[7] = currentVertex;
}


//-----------------------------------------------------------------------------------------------
void UFO::Update(float deltaSeconds)
{
	m_timeAlive += deltaSeconds;
	m_timeSinceLastFire += deltaSeconds;
	if (m_isDead)
	{
		m_timeDead += deltaSeconds;
	}

	m_orientation += m_angularVelocity * deltaSeconds;
	m_velocity += m_acceleration * deltaSeconds;
	m_acceleration = Vector2::Zero; //Zero out acceleration to insure one-frame application
	m_position += m_velocity * deltaSeconds;

	Fire();

	ScreenExit();
}


//-----------------------------------------------------------------------------------------------
void UFO::Render() const
{
	The.Renderer->PushView();
	The.Renderer->TranslateView(m_position);

	The.Renderer->DrawLine(m_vertices[0], m_vertices[1], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[1], m_vertices[2], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[2], m_vertices[3], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[3], m_vertices[4], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[4], m_vertices[5], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[5], m_vertices[6], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[6], m_vertices[7], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[7], m_vertices[0], WHITE, WHITE);

	The.Renderer->DrawLine(m_vertices[1], m_vertices[4], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[0], m_vertices[5], WHITE, WHITE);

	The.Renderer->PopView();
}


//-----------------------------------------------------------------------------------------------
void UFO::ScreenExit()
{
	if (m_position.x - m_renderRadius > WINDOW_PHYSICAL_WIDTH)
	{
		m_isDead = true;
		m_points = 0;
	}
	else if (m_position.x + m_renderRadius < 0.f)
	{
		m_isDead = true;
		m_points = 0;
	}
}


//-----------------------------------------------------------------------------------------------
void UFO::Fire()
{
	if (m_timeSinceLastFire < kMinimumTimeBetweenFiring)
	{
		return;
	}

	g_theGame->FireEnemyBullet(m_position);
	m_timeSinceLastFire = 0.f;
}


//-----------------------------------------------------------------------------------------------
UFO::~UFO()
{
	delete[] m_vertices;
	m_channel->stop();
}