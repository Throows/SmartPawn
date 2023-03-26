#include <Core/pch.hpp>
#include <Core/Configuration.hpp>
#include <fstream>
#include <format>

static const std::string localName[] = {
    "en_US",
    "fr_FR",
};

namespace SPV
{

const std::string& LocaleToString(Locale locale)
{
    return localName[(int)locale];
}

Locale StringToLocale(const std::string& str)
{
    if (str == "fr_FR")
        return Locale::fr_FR;
    else 
        return Locale::en_US;
}

void from_json(const nlohmann::json &j, Settings &s)
{
    s.locale = StringToLocale(j.at("lang").get<std::string>());
    j.at("grid").at("x").get_to(s.gridWidth);
    j.at("grid").at("y").get_to(s.gridHeight);
    j.at("plugin").at("number").get_to(s.pluginNumber);
    j.at("tie").get_to(s.tieMoveNumber);
}

void to_json(nlohmann::json &j, const Settings &s)
{
    j = nlohmann::json{
        { "lang", LocaleToString(s.locale) },
        { "grid", { { "x", s.gridWidth }, { "y", s.gridHeight } } },
        { "plugin", { { "number", s.pluginNumber } } },
        { "tie", s.tieMoveNumber },
    };
}

Configuration::Configuration()
{
    this->m_settings = {
        .locale = Locale::en_US,
        .gridWidth = 10,
        .gridHeight = 10,
        .pluginNumber = 2,
        .tieMoveNumber = 100,
    };
}

void Configuration::LoadConfiguration()
{
    std::filesystem::path settingsPath = "Resources/config.json";
    if (std::filesystem::is_regular_file(settingsPath)) {
        SPV_APP_INFO("Loading settings from file {}", settingsPath.string());
        std::ifstream settingsFile(settingsPath);
        nlohmann::json settingsJson = nlohmann::json::parse(settingsFile);
        this->m_settings = settingsJson.get<Settings>();
    }

    auto langPath = "Resources/Lang/" + localName[(int)this->m_settings.locale] + ".json";
    if (!std::filesystem::is_regular_file(langPath)) {
        SPV_APP_ERROR("Language file not found using default language");
        //TODO: Load default language
        return;
    }
    else {
        std::ifstream langFile(langPath);
        m_texts = nlohmann::json::parse(langFile);
    }
}

void Configuration::SetLocale(Locale locale)
{
    this->m_settings.locale = locale;
}

std::string Configuration::GetText(const char *key) const
{
    if (m_texts.contains(key))
        return m_texts[key].get<std::string>();
    return "<text-error>";
}

} // Namespace SPV