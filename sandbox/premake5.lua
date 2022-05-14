project "sandbox"

    kind "ConsoleApp"
    language "C++"
    cppdialect "c++17"

    location "%{wks.location}/build"
    targetdir "%{wks.location}/bin/bin/%{cfg.name}_%{cfg.architecture}"
    objdir "%{wks.location}/bin/obj/%{cfg.name}_%{cfg.architecture}"

    files
    {
        "src/**.cpp",
    }

    includedirs
    {
        "%{wks.location}/masterX/src",
        "%{Includes.spdlog}",
        "%{Includes.GLFW}",
        "%{Includes.Imgui}"
    }

    links
    {
        "masterX",
        "GLFW",
        "glad",
        "Imgui",


        "CoreFoundation.framework",
        "Cocoa.framework",
        "IOKit.framework",
        "CoreVideo.framework",
        "OpenGL.framework",

    }

    filter "configurations:Debug"
        defines "MX_DEBUG"
        symbols "On"
    filter "configurations:Release"
        optimize "On"