#pragma once
#include <nlohmann/json.hpp>
#include <string>

namespace SPV
{

enum Locale {
    en_US,
    fr_FR,
};

const std::string& LocaleToString(Locale locale);
Locale StringToLocale(const std::string& str);


struct Settings {
    Locale locale               = Locale::en_US;
    unsigned int gridWidth      = 10;
    unsigned int gridHeight     = 10;    
    unsigned int pluginNumber   = 2;
    unsigned int initialPawnNB  = 5;
    unsigned int tieMoveNumber  = 100;
};

void from_json(const nlohmann::json& j, Settings& s);
void to_json(nlohmann::json& j, const Settings& s);

class Configuration
{
public:
    Configuration() = default;
    ~Configuration() = default;

    void LoadConfiguration();

    const Settings& GetSettings() const { return m_settings; }
    void SetLocale(Locale locale);

    std::string GetText(const char* key) const;
    template <typename... Args>
    std::string GetFormatedText(const char* key, Args&&... args) { return std::vformat(GetText(key), std::make_format_args(std::forward<Args>(args)...)); }

private:
    Settings m_settings;
    nlohmann::json m_texts;
};

} // Namespace SPV
