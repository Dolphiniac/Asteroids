#include "Game/Number.hpp"

#include "Engine/Core/ErrorWarningAssert.hpp"
#include "Engine/Core/StringUtils.hpp"
#include "Engine/Renderer/GLRenderer.hpp"
#include "Engine/Core/EngineSystemManager.hpp"


//-----------------------------------------------------------------------------------------------
Number::Number()
: m_value(0)
{
	m_renderRadius = DEFAULT_RENDER_RADIUS;

	Vector2 vertex;

	vertex.SetXY(-m_renderRadius * .75f, m_renderRadius);
	m_vertices.push_back(vertex);

	vertex.SetXY(-m_renderRadius * .75f, 0.f);
	m_vertices.push_back(vertex);

	vertex.SetXY(-m_renderRadius * .75f, -m_renderRadius);
	m_vertices.push_back(vertex);

	vertex.SetXY(m_renderRadius * .75f, m_renderRadius);
	m_vertices.push_back(vertex);

	vertex.SetXY(m_renderRadius * .75f, 0.f);
	m_vertices.push_back(vertex);

	vertex.SetXY(m_renderRadius * .75f, -m_renderRadius);
	m_vertices.push_back(vertex);
}


//-----------------------------------------------------------------------------------------------
Number::Number(int initialVal)
: m_value(initialVal)
{
	m_renderRadius = DEFAULT_RENDER_RADIUS;
	SetNum(initialVal);

	Vector2 vertex;

	vertex.SetXY(-m_renderRadius * .75f, m_renderRadius);
	m_vertices.push_back(vertex);

	vertex.SetXY(-m_renderRadius * .75f, 0.f);
	m_vertices.push_back(vertex);

	vertex.SetXY(-m_renderRadius * .75f, -m_renderRadius);
	m_vertices.push_back(vertex);

	vertex.SetXY(m_renderRadius * .75f, m_renderRadius);
	m_vertices.push_back(vertex);

	vertex.SetXY(m_renderRadius * .75f, 0.f);
	m_vertices.push_back(vertex);

	vertex.SetXY(m_renderRadius * .75f, -m_renderRadius);
	m_vertices.push_back(vertex);
}


//-----------------------------------------------------------------------------------------------
void Number::SetNum(int toSet)
{
	ASSERT_OR_DIE(toSet >= 0 && toSet <= 9, Stringf("Invalid value for Number:\t%i\n", toSet));

	if (toSet == m_value)
	{
		return;
	}

	m_value = toSet;
}


//-----------------------------------------------------------------------------------------------
void Number::Render() const
{
	The.Renderer->PushView();
	The.Renderer->TranslateView(m_position);

	switch (m_value)
	{
	case 0:
		Render0();
		break;
	case 1:
		Render1();
		break;
	case 2:
		Render2();
		break;
	case 3:
		Render3();
		break;
	case 4:
		Render4();
		break;
	case 5:
		Render5();
		break;
	case 6:
		Render6();
		break;
	case 7:
		Render7();
		break;
	case 8:
		Render8();
		break;
	case 9:
		Render9();
		break;
	}

	The.Renderer->PopView();
}


//-----------------------------------------------------------------------------------------------
void Number::Render0() const
{
	The.Renderer->DrawLine(m_vertices[0], m_vertices[2], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[2], m_vertices[5], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[0], m_vertices[3], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[3], m_vertices[5], WHITE, WHITE);
}


//-----------------------------------------------------------------------------------------------
void Number::Render1() const
{
	The.Renderer->DrawLine(m_vertices[3], m_vertices[5], WHITE, WHITE);
}


//-----------------------------------------------------------------------------------------------
void Number::Render2() const
{
	The.Renderer->DrawLine(m_vertices[0], m_vertices[3], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[3], m_vertices[4], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[4], m_vertices[1], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[1], m_vertices[2], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[2], m_vertices[5], WHITE, WHITE);
}


//-----------------------------------------------------------------------------------------------
void Number::Render3() const
{
	The.Renderer->DrawLine(m_vertices[0], m_vertices[3], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[3], m_vertices[5], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[4], m_vertices[1], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[5], m_vertices[2], WHITE, WHITE);
}


//-----------------------------------------------------------------------------------------------
void Number::Render4() const
{
	The.Renderer->DrawLine(m_vertices[0], m_vertices[1], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[1], m_vertices[4], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[3], m_vertices[5], WHITE, WHITE);
}


//-----------------------------------------------------------------------------------------------
void Number::Render5() const
{
	The.Renderer->DrawLine(m_vertices[3], m_vertices[0], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[0], m_vertices[1], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[1], m_vertices[4], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[4], m_vertices[5], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[5], m_vertices[2], WHITE, WHITE);
}


//-----------------------------------------------------------------------------------------------
void Number::Render6() const
{
	The.Renderer->DrawLine(m_vertices[3], m_vertices[0], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[0], m_vertices[2], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[2], m_vertices[5], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[5], m_vertices[4], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[4], m_vertices[1], WHITE, WHITE);
}


//-----------------------------------------------------------------------------------------------
void Number::Render7() const
{
	The.Renderer->DrawLine(m_vertices[0], m_vertices[3], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[3], m_vertices[5], WHITE, WHITE);
}


//-----------------------------------------------------------------------------------------------
void Number::Render8() const
{
	The.Renderer->DrawLine(m_vertices[0], m_vertices[3], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[1], m_vertices[4], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[2], m_vertices[5], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[0], m_vertices[2], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[3], m_vertices[5], WHITE, WHITE);
}


//-----------------------------------------------------------------------------------------------
void Number::Render9() const
{
	The.Renderer->DrawLine(m_vertices[0], m_vertices[3], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[1], m_vertices[4], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[2], m_vertices[5], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[0], m_vertices[1], WHITE, WHITE);
	The.Renderer->DrawLine(m_vertices[3], m_vertices[5], WHITE, WHITE);
}