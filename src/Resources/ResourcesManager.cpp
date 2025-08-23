#include "Resources/ResourcesManager.hpp"
#include "Utility/Enviroment.hpp"
#include "Utility/Logger.hpp"
// #include <SFML/>

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
    m_FontHolder->AddDirectory(Enviroment::FontDirectory, true);
    m_FontHolder->LoadDirectory();

    // Load Texture
    m_TextureHolder = std::make_unique<TextureHolder>();
    m_TextureHolder->AddDirectory(Enviroment::TextureDirectory, true);
    m_TextureHolder->LoadDirectory();

    // Load Sound
    m_AudioHolder = std::make_unique<AudioHolder>();
    m_AudioHolder->AddDirectory(Enviroment::AudioDirectory, true);
    m_AudioHolder->LoadDirectory();

    LOG_DEBUG("Play Sound demo");
}

bool ResourcesManager::LoadFile(ResourcesType Type, const std::string &File)
{
    switch (Type)
    {
    case ResourcesType::Font:
    {
        return m_FontHolder->LoadFile(File);
    }
    case ResourcesType::Texture:
    {
        return m_TextureHolder->LoadFile(File);
    }
    default:
        break;
    }
    return false;
}

const std::vector<std::string> ResourcesManager::LoadFiles(ResourcesType Type, const std::vector<std::string> FileTable)
{
    switch (Type)
    {
    case ResourcesType::Font:
    {
        return m_FontHolder->LoadFiles(FileTable);
    }
    default:
        break;
    }
    return std::vector<std::string>();
}