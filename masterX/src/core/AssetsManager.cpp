#include "mxpch.hpp"
#include "AssetsManager.hpp"

#include "Renderer/Shader.hpp"
#include "Renderer/Texture.hpp"

namespace mx
{
    std::unordered_map<std::string, Ref<Asset>> AssetsManager::m_assets;

    template<>
    AssetLoader<Shader> AssetLoader<Shader>::fromFile(const std::string& filename)
    {
        return AssetLoader<mx::Shader>([&](){
            return mx::Shader::Create(filename);
        });
    }

    template<>
    template<typename ...Args>
    AssetLoader<Shader> AssetLoader<Shader>::construct(Args&& ...args)
    {
        return AssetLoader<mx::Shader>([&](){
            return mx::Shader::Create(args...);
        });
    }

    template<>
    AssetLoader<Texture2D> AssetLoader<Texture2D>::fromFile(const std::string& filename)
    {
        return AssetLoader<mx::Texture2D>([&](){
            return mx::Texture2D::Create(filename);
        });
    }

    template<>
    template<typename ...Args>
    AssetLoader<Texture2D> AssetLoader<Texture2D>::construct(Args&& ...args)
    {
        return AssetLoader<mx::Texture2D>([&](){
            return mx::Texture2D::Create(args...);
        });
    }
}