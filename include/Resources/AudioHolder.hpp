#pragma once
#include <SFML/Audio.hpp>
#include <memory>
#include "Resources/ResourcesHolder.hpp"
#include <map>
#include <string>

class AudioHolder : public ResourcesHolder
{
public:
    AudioHolder();
    virtual ~AudioHolder() override;
    virtual void LoadDirectory() override;
    virtual bool LoadFile(const std::string &FilePath) override;

    // Change the return type to a const string reference
    const std::string& GetMusic(const std::string& musicName) const;

private:
    bool AddMusic(const std::string& musicName, const std::string& filePath);

    std::map<std::string, std::string> m_MusicMap;
};