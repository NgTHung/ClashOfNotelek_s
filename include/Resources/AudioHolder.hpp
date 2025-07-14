#pragma once
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <memory>
#include <Resources/ResourcesHolder.hpp>
#include <map>
#include <fstream>

class AudioHolder : public ResourcesHolder
{
public:
    AudioHolder();
    virtual ~AudioHolder() override;
    virtual void LoadDirectory() override;
    virtual bool LoadFile(const std::string &FilePath) override;
    // bool LoadJsonFile(const std::string &FilePath);
    const sf::Sound &GetSound(std::string SoundName) const;
private:
    bool AddSound(const std::string &AudioName, std::unique_ptr<sf::Sound> n_Sound);
    std::map<std::string, std::unique_ptr<sf::Sound>> m_AudioMap;
};