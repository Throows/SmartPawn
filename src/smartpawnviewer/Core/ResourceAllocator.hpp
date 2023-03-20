#pragma once
#include <string>
#include <filesystem>

class ResourceAllocator
{
public:
    ResourceAllocator(std::string& executablePath);
    ~ResourceAllocator();

    std::string GetFontPath(const char* fontName);
    std::string GetGUITexturePath(const char* textureName);
    std::string GetBackgroundPath(const char* textureName);

private:
    std::filesystem::path cwd;
};
