#include "ResourceAllocator.hpp"

ResourceAllocator::ResourceAllocator(std::string& executablePath)
{
    this->cwd = executablePath;
    this->cwd = this->cwd.parent_path(); // Remove the executable name
}

ResourceAllocator::~ResourceAllocator()
{
}

std::string ResourceAllocator::GetFontPath(const char* fontName)
{
    return this->cwd / "Resources" /  "Fonts" / fontName;
}

std::string ResourceAllocator::GetGUITexturePath(const char* textureName)
{
    return this->cwd / "Resources" / "GUI" / textureName;
}

std::string ResourceAllocator::GetBackgroundPath(const char* textureName)
{
    return this->cwd / "Resources" / "Backgrounds" / textureName;
}
