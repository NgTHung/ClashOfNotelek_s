#include "Resources/TextureHolder.hpp"
#include "Utility/Logger.hpp"

TextureHolder::TextureHolder() {};
TextureHolder::~TextureHolder() {};

void TextureHolder::LoadDirectory()
{
    if (m_SelectedDirectory.empty())
    {
        LOG_ERROR("Selected directory is empty. Cannot load texture.");
        throw "Not properly used.";
    }
    std::filesystem::path Path(m_SelectedDirectory);
    if (!std::filesystem::is_directory(Path))
    {
        LOG_ERROR("Selected path is not a directory: {}", m_SelectedDirectory);
        throw "Directory not exist " + m_SelectedDirectory;
    }
    for (auto File : std::filesystem::directory_iterator(Path))
    {
        if (File.path().extension().string() == ".png")
        {
            LOG_DEBUG("Loading texture file: {}", File.path().string());
            LoadFile(File.path().string());
        }
    }
}

bool TextureHolder::LoadFile(const std::string &TexturePath)
{
    std::unique_ptr<sf::Texture> Texture = std::make_unique<sf::Texture>();
    std::filesystem::path Path(TexturePath);
    if (!Texture->loadFromFile(Path))
    {
        LOG_ERROR("Failed to load texture from file: {}", Path.string());
        return false;
    }
    AddTexture(Path.filename().string(), std::move(Texture));
    return true;
}

bool TextureHolder::AddTexture(const std::string &TextureName, std::unique_ptr<sf::Texture> Texture)
{
    auto InsertedTexture = m_TextureMap.insert(std::make_pair(TextureName, std::move(Texture)));
    if (!InsertedTexture.second)
    {
        LOG_ERROR("Texture {} already exists in the map.", TextureName);
        throw "Cannot insert texture " + TextureName;
    }
    return true;
}

const sf::Texture &TextureHolder::GetTexture(std::string TextureName) const
{
    auto SelectTexture = m_TextureMap.find(TextureName);
    assert(SelectTexture != m_TextureMap.end());
    return *SelectTexture->second;
};