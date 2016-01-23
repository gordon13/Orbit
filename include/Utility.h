#ifndef UTILITY_H
#define UTILITY_H

#include <sstream>
#include <cmath>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

namespace sf
{
	class Sprite;
	class Text;
}

//template <typename T>
//std::string toString(const T& value);

template <typename T>
std::string toString(const T& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

#endif // UTILITY_H
