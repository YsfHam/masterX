#pragma once

#include "mxpch.hpp"
#include "utils/types.hpp"
#include "core/Assert.hpp"

namespace mx
{
    class Asset
    {
    public:
        virtual ~Asset() = default;
        virtual std::string getName() const = 0;
    };

    template<typename T>
    class AssetLoader
    {
    public:
        AssetLoader(const std::function<Ref<T>()>& loader)
            : m_loader(loader)
        {}
        Ref<T> load() const
        {
            return m_loader();
        }

        static AssetLoader<T> fromFile(const std::string& filename)
        {
            MX_CORE_ASSERT(false, "No known implementation for {}", typeid(T).name());
        }
        template<typename ...Args>
        static AssetLoader<T> construct(Args&& ...args)
        {
            MX_CORE_ASSERT(false, "No known implementation for {}", typeid(T).name());
        }

    private:
        std::function<Ref<T>()> m_loader;
    };

    class AssetsManager
    {
    public:

        static void addAsset(const std::string& assetName, const Ref<Asset>& asset)
        {
            MX_CORE_ASSERT(m_assets.find(assetName) == m_assets.end(), "Asset {} already exists", assetName);
            m_assets[assetName] = asset;
        }

        static void addAsset(Ref<Asset>& asset)
        {
            addAsset(asset->getName(), asset);
        }

        template<typename T>
        static Ref<T> loadAsset(const std::string& assetName, const AssetLoader<T>& loader)
        {
            Ref<T> asset = loader.load();
            addAsset(assetName, asset);

            return asset;
        }

        template<typename T>
        static Ref<T> loadAsset(const AssetLoader<T>& loader)
        {
            Ref<T> asset = loader.load();
            addAsset(asset->getName(), asset);
            return asset;
        }


        template <typename T>
        static Ref<T> getAsset(const std::string& assetName)
        {
            MX_CORE_ASSERT(m_assets.find(assetName) != m_assets.end(), "Asset {} does not exist", assetName);
            return std::static_pointer_cast<T>(m_assets[assetName]);
        }

        static void clearAssets()
        {
            m_assets.clear();
        }

    private:
        static std::unordered_map<std::string, Ref<Asset>> m_assets;
    };
}