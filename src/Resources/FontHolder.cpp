#include "Resources/FontHolder.hpp"
#include "Utility/Logger.hpp"
#include "Utility/Environment.hpp"

FontHolder::FontHolder() = default;
FontHolder::~FontHolder() = default;
bool FontHolder::AddFont(const std::string &FontName, std::unique_ptr<sf::Font> Font)
{
    auto InsertedFont = m_FontMap.insert(std::make_pair(FontName, std::move(Font)));
    if (!InsertedFont.second)
    {
        LOG_ERROR("Font {} already exists in the map.", FontName);
        throw std::runtime_error("Cannot insert font " + FontName);
    }
    return true;
}

sf::Font &FontHolder::GetFont(const std::string& FontName) const
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
        LOG_ERROR("Failed to load font from file: {}", Path.string());
        return false;
    }
    AddFont(Path.filename().string(), std::move(Font));
    return true;
}

void FontHolder::LoadDirectory()
{
    if (m_SelectedDirectory.empty())
    {
        LOG_ERROR("Selected directory is empty. Cannot load fonts.");
        throw std::invalid_argument("Not properly used.");
    }
    std::filesystem::path Path(m_SelectedDirectory);
    if (!std::filesystem::is_directory(Path))
    {
        LOG_ERROR("Selected path is not a directory: {}", m_SelectedDirectory);
        throw std::runtime_error("Directory not exist " + m_SelectedDirectory);
    }
    for (const auto& File : std::filesystem::directory_iterator(Path))
    {
        if (File.path().extension().string() == Environment::FontExtention)
        {
            LOG_DEBUG("Loading font file: {}", File.path().string());
            LoadFile(File.path().string());
        }
    }
}