#include "LocaleText.hpp"
#include <fstream>
#include <format>

static std::string localName[] = {
    "en_US",
    "fr_FR",
};

namespace SPV
{

LocaleText::LocaleText(Locale locale) 
    : m_locale(locale)
{
}

LocaleText::~LocaleText()
{
}

void LocaleText::SetupLocale()
{
    auto filePath = "Resources/Lang/" + localName[(int)this->m_locale] + ".json";
    std::ifstream file(filePath);
    m_json = nlohmann::json::parse(file);
}

void LocaleText::SetLocale(Locale locale)
{
    this->m_locale = locale;
}

std::string LocaleText::GetText(const char *key) const
{
    if (m_json.contains(key))
        return m_json[key].get<std::string>();
    return "<text-error>";
}

std::string& LocaleText::LocaleToString(Locale locale)
{
    return localName[(int)locale];
}

} // Namespace SPV