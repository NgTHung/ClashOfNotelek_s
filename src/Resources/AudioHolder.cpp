#include <Resources/AudioHolder.hpp>
#include "Utility/Logger.hpp"
#include "Utility/Enviroment.hpp"

AudioHolder::AudioHolder(){}
AudioHolder::~AudioHolder(){}
void AudioHolder::LoadDirectory()
{
    if (m_SelectedDirectory.empty())
    {
        LOG_ERROR("Selected directory is empty. Cannot load Sound.");
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
        std::string FilePath = File.path().extension().string();
        if (FilePath == Enviroment::AudioExtention)
        {
            LOG_DEBUG("Loading Sound file: {}", File.path().string());
            LoadFile(File.path().string());
        }
    }
}
bool AudioHolder::LoadFile(const std::string &FilePath)
{
    std::unique_ptr<sf::Sound> Sound = std::make_unique<sf::Sound>();
    std::filesystem::path Path(FilePath);
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(Path))
    {
        LOG_ERROR("Failed to load Sound from file: {}", Path.string());
        return false;
    }
    Sound->setBuffer(buffer);
    AddSound(Path.filename().string(), std::move(Sound));
    return true;
}
const sf::Sound &AudioHolder::GetSound(std::string SoundName) const
{
}
bool AudioHolder::AddSound(const std::string &SoundName, std::unique_ptr<sf::Sound> n_Sound){
    auto InsertSound = m_AudioMap.insert(std::make_pair(SoundName, std::move(n_Sound)));
    if (!InsertSound.second)
    {
        LOG_ERROR("Sound {} already exists in the map.", SoundName);
        throw "Cannot insert Sound " + SoundName;
    }
    return true;
}