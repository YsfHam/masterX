project "masterX"

    kind "StaticLib"
    language "C++"
    cppdialect "c++17"

    location "%{wks.location}/build"
    targetdir "%{wks.location}/bin/bin/%{cfg.name}_%{cfg.architecture}"
    objdir "%{wks.location}/bin/obj/%{cfg.name}_%{cfg.architecture}"

    pchheader "src/mxpch.hpp"
    pchsource "src/mxpch.cpp"

    files
    {
        "src/**.cpp"
    }

    links
    {
        "GLFW",
        "glad",
        "Imgui",


        "CoreFoundation.framework",
        "Cocoa.framework",
        "IOKit.framework",
        "CoreVideo.framework",
        "OpenGL.framework",
    }

    includedirs
    {
        "src",
        "%{Includes.spdlog}",
        "%{Includes.GLFW}",
        "%{Includes.glad}",
        "%{Includes.Imgui}",
    }