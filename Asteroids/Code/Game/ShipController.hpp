#pragma once


//-----------------------------------------------------------------------------------------------
class Ship;
class XboxController;


//-----------------------------------------------------------------------------------------------
class ShipController
{
private:
	XboxController*		m_xbInput;
	Ship*				m_ship;
	void				SetController();
	void				ProcessXbox();
	void				ProcessKeyboard();
	void				SetupThruster(float axisVal);

public:
	ShipController(Ship *controlledShip);
	void Update();
};