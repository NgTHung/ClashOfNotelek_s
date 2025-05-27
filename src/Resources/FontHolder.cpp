#include "Resources/FontHolder.hpp"
FontHolder::FontHolder() {};
FontHolder::~FontHolder() {
};
bool FontHolder::AddFont(const std::string &FontName, std::unique_ptr<sf::Font> Font)
{
    auto InsertedFont = m_FontMap.insert(std::make_pair(FontName, std::move(Font)));
    if (!InsertedFont.second)
    {
        throw "Cannot insert font " + FontName;
    }
    m_FontTable.push_back(FontName);
    return true;
}

sf::Font &FontHolder::GetFont(const std::string FontName)
{
    auto SelectedFont = m_FontMap.find(FontName);
    assert(SelectedFont != m_FontMap.end());

    return *SelectedFont->second;
}
const sf::Font &FontHolder::GetFont(const std::string FontName) const
{
    auto SelectedFont = m_FontMap.find(FontName);
    assert(SelectedFont != m_FontMap.end());

    return *SelectedFont->second;
}

bool FontHolder::LoadFile(const std::string &FontPath)
{
    std::unique_ptr<sf::Font> Font = std::make_unique<sf::Font>();
    std::filesystem::path Path(FontPath);
    if (!Font->openFromFile(Path))
    {
        return false;
    }
    AddFont(Path.filename().string(), std::move(Font));
    return true;
}

void FontHolder::LoadDirectory()
{
    if (m_SelectedDirectory.empty())
    {
        throw "Not properly used.";
    }
    std::filesystem::path Path(m_SelectedDirectory);
    if (!std::filesystem::is_directory(Path))
    {
        throw "Directory not exist " + m_SelectedDirectory;
    }
    for (auto File : std::filesystem::directory_iterator(Path))
    {
        if (File.path().extension().string() == ".ttf")
        {
            LoadFile(File.path().string());
        }
    }
}