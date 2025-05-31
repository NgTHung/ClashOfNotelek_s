#include "Resources/ResourcesManager.hpp"

const FontHolder &ResourcesManager::GetFontHolder() const
{
    return *m_FontHolder;
}

const ResourcesManager &ResourcesManager::GetManager()
{
    static ResourcesManager m_Instance{};
    return m_Instance;
}

ResourcesManager::ResourcesManager()
{
    m_FontHolder = std::make_unique<FontHolder>();
    m_FontHolder->AddDirectory("assets/fonts", true);
    m_FontHolder->LoadDirectory();
}

bool ResourcesManager::LoadFile(ResourcesType Type, const std::string &File)
{
    switch (Type)
    {
    case ResourcesType::Font:
    {
        return m_FontHolder->LoadFile(File);
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