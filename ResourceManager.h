# pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <cassert>

template<typename T>
class ResourceManager
{
public:
    T& get(const std::string& filename) const;

private:
    mutable std::map<std::string, std::unique_ptr<T>> m_resources;
};

template<typename T>
T& ResourceManager<T>::get(const std::string& filename) const
{
    auto found = m_resources.find(filename);
    if (found == m_resources.end()) {
        std::unique_ptr<T> resource(new T());
        if (!resource->loadFromFile(filename))
            throw std::runtime_error("ResourceManager failed to load '" + filename + "'");

        auto inserted = m_resources.emplace(std::make_pair(filename, std::move(resource)));
        assert(inserted.second);
        return *inserted.first->second;
    }
    return *found->second;
}

template<>
inline sf::Music& ResourceManager<sf::Music>::get(const std::string& filename) const
{
    auto found = m_resources.find(filename);
    if (found == m_resources.end()) {
        std::unique_ptr<sf::Music> resource(new sf::Music());
        if (!resource->openFromFile(filename))
            throw std::runtime_error("ResourceManager failed to open '" + filename + "'");

        auto inserted = m_resources.emplace(std::make_pair(filename, std::move(resource)));
        assert(inserted.second);
        return *inserted.first->second;
    }
    return *found->second;
}