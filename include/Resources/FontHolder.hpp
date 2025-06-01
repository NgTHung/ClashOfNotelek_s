#pragma once
#include "Resources/ResourcesHolder.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <algorithm>
class FontHolder : public ResourcesHolder
{
public:
    FontHolder();
    // FontHolder(const std::string DirectoryName);
    virtual ~FontHolder() override;
    virtual void LoadDirectory() override;
    virtual bool LoadFile(const std::string &FontPath) override;
    const sf::Font &GetFont(const std::string FontName) const;

private:
    bool AddFont(const std::string &FontName, std::unique_ptr<sf::Font> Font);
    std::map<std::string, std::unique_ptr<sf::Font>> m_FontMap;
};