#pragma once

#include <string>
#include <map>


//-----------------------------------------------------------------------------------------------
class SpriteSheet;


//-----------------------------------------------------------------------------------------------
class Text
{
public:
	Text();
	Text(const std::string& text);
	void SetText(const std::string& text);
	void Render() const;

private:
	std::string							m_text;

private:
	static std::map<char, int>			s_charMap;
	SpriteSheet*					s_spritesheet;
};