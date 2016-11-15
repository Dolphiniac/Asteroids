#pragma once

#include "Game/GameObject.hpp"
#include "Engine/Core/Audio.hpp"


//-----------------------------------------------------------------------------------------------
class UFO : public GameObject
{
	static const float kMinimumTimeBetweenFiring;

public:
	UFO();
	void Update(float deltaSeconds);
	void Render() const;
	void ScreenExit();
	void Fire();
	~UFO();
private:
	Vector2*		m_vertices;
	float			m_timeSinceLastFire;
	SoundID			m_ID;
	FMOD::Channel*	m_channel;
};