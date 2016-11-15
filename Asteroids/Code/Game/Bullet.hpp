#pragma once

#include "Game/GameObject.hpp"


//-----------------------------------------------------------------------------------------------
class Vector2;


//-----------------------------------------------------------------------------------------------
class Bullet : public GameObject
{
public:
	Bullet(const Vector2& position, float radius, float orientation, float speedModifier = 1.f);
	void Update(float deltaSeconds);
	void Render() const;

private:
	float			m_speedModifier;
};