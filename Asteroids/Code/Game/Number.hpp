#pragma once

#include "Game/GameObject.hpp"

#include <vector>


//-----------------------------------------------------------------------------------------------
class Number : public GameObject
{
public:
	Number();
	Number(int initialVal);
	void SetNum(int toSet);
	void Render() const;

private:
	void Render0() const;
	void Render1() const;
	void Render2() const;
	void Render3() const;
	void Render4() const;
	void Render5() const;
	void Render6() const;
	void Render7() const;
	void Render8() const;
	void Render9() const;

private:
	int							m_value;
	std::vector<Vector2>		m_vertices;
};