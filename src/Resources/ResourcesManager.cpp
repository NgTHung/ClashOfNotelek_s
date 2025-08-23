#include "Resources/ResourcesManager.hpp"
#include "Utility/Logger.hpp"
// #include <SFML/>
#include "Utility/Environment.hpp"

const FontHolder &ResourcesManager::GetFontHolder() const
{
    return *m_FontHolder;
}

const TextureHolder &ResourcesManager::GetTextureHolder() const
{
    return *m_TextureHolder;
}
const AudioHolder &ResourcesManager::GetAudioHolder() const
{
    return *m_AudioHolder;
}

const ResourcesManager &ResourcesManager::GetManager()
{
    static ResourcesManager m_Instance{};
    return m_Instance;
}

ResourcesManager::ResourcesManager()
{
    // Load Font
    m_FontHolder = std::make_unique<FontHolder>();
    m_FontHolder->AddDirectory(Environment::FontDirectory, true);
    m_FontHolder->LoadDirectory();

    // Load Texture
    m_TextureHolder = std::make_unique<TextureHolder>();
    m_TextureHolder->AddDirectory(Environment::TextureDirectory, true);
    m_TextureHolder->LoadDirectory();

    // Load Sound
    m_AudioHolder = std::make_unique<AudioHolder>();
    m_AudioHolder->AddDirectory(Environment::AudioDirectory, true);
    m_AudioHolder->LoadDirectory();

    LOG_DEBUG("Play Sound demo");
}

bool ResourcesManager::LoadFile(const ResourcesType Type, const std::string &Path) const {
    switch (Type)
    {
    case ResourcesType::Font:
    {
        return m_FontHolder->LoadFile(Path);
    }
    case ResourcesType::Texture:
    {
        return m_TextureHolder->LoadFile(Path);
    }
    default:
        break;
    }
    return false;
}

std::vector<std::string> ResourcesManager::LoadFiles(ResourcesType Type, const std::vector<std::string>& FileTable) const {
    switch (Type)
    {
    case ResourcesType::Font:
    {
        return m_FontHolder->LoadFiles(FileTable);
    }
    default:
        break;
    }
    return {};
}

void ResourcesManager::LoadDirectory(const std::string &DirectoryPath) {
    if (m_TextureHolder)
    {
        m_TextureHolder->AddDirectory(DirectoryPath, true);
        m_TextureHolder->LoadDirectory();
    }
    if (m_FontHolder)
    {
        m_FontHolder->AddDirectory(DirectoryPath, true);
        m_FontHolder->LoadDirectory();
    }
}
