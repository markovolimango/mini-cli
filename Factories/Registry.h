#ifndef CLI_REGISTRY_H
#define CLI_REGISTRY_H

#include <map>
#include <memory>
#include <string>

class IFactory;

class Registry
{
public:
    static IFactory* getFactory(const std::string& name);

    static void registerFactory(const std::string& name, IFactory* factory);

private:
    static std::unique_ptr<Registry> instance;

    std::map<std::string, IFactory*> m_map;

    static Registry* getInstance();
};


inline IFactory* Registry::getFactory(const std::string& name)
{
    return getInstance()->m_map[name];
}

inline void Registry::registerFactory(const std::string& name, IFactory* factory)
{
    getInstance()->m_map.insert({name, factory});
}

inline Registry* Registry::getInstance()
{
    if (instance == nullptr)
        instance = std::make_unique<Registry>();
    return instance.get();
}

#endif
