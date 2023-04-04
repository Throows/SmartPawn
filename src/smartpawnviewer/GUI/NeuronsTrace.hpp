#pragma once

#include <Core/pch.hpp>

namespace SPV
{

enum Direction
{
    RIGHT = 0,
    DOWN = 90,
    LEFT = 180,
    UP = 270,
};

std::ostream& operator<<(std::ostream& stream, const Direction& dir);
Direction nextDirection(Direction& dir);
Direction previousDirection(Direction& dir);

class Trace
{

public:
    Trace(Direction direction, unsigned int maxSize, sf::Vector2f position);
    ~Trace() = default;

    void Init(sf::Texture& texture, bool isJunction);

    bool Update(int growSize);
    const sf::RectangleShape& GetDrawable() const { return m_traceShape; }

    void GetEndPosition(sf::Vector2f& position);

    friend std::ostream& operator<<(std::ostream& stream, const Trace& trace);
    inline std::string to_string();

    bool HasGrown() const { return hasGrown; }

private:
    sf::RectangleShape m_traceShape;
    const unsigned int m_size;
    bool isJunction;
    bool hasGrown = false;
};

class NeuronsTrace
{
public:
    NeuronsTrace(sf::Vector2i maxBounds);
    ~NeuronsTrace();

    void Init(std::shared_ptr<sf::Texture> texture);
    void MakeTrace();
    void Update(const int& dt);
    void Render(sf::RenderWindow& window);

    void Restart();

private:
    sf::Vector2i m_maxBounds;
    Direction traceDir = Direction::UP;
    const unsigned int m_turns = 3;
    std::map<unsigned char, std::unique_ptr<Trace>> traces;  
    std::shared_ptr<sf::Texture> traceTexture;

    sf::Vector2f CalculateStartPosition();
}; 
 
} // namespace SPV



