#include "Game/Text.hpp"
#include "Engine/Renderer/SpriteSheet.hpp"
#include "Engine/Core/EngineSystemManager.hpp"
#include "Engine/Math/AABB2.hpp"
#include "Engine/Renderer/GLRenderer.hpp"

#define STATIC


//-----------------------------------------------------------------------------------------------
STATIC std::map<char, int> Text::s_charMap =
{
	{ '0', 15 },
	{ '1', 16 },
	{ '2', 17 },
	{ '3', 18 },
	{ '4', 19 },
	{ '5', 20 },
	{ '6', 21 },
	{ '7', 22 },
	{ '8', 23 },
	{ '9', 24 },
	{ 'A', 32 },
	{ 'B', 33 },
	{ 'C', 34 },
	{ 'D', 35 },
	{ 'E', 36 },
	{ 'F', 37 },
	{ 'G', 38 },
	{ 'H', 39 },
	{ 'I', 40 },
	{ 'J', 41 },
	{ 'K', 42 },
	{ 'L', 43 },
	{ 'M', 44 },
	{ 'N', 45 },
	{ 'O', 46 },
	{ 'P', 47 },
	{ 'Q', 48 },
	{ 'R', 49 },
	{ 'S', 50 },
	{ 'T', 51 },
	{ 'U', 52 },
	{ 'V', 53 },
	{ 'W', 54 },
	{ 'X', 55 },
	{ 'Y', 56 },
	{ 'Z', 57 },
	{ 'a', 64 },
	{ 'b', 65 },
	{ 'c', 66 },
	{ 'd', 67 },
	{ 'e', 68 },
	{ 'f', 69 },
	{ 'g', 70 },
	{ 'h', 71 },
	{ 'i', 72 },
	{ 'j', 73 },
	{ 'k', 74 },
	{ 'l', 75 },
	{ 'm', 76 },
	{ 'n', 77 },
	{ 'o', 78 },
	{ 'p', 79 },
	{ 'q', 80 },
	{ 'r', 81 },
	{ 's', 82 },
	{ 't', 83 },
	{ 'u', 84 },
	{ 'v', 85 },
	{ 'w', 86 },
	{ 'x', 87 },
	{ 'y', 88 },
	{ 'z', 89 }
};


//-----------------------------------------------------------------------------------------------
Text::Text()
{
}


//-----------------------------------------------------------------------------------------------
Text::Text(const std::string& text)
: m_text(text)
{
	s_spritesheet = new SpriteSheet("Data/Images/text.png", 95, 1);
}


//-----------------------------------------------------------------------------------------------
void Text::SetText(const std::string& text)
{
	m_text = text;
}


//-----------------------------------------------------------------------------------------------
void Text::Render() const
{
	for (char c : m_text)
	{
		The.Renderer->DrawTexturedAABB(AABB2(Vector2(0.f, 0.f), Vector2(1600.f, 900.f)),
			s_spritesheet->GetTexture(),
			s_spritesheet->GetTexCoordsForSpriteIndex(s_charMap[c]),
			WHITE);
	}
}