#pragma once
#include <string>
#include <unordered_set>
#include <vector>
class ResourcesHolder
{
public:
    ResourcesHolder();
    virtual ~ResourcesHolder();
    virtual void LoadDirectory() = 0;
    virtual bool LoadFile(const std::string &FilePath) = 0;
    void LoadDirectory(const std::string &DirectoryPath);
    const std::vector<std::string> LoadFiles(const std::vector<std::string> FileTable);
    void AddDirectory(const std::string &DirectoryPath, bool isSelected = false);
    void SelectDirectory(const std::string &DirectoryPath);
    void ReloadDirectory(const std::string &DirectoryPath);

protected:
    std::string m_SelectedDirectory;
    std::unordered_set<std::string> m_DirectoryTable;
};