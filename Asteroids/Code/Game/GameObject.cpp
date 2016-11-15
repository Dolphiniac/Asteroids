#include "Game/GameObject.hpp"
#include "Game/TheGame.hpp"
#include "Engine/Math/MathUtils.hpp"
#include "Engine/Renderer/TheRenderer.hpp"



//-----------------------------------------------------------------------------------------------
GameObject::GameObject()
: m_position(Vector2::Zero)
, m_points(0)
, m_physicsRadius(0.f)
, m_renderRadius(0.f)
, m_velocity(Vector2::Zero)
, m_acceleration(Vector2::Zero)
, m_angularVelocity(0.f)
, m_orientation(0.f)
, m_isDead(false)
, m_timeAlive(0.f)
, m_timeDead(0.f)
{
}


//-----------------------------------------------------------------------------------------------
void GameObject::Update(float deltaSeconds)
{
	m_timeAlive += deltaSeconds;
	if (m_isDead)
	{
		m_timeDead += deltaSeconds;
	}

	m_orientation += m_angularVelocity * deltaSeconds;
	m_velocity += m_acceleration * deltaSeconds;
	m_acceleration = Vector2::Zero; //Zero out acceleration to insure one-frame application
	m_position += m_velocity * deltaSeconds;

	ScreenWrap();
}


//-----------------------------------------------------------------------------------------------
void GameObject::ScreenWrap()
{
	if (m_position.x - m_renderRadius > WINDOW_PHYSICAL_WIDTH)
	{
		m_position.x = -m_renderRadius;
	}
	else if (m_position.x + m_renderRadius < 0.f)
	{
		m_position.x = WINDOW_PHYSICAL_WIDTH + m_renderRadius;
	}

	if (m_position.y - m_renderRadius > WINDOW_PHYSICAL_HEIGHT)
	{
		m_position.y = -m_renderRadius;
	}
	else if (m_position.y + m_renderRadius < 0.f)
	{
		m_position.y = WINDOW_PHYSICAL_HEIGHT + m_renderRadius;
	}
}


//-----------------------------------------------------------------------------------------------
bool GameObject::CollidesWith(const GameObject *col) const
{
	if (col == nullptr)
	{
		return false;
	}
	return DoDiscsOverlap(m_position, m_physicsRadius, col->m_position, col->m_physicsRadius);
}

Vector2 GameObject::GetPosition() const
{
	return m_position;
}

float GameObject::GetOrientation() const
{
	return m_orientation;
}


float GameObject::GetRenderRadius() const
{
	return m_renderRadius;
}


//-----------------------------------------------------------------------------------------------
bool GameObject::ShouldDelete() const
{
	return m_isDead;
}