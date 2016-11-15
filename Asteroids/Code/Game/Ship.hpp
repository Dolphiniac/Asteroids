#pragma once
#include "Game/GameObject.hpp"


//-----------------------------------------------------------------------------------------------
const float			SHIP_ANGULARSPEED = 250.f;
const float			SHIP_ACCELSPEED = 225.f;


//-----------------------------------------------------------------------------------------------
class ShipController;


//-----------------------------------------------------------------------------------------------
class Ship : public GameObject
{
	friend class ShipController;
public:
	Ship();
	virtual void Update(float deltaSeconds);
	virtual void Render() const;
	void DrawThruster() const;
	virtual bool ShouldDelete() const;

protected:
	float				m_thrusterRadius;
	Vector2*			m_vertices;
	int					m_vertCount;
	Vector2				m_thrusterVertices[3];
	bool				m_drawThruster;
	ShipController*		m_controller;
};