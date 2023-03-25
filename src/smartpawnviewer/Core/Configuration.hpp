#pragma once
#include <nlohmann/json.hpp>
#include <string>

namespace SPV
{

enum Locale {
    en_US,
    fr_FR,
};

std::string& LocaleToString(Locale locale);
Locale StringToLocale(const std::string& str);


struct Settings {
    Locale locale;
    unsigned int gridWidth;
    unsigned int gridHeight;
    unsigned int pluginNumber;
    unsigned int tieMoveNumber;
};

void from_json(const nlohmann::json& j, Settings& s);
void to_json(nlohmann::json& j, const Settings& s);

class Configuration
{
public:
    Configuration();
    ~Configuration() = default;

    void LoadConfiguration();

    const Settings& GetSettings() const { return m_settings; }
    void SetLocale(Locale locale);

    std::string GetText(const char* key) const;
    template <typename... Args>
    std::string GetFormatedText(const char* key, Args&&... args) const { return fmt::format(GetText(key), std::forward<Args>(args)...); }

private:
    Settings m_settings;
    nlohmann::json m_texts;
};

} // Namespace SPV
