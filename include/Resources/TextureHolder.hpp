#pragma once
#include "Resources/ResourcesHolder.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <algorithm>

class TextureHolder : public ResourcesHolder
{
public:
    TextureHolder();
    virtual ~TextureHolder() override;
    virtual void LoadDirectory() override;
    virtual bool LoadFile(const std::string &FilePath) override;
    const sf::Texture &GetTexture(std::string TextureName) const;

private:
    bool AddTexture(const std::string &TextureName, std::unique_ptr<sf::Texture> Texture);
    std::map<std::string, std::unique_ptr<sf::Texture>> m_TextureMap;
};