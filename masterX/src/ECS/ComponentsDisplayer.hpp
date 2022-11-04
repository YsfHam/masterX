#pragma once

#include "components.hpp"
#include "ecs.hpp"

#include "Imgui/Imgui.hpp"

#include "core/Assert.hpp"

namespace mx
{
    class ComponentsDisplayer
    {
    public:

        template<typename T>
        void displayComponent(EntityID entity)
        {
            MX_CORE_ASSERT(false, "No known implementation for {}", typeid(T).name());
        }


        void displayComponents(EntityID entity);

    private:
        template<typename T, typename F>
        void drawComponent(const char *name, EntityID entity, F func)
        {
            ComponentID cmpID = EntityRegistry::getComponentID<T>();
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen;
            if (ImGui::TreeNodeEx(reinterpret_cast<void*>(cmpID), flags, "%s", name))
            {
                bool cmpRemoved = ImGui::Button("Remove Component");
                if (cmpRemoved)
                    EntityRegistry::removeComponent<T>(entity);

                if (!cmpRemoved)
                    func(EntityRegistry::getComponent<T>(entity));

                ImGui::TreePop();
            }
        }


        template<typename CmpsList>
        void displayComponentsFromList(EntityID entity)
        {
            using First = typename CmpsList::FirstCmp;
            using Rest = typename CmpsList::RestCmps;

            if constexpr (CmpsList::valid)
            {
                if (EntityRegistry::hasComponent<First>(entity))
                    displayComponent<First>(entity);
                
                displayComponentsFromList<Rest>(entity);
            }
        }
    };
}