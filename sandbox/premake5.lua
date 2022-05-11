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
    }

    libdirs
    {
    }

    links
    {
        "masterX",
        "GLFW",
        "CoreFoundation.framework",
        "Cocoa.framework",
        "IOKit.framework",
        "CoreVideo.framework",
        "OpenGL.framework",

    }