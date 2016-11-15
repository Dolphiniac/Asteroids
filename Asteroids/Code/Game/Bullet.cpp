#include "Game/Bullet.hpp"
#include "Game/TheGame.hpp"
#include "Engine/Math/MathUtils.hpp"
#include "Engine/Renderer/GLRenderer.hpp"
#include "Engine/Core/EngineSystemManager.hpp"

#include <math.h>


//-----------------------------------------------------------------------------------------------
Bullet::Bullet(const Vector2& position, float radius, float orientation, float speedModifier)
: m_speedModifier(speedModifier)
{
	m_position = position;
	float orientationRadians = orientation * DEG2RAD;
	m_position.x += radius * cos(orientationRadians);
	m_position.y += radius * sin(orientationRadians);
	float speed = 450.f;
	m_velocity.SetXY(speed * cos(orientationRadians) * m_speedModifier, speed * sin(orientationRadians) * m_speedModifier);

	m_renderRadius = .5f;
	m_physicsRadius = 10.f;
}


//-----------------------------------------------------------------------------------------------
void Bullet::Update(float deltaSeconds)
{
	if (m_timeAlive > 2.f / m_speedModifier)
	{
		m_isDead = true;
	}
	GameObject::Update(deltaSeconds);
}


//-----------------------------------------------------------------------------------------------
void Bullet::Render() const
{
	The.Renderer->PushView();
	The.Renderer->TranslateView(m_position);
	The.Renderer->DrawPolygon(m_renderRadius, 20, 0, WHITE);
	The.Renderer->PopView();
}