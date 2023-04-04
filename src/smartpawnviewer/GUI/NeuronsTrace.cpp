#include "GUI/NeuronsTrace.hpp"
#include "NeuronsTrace.hpp"

namespace SPV
{
    
std::ostream &operator<<(std::ostream &stream, const Direction &dir)
{
    switch (dir) {
    case Direction::UP:
        stream << "UP";
        break;
    case Direction::DOWN:
        stream << "DOWN";
        break;
    case Direction::LEFT:
        stream << "LEFT";
        break;
    case Direction::RIGHT:
        stream << "RIGHT";
        break;
    }
    return stream;
}

Direction nextDirection(Direction &dir) // Clockwise change direction
{
    return static_cast<Direction>((static_cast<int>(dir) + 90) % 360);
}

Direction previousDirection(Direction &dir) // Counter-clockwise change direction
{
    int newDir = 270;
    if(static_cast<int>(dir) > 0) newDir = (static_cast<int>(dir) - 90) % 360;
    return static_cast<Direction>(newDir);
}

// ------ Trace ------
Trace::Trace(Direction direction, unsigned int maxSize, sf::Vector2f position)
    : m_traceShape(sf::RectangleShape())
    , m_size(maxSize)
{
    m_traceShape.setRotation(direction);
    SPV_APP_INFO("Trace Rotation : {0}", m_traceShape.getRotation());
    m_traceShape.setPosition(position);
    m_traceShape.setSize(sf::Vector2f(0, 19));
    
}

void Trace::Init(sf::Texture& texture, bool isJunction)
{
    m_traceShape.setTexture(&texture);
    m_traceShape.setTextureRect(sf::IntRect(isJunction ? 20 : 0, 0, 19, 19));
    this->isJunction = isJunction;
}

bool Trace::Update(int growSize)
{
    if (!this->hasGrown) {
        auto newSize = m_traceShape.getSize();
        newSize.x += growSize;
        if (newSize.x >= this->m_size) {
            newSize.x = this->m_size;
            this->hasGrown = true;
        }
        m_traceShape.setSize(newSize);
    }
    return !this->hasGrown;
}

void Trace::GetEndPosition(sf::Vector2f &position)
{
    Direction direction = static_cast<Direction>(m_traceShape.getRotation());
    switch (direction)
    {
    case Direction::UP:
        position.y -= this->m_size;
        break;
    case Direction::DOWN:
        position.y += this->m_size;
        break;
    case Direction::LEFT:
        position.x -= this->m_size;
        break;
    case Direction::RIGHT:
        position.x += this->m_size;
        break;
    default:
        position.x = 0;
        position.y = 0;
        break;
    }
}

std::ostream& operator<<(std::ostream& stream, const Trace& trace)
{
    Direction dir = static_cast<Direction>(trace.m_traceShape.getRotation());
    stream  << "{Trace : SizeX: " << trace.m_traceShape.getSize().x << ", "
            << "SizeY: " << trace.m_traceShape.getSize().y << ", "  
            << "Rotation: " << dir << ", "
            << "hasGrown: " << trace.hasGrown << ", "
            << "isJunction: " << trace.isJunction << "}"
            << std::endl;
    return stream;
}

inline std::string Trace::to_string()
{
    std::ostringstream stream;
    stream << (*this);
    return stream.str();
}

// ------ NeuronsTrace ------
NeuronsTrace::NeuronsTrace(sf::Vector2i maxBounds) 
    : m_maxBounds(maxBounds)
{
}

NeuronsTrace::~NeuronsTrace()
{
}

void NeuronsTrace::Init(std::shared_ptr<sf::Texture> texture)
{
   this->traceTexture = std::move(texture);
   MakeTrace();
}

void NeuronsTrace::MakeTrace()
{
    Direction dir = this->traceDir;
    Direction nextDir = nextDirection(dir);
    sf::Vector2f position = CalculateStartPosition();
    
    for(unsigned int nextTraceID = 0; nextTraceID < this->m_turns * 2; nextTraceID+=2) {
        auto trace = std::make_unique<Trace>(dir, static_cast<unsigned int>(std::rand() % 150 + 50), position);
        trace->Init(*this->traceTexture.get(), false);
        trace->GetEndPosition(position);
        this->traces.emplace(nextTraceID, std::move(trace));
        auto junction = std::make_unique<Trace>(nextDir, 20, position);
        junction->Init(*this->traceTexture.get(), true);
        junction->GetEndPosition(position);
        this->traces.emplace(1+nextTraceID, std::move(junction));
        dir = nextDir;
        nextDir = nextDirection(dir);
    }
}

void NeuronsTrace::Update(const int& dt)
{
    int sizedt = dt / 10 + 1;
    for (auto& [id, trace] : this->traces) {
        if (trace->Update(sizedt)) {
            SPV_APP_INFO("Part : {}, Trace : {}, pixels {}", id, trace->to_string(), sizedt);
            return;
        }
    }
    this->Restart();
}

void NeuronsTrace::Render(sf::RenderWindow &window)
{
    for (auto& [id, trace] : this->traces) {
        window.draw(trace->GetDrawable());
    }
}

void NeuronsTrace::Restart()
{
    this->traceDir = nextDirection(this->traceDir);
    this->traces.clear();
    this->MakeTrace();
}

sf::Vector2f NeuronsTrace::CalculateStartPosition()
{
    int randomX = std::rand() % this->m_maxBounds.x;
    int randomY = std::rand() % this->m_maxBounds.y;
    switch (this->traceDir)
    {
    case Direction::UP:
        return sf::Vector2f(randomX, this->m_maxBounds.y);
    case Direction::DOWN:
        return sf::Vector2f(randomX, 0);
    case Direction::LEFT:
        return sf::Vector2f(this->m_maxBounds.x, randomY);
    case Direction::RIGHT:
        return sf::Vector2f(0, randomY);
    default:
        return sf::Vector2f(0, 0);
    };
}

} // namespace SPV