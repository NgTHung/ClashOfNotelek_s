#pragma once
#include "Resources/ResourcesHolder.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>

class FontHolder : public ResourcesHolder {
public:
    FontHolder();

    // FontHolder(const std::string DirectoryName);
    ~FontHolder() override;

    void LoadDirectory() override;

    bool LoadFile(const std::string &FontPath) override;

    sf::Font &GetFont(const std::string &FontName) const;

private:
    bool AddFont(const std::string &FontName, std::unique_ptr<sf::Font> Font);

    std::map<std::string, std::unique_ptr<sf::Font> > m_FontMap;
};
