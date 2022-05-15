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
        "%{Includes.Imgui}",
        "%{Includes.math3D}",
    }

    links
    {
        "masterX",
        "GLFW",
        "glad",
        "Imgui",
        "math3D",

        "CoreFoundation.framework",
        "Cocoa.framework",
        "IOKit.framework",
        "CoreVideo.framework",
        "OpenGL.framework",

    }

    defines
    {
        "USE_INSTRINSICS"
    }

    filter "configurations:Debug"
        defines "MX_DEBUG"
        symbols "On"
    filter "configurations:Release"
        optimize "On"