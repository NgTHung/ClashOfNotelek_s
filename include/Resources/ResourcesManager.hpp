#pragma once
#include "Resources/FontHolder.hpp"
#include "Resources/TextureHolder.hpp"
#include "Resources/AudioHolder.hpp"
#include "Utility/ResourcesUtility.hpp"

class ResourcesManager
{
public:
    const FontHolder &GetFontHolder() const;
    const TextureHolder &GetTextureHolder() const;
    const AudioHolder &GetAudioHolder() const;
    const static ResourcesManager &GetManager();
    bool LoadFile(ResourcesType Type, const std::string &Path) const;
    std::vector<std::string> LoadFiles(ResourcesType Type,const std::vector<std::string> &FileTable) const;
    void LoadDirectory(const std::string &DirectoryPath);
private:
    std::unique_ptr<FontHolder> m_FontHolder;
    std::unique_ptr<TextureHolder> m_TextureHolder;
    std::unique_ptr<AudioHolder> m_AudioHolder;
    ResourcesManager();
    ~ResourcesManager() = default;
};