#include "Resources/AudioHolder.hpp"
#include "Utility/Logger.hpp"
#include "Utility/Environment.hpp"
#include <filesystem>
#include <stdexcept>

AudioHolder::AudioHolder() {
    m_MusicMap.clear();
}

AudioHolder::~AudioHolder() {}

void AudioHolder::LoadDirectory()
{
    if (m_SelectedDirectory.empty())
    {
        LOG_ERROR("Selected directory is empty. Cannot load music.");
        throw std::runtime_error("Not properly used.");
    }
    std::filesystem::path Path(m_SelectedDirectory);

    if (!std::filesystem::is_directory(Path))
    {
        LOG_ERROR("Selected path is not a directory: {}", m_SelectedDirectory);
        throw std::runtime_error("Directory not exist " + m_SelectedDirectory);
    }

    for (auto const& File : std::filesystem::directory_iterator(Path))
    {
        std::string FileExtension = File.path().extension().string();
        if (FileExtension == Environment::AudioExtention)
        {
            LOG_DEBUG("Loading music file: {}", File.path().string());
            LoadFile(File.path().string());
        }
    }
}

bool AudioHolder::LoadFile(const std::string& FilePath)
{
    std::filesystem::path path(FilePath);
    std::string musicID = path.stem().string();

    LOG_DEBUG("Loading music file: {}. Attempting to add with ID: {}", FilePath, musicID);
    m_Sound.insert({musicID,sf::SoundBuffer(FilePath)});
    return AddMusic(musicID, FilePath);
}

const sf::SoundBuffer& AudioHolder::GetSoundBuffer(const std::string& musicName) const
{
    auto selectMusic = m_MusicMap.find(musicName);
    if (selectMusic == m_MusicMap.end()) {
        LOG_ERROR("Music {} not found in soundmap.", musicName);
        // Throw an exception or return a reference to an empty/default string
        // Throwing is safer as it prevents a dangling reference
        throw std::out_of_range("Music name not found in soundmap: " + musicName);
    }
    return m_Sound.at(musicName);
}


// Update GetMusic to return the file path
const std::string& AudioHolder::GetMusic(const std::string& musicName) const
{
    auto selectMusic = m_MusicMap.find(musicName);
    if (selectMusic == m_MusicMap.end()) {
        LOG_ERROR("Music {} not found in map.", musicName);
        // Throw an exception or return a reference to an empty/default string
        // Throwing is safer as it prevents a dangling reference
        throw std::out_of_range("Music name not found in map: " + musicName);
    }
    return selectMusic->second;
}

bool AudioHolder::AddMusic(const std::string& musicName, const std::string& filePath){
    auto [iterator, success] = m_MusicMap.insert(std::make_pair(musicName, filePath));
    if (!success)
    {
        LOG_ERROR("Music {} already exists in the map.", musicName);
        throw std::runtime_error("Cannot insert music " + musicName);
    }
    LOG_DEBUG("Loaded music: {}", musicName);
    return true;
}