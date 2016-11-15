#include "Game/Ship.hpp"
#include "Game/TheGame.hpp"
#include "Game/ShipController.hpp"
#include "Engine/Math/MathUtils.hpp"
#include "Engine/Renderer/GLRenderer.hpp"
#include "Engine/Core/EngineSystemManager.hpp"

#include <math.h>
#include <cstdlib>
#include <ctime>



//-----------------------------------------------------------------------------------------------
Ship::Ship()
{
	m_orientation = 90.f;
	m_controller = new ShipController(this);
	srand(static_cast <unsigned int> (time(NULL)));

	m_drawThruster = false;


	m_position.SetXY(WINDOW_PHYSICAL_WIDTH / 2.f, WINDOW_PHYSICAL_HEIGHT / 2.f);
	m_renderRadius = DEFAULT_RENDER_RADIUS;
	m_physicsRadius = m_renderRadius * .5f;
	m_thrusterRadius = m_physicsRadius * .65f;
	m_vertCount = 6;
	m_vertices = new Vector2[m_vertCount];
	float step = 2 * pi / 13.f;
	float currentPolarRadians = 0.f; //Start at 90deg to point up

	int i = 0;

	//Do that stuff to make it look right
	Vector2 vertex(m_renderRadius * cos(currentPolarRadians), m_renderRadius * sin(currentPolarRadians));
	m_vertices[i++] = vertex;
	currentPolarRadians += step * 5;

	vertex.SetXY(m_renderRadius * cos(currentPolarRadians), m_renderRadius * sin(currentPolarRadians));
	m_vertices[i++] = vertex;

	//m_physicsRadius is used to make the 'A' cross-section
	vertex.SetXY(m_physicsRadius * cos(currentPolarRadians), m_physicsRadius * sin(currentPolarRadians) * 1.5f);
	m_vertices[i++] = vertex;

	//m_thrusterRadius is used to initialize thruster points on the 'A'
	vertex.SetXY(m_thrusterRadius * cos(currentPolarRadians) * 1.5f, m_thrusterRadius * sin(currentPolarRadians) * 1.5f);
	m_thrusterVertices[0] = vertex;

	currentPolarRadians += step * 3;
	vertex.SetXY(m_physicsRadius * cos(currentPolarRadians), m_physicsRadius * sin(currentPolarRadians) * 1.5f);
	m_vertices[i++] = vertex;

	vertex.SetXY(m_thrusterRadius * cos(currentPolarRadians) * 1.5f, m_thrusterRadius * sin(currentPolarRadians) * 1.5f);
	m_thrusterVertices[1] = vertex;

	vertex.SetXY(m_renderRadius * cos(currentPolarRadians), m_renderRadius * sin(currentPolarRadians));
	m_vertices[i++] = vertex;

	currentPolarRadians += step * 5;
	vertex.SetXY(m_renderRadius * cos(currentPolarRadians), m_renderRadius * sin(currentPolarRadians));
	m_vertices[i++] = vertex;
	
	//Set the initial thruster endpoint to ensure no draw errors
	vertex.SetXY(m_renderRadius * cos(3.f * pi / 2.f), m_renderRadius * sin(3.f * pi / 2.f));
	m_thrusterVertices[2] = vertex;

	m_physicsRadius += 10.f; //Shenanigan adjustment
}


//-----------------------------------------------------------------------------------------------
void Ship::Update(float deltaSeconds)
{
	m_controller->Update();
	GameObject::Update(deltaSeconds);
}


//-----------------------------------------------------------------------------------------------
void Ship::Render() const
{
	The.Renderer->PushView();
	The.Renderer->TranslateView(m_position);
	The.Renderer->RotateView(m_orientation);
	for (int i = 0; i < m_vertCount - 1; i += 2)
	{
		The.Renderer->DrawLine(m_vertices[i], m_vertices[i + 1], WHITE, WHITE);
	}
	
	if (m_drawThruster)
	{
		DrawThruster();
	}

	The.Renderer->PopView();
}


//-----------------------------------------------------------------------------------------------
void Ship::DrawThruster() const
{
	The.Renderer->DrawLine(m_thrusterVertices[0], m_thrusterVertices[2], WHITE, WHITE);
	The.Renderer->DrawLine(m_thrusterVertices[1], m_thrusterVertices[2], WHITE, WHITE);
}


//-----------------------------------------------------------------------------------------------
bool Ship::ShouldDelete() const
{
	return m_isDead;// && m_timeDead >= 3.f;
}