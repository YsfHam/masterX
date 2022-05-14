project "glad"
	kind "StaticLib"
	language "C"

	location "%{wks.location}/build"
    targetdir "%{wks.location}/bin/bin/%{cfg.name}_%{cfg.architecture}"
    objdir "%{wks.location}/bin/obj/%{cfg.name}_%{cfg.architecture}"

	files
	{
		"src/glad.c"
	}

	includedirs "include"

	filter "configurations:Debug"
        defines "MX_DEBUG"
        symbols "On"
    filter "configurations:Release"
        optimize "On"