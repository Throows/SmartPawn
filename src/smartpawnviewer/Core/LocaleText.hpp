#pragma once
#include <nlohmann/json.hpp>
#include <string>

namespace SPV
{

enum Locale {
    en_US,
    fr_FR,
};

class LocaleText
{
public:
    LocaleText(Locale locale);
    ~LocaleText();

    void SetupLocale();

    const Locale& GetLocale() const { return m_locale; }
    void SetLocale(Locale locale);

    std::string GetText(const char* key) const;
    template <typename... Args>
    std::string GetFormatedText(const char* key, Args&&... args) const { return fmt::format(GetText(key), std::forward<Args>(args)...); }

private:
    Locale m_locale;
    nlohmann::json m_json;

    std::string& LocaleToString(Locale locale);
};

} // Namespace SPV
