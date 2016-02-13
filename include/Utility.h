#ifndef UTILITY_H
#define UTILITY_H

#include <sstream>
#include <cmath>
#include <utility>

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


// vector math
/*sf::Vector2f normalizeVector2fds(const sf::Vector2f& source)
{
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return sf::Vector2f(source.x / length, source.y / length);
    else
        return source;
}*/

/*float getLength(float x, float y)
{
    return sqrt(x*x + y*y);
}*/

#endif // UTILITY_H
