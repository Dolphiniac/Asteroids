#include "Game/ShipController.hpp"
#include "Game/Ship.hpp"
#include "Game/TheGame.hpp"
#include "Engine/Input/TheKeyboard.hpp"
#include "Engine/Core/EngineSystemManager.hpp"
#include "Engine/Input/XboxController.hpp"

#include <cstdlib>
#include <cmath>


//-----------------------------------------------------------------------------------------------
ShipController::ShipController(Ship *controlledShip)
{
	m_ship = controlledShip;
	SetController();
}


//-----------------------------------------------------------------------------------------------
void ShipController::SetController()
{
	/*m_xbInput = new XboxController(1);*/
}


//-----------------------------------------------------------------------------------------------
void ShipController::ProcessXbox()
{
	SetupThruster(The.Input->GetRightTrigger());

	float orientation = The.Input->GetLeftPolarRadians();

	m_ship->m_orientation = (orientation == DEADZONE_RADIANS) ? m_ship->m_orientation : orientation * RAD2DEG;
	if (The.Input->GetButtonDown(VB_A))
	{
		g_theGame->FirePlayerBullet();
	}
}


//-----------------------------------------------------------------------------------------------
void ShipController::ProcessKeyboard()
{
	SetupThruster(The.Input->GetVerticalAxisBinary());

	m_ship->m_angularVelocity = SHIP_ANGULARSPEED * -The.Input->GetHorizontalAxisBinary();

	if (The.Input->GetKeyDown(KB_SPACE))
	{
		g_theGame->FirePlayerBullet();
	}
}


//-----------------------------------------------------------------------------------------------
void ShipController::SetupThruster(float axisVal)
{
	float renderVal = RangeMap(axisVal, 0.f, 1.f, .5f, 1.f);
	float thrustRadians = (m_ship->m_orientation) * DEG2RAD;
	static float thrustRenderRadians = pi;
	if (axisVal > 0.f)
	{
		//Re-initialize thruster endpoint and trigger draw for this frame
		m_ship->m_renderRadius = static_cast <float> (rand() % 15 + 25);
		Vector2 thrustVertex(m_ship->m_renderRadius * renderVal * cos(thrustRenderRadians), m_ship->m_renderRadius * renderVal * sin(thrustRenderRadians));
		m_ship->m_thrusterVertices[2] = thrustVertex;
		m_ship->m_drawThruster = true;
		if (m_ship->m_renderRadius < DEFAULT_RENDER_RADIUS)
		{
			m_ship->m_renderRadius = DEFAULT_RENDER_RADIUS;

		}

		m_ship->m_acceleration.SetXY(SHIP_ACCELSPEED * axisVal * cos(thrustRadians), SHIP_ACCELSPEED * axisVal * sin(thrustRadians));
	}
	else
	{
		m_ship->m_drawThruster = false;
		m_ship->m_renderRadius = DEFAULT_RENDER_RADIUS;
	}

}


//-----------------------------------------------------------------------------------------------
void ShipController::Update()
{
	/*m_xbInput->Update();*/
	if (g_controllerOne->IsConnected())
	{
		ProcessXbox();
	}
	else
	{
		ProcessKeyboard();
	}
}