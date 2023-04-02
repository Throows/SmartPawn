#pragma once

#include <Core/pch.hpp>

namespace SPV
{

enum class Direction : unsigned char
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

Direction nextDirection(Direction& dir);
std::ostream& operator<<(std::ostream& stream, const Direction& dir);


struct Trace
{
    sf::RectangleShape traceShape;
    unsigned int maxSize;
    Direction direction;
    bool hasGrown = false;
    bool isJunction;

    void Init(sf::Vector2f position) {
        int rotation = 270;
        if (direction == Direction::DOWN) rotation = 90;
        else if (direction == Direction::LEFT) rotation = 180;
        else if (direction == Direction::RIGHT) rotation = 0;
        traceShape.setRotation(rotation);
        traceShape.setPosition(position);
        if (isJunction)
            traceShape.setFillColor(sf::Color::Magenta);
        else if (direction == Direction::UP || direction == Direction::DOWN)
            traceShape.setFillColor(sf::Color::Green);
        else
            traceShape.setFillColor(sf::Color::Blue);
    }

    void GetEndPosition(sf::Vector2f& position) {
        if (direction == Direction::UP) position.y -= maxSize;
        else if (direction == Direction::DOWN) position.y += maxSize;
        else if (direction == Direction::LEFT) position.x -= maxSize;
        else if (direction == Direction::RIGHT) position.x += maxSize;
    }

    unsigned int GetGrowingSize() {
        return traceShape.getSize().x;
    };

    void Grow(int size){
        int growSize = GetGrowingSize() + size;
        traceShape.setSize(sf::Vector2f(growSize, 20));
    }
};

std::ostream& operator<<(std::ostream& stream, const Trace& trace);
inline std::string to_string(const Trace& trace);

class NeuronsTrace
{
public:
    NeuronsTrace(sf::Vector2i maxBounds);
    ~NeuronsTrace();

    void Init(std::shared_ptr<sf::Texture> texture, Direction startDir);
    void Update(const int& dt);
    void Render(sf::RenderWindow& window);

private:
    sf::Vector2i m_maxBounds;
    const unsigned int m_turns = 3;

    std::map<unsigned char, Trace> traces;
}; 
 
} // namespace SPV



