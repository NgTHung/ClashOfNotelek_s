#include "Resources/ResourcesHolder.hpp"

ResourcesHolder::ResourcesHolder() = default;
ResourcesHolder::~ResourcesHolder() = default;
void ResourcesHolder::AddDirectory(const std::string &DirectoryPath, bool isSelected)
{
    m_DirectoryTable.insert(DirectoryPath);

    if (isSelected)
    {
        this->SelectDirectory(DirectoryPath);
    }
}
void ResourcesHolder::SelectDirectory(const std::string &DirectoryPath)
{
    m_SelectedDirectory = DirectoryPath;
}

std::vector<std::string> ResourcesHolder::LoadFiles(const std::vector<std::string> &FileTable)
{
    std::vector<std::string> LoadedFilesTable;
    for (const std::string &Name : FileTable)
    {
        if (LoadFile(Name))
        {
            LoadedFilesTable.push_back(Name);
        }
    }
    return LoadedFilesTable;
}

void ResourcesHolder::LoadDirectory(const std::string &DirectoryPath)
{
    AddDirectory(DirectoryPath, true);
    LoadDirectory();
}

void ResourcesHolder::ReloadDirectory(const std::string &DirectoryPath)
{
    SelectDirectory(DirectoryPath);
    LoadDirectory();
}
