#include "GUI/NeuronsTrace.hpp"
#include "NeuronsTrace.hpp"

namespace SPV
{

Direction nextDirection(Direction &dir) // Clockwise change direction
{
    switch (dir) {
    case Direction::UP:
        return Direction::RIGHT;
    case Direction::DOWN:
        return Direction::LEFT;
    case Direction::LEFT:
        return Direction::UP;
    case Direction::RIGHT:
        return Direction::DOWN;
    }       
}

Direction previousDirection(Direction &dir) // Counter-clockwise change direction
{
    switch (dir) {
    case Direction::UP:
        return Direction::LEFT;
    case Direction::DOWN:
        return Direction::RIGHT;
    case Direction::LEFT:
        return Direction::DOWN;
    case Direction::RIGHT:
        return Direction::UP;
    }
}

std::ostream &operator<<(std::ostream &stream, const Direction &dir)
{
    stream << "{Direction: ";
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
    stream << "}";
    return stream;
}

std::ostream& operator<<(std::ostream &stream, const Trace &trace)
{
    stream << "Trace: {MSize:" << trace.maxSize << "}, " << trace.direction << ", {sizeX: " << trace.traceShape.getSize().x << "}, {sizeY: " << trace.traceShape.getSize().y << "}, {Junction:" << trace.isJunction << "}" << std::endl;
    return stream;
}

std::string to_string(const Trace& trace)
{
    std::ostringstream stream;
    stream << trace;
    return stream.str();
}


NeuronsTrace::NeuronsTrace(sf::Vector2i maxBounds) 
    : m_maxBounds(maxBounds)
{
}

NeuronsTrace::~NeuronsTrace()
{
}

void NeuronsTrace::Init(std::shared_ptr<sf::Texture> texture, Direction startDir)
{
    (void)texture;
    unsigned char nextTraceID = 0;
    Direction dir = startDir;
    Direction nextDir = nextDirection(dir);
    sf::Vector2f position = {500, 400};
    
    for(; nextTraceID < this->m_turns * 2; nextTraceID+=2) {
        Trace trace = {
            .traceShape = sf::RectangleShape(sf::Vector2f(0, 0)),
            .maxSize = static_cast<unsigned int>(std::rand() % 150 + 50),
            .direction = dir,
            .isJunction = false,
        };
        trace.Init(position);
        trace.GetEndPosition(position);
        SPV_APP_TRACE("Position: {}, {}", position.x, position.y);
        this->traces.emplace(nextTraceID, trace);
        Trace junction = {
            .traceShape = sf::RectangleShape(sf::Vector2f(0, 0)),
            .maxSize = 20,
            .direction = nextDir,
            .isJunction = true,
        };
        junction.Init(position);
        junction.GetEndPosition(position);
        this->traces.emplace(1+nextTraceID, junction);
        dir = nextDir;
        nextDir = nextDirection(dir);
    }
}

void NeuronsTrace::Update(const int& dt)
{
    for (auto& [id, trace] : this->traces) {
        if (trace.hasGrown) continue;

        int pixelSize = dt / 10 + 1;
        trace.Grow(pixelSize);
        if (trace.GetGrowingSize() >= trace.maxSize) {
            trace.hasGrown = true;
        }
        SPV_APP_INFO("Part : {}, Trace : {}, pixels {}", id, to_string(trace), pixelSize);
        return;
    }
}

void NeuronsTrace::Render(sf::RenderWindow &window)
{
    for (auto& [id, trace] : this->traces) {
        window.draw(trace.traceShape);
    }
}

} // namespace SPV