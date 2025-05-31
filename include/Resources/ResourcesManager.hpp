#pragma once
#include "Resources/FontHolder.hpp"
#include "Utility/ResourcesUtility.hpp"

class ResourcesManager
{
public:
    const FontHolder &GetFontHolder() const;
    const static ResourcesManager &GetManager();
    bool LoadFile(const ResourcesType Type, const std::string &Path);
    const std::vector<std::string> LoadFiles(ResourcesType Type, const std::vector<std::string> FileTable);
    void LoadDirectory(const std::string &DirectoryPath);

private:
    std::unique_ptr<FontHolder> m_FontHolder;
    ResourcesManager();
    ~ResourcesManager() = default;
};