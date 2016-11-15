#pragma once
#include "Engine/Math/Vector2.hpp"


//-----------------------------------------------------------------------------------------------
const float DEFAULT_RENDER_RADIUS = 30.f;


//-----------------------------------------------------------------------------------------------
class GameObject
{
public:
	GameObject();
	virtual void Update(float deltaSeconds);
	virtual void Render() const = 0;
	bool CollidesWith(const GameObject *col) const;
	Vector2 GetPosition() const;
	void SetPosition(const Vector2& newPos) { m_position = newPos; }
	float GetOrientation() const;
	float GetRenderRadius() const;
	virtual bool ShouldDelete() const;
	int GetPoints() const { return m_points; }

	bool			m_isDead;

protected:
	Vector2			m_position;
	float			m_physicsRadius;
	float			m_renderRadius;
	Vector2			m_velocity;
	Vector2			m_acceleration;
	float			m_angularVelocity;
	float			m_orientation;
	float			m_timeAlive;
	float			m_timeDead;
	int				m_points;

	void ScreenWrap();
};