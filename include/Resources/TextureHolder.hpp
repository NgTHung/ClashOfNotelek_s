#pragma once
#include "Resources/ResourcesHolder.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <algorithm>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

struct ObjectInfo{
    sf::Vector2f Position;
    sf::IntRect Intrect;
};

class JsonObject{
public:
    JsonObject() = default;
    JsonObject(json JSON);
    ~JsonObject() = default;
    const ObjectInfo GetInfo();
    // void NextState();
private:
    json m_Json;
};

class TextureHolder : public ResourcesHolder
{
public:
    TextureHolder();
    virtual ~TextureHolder() override;
    virtual void LoadDirectory() override;
    virtual bool LoadFile(const std::string &FilePath) override;
    bool LoadJsonFile(const std::string &FilePath);
    const sf::Texture &GetTexture(std::string TextureName) const;

private:
    bool AddTexture(const std::string &TextureName, std::unique_ptr<sf::Texture> Texture);
    bool AddJson(const std::string &JsonName, JsonObject JSON);
    std::map<std::string, std::unique_ptr<sf::Texture>> m_TextureMap;
    std::map<std::string, JsonObject> m_JsonMap;
};

