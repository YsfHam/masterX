workspace "masterX"

architecture "x64"

configurations
{
  "Debug",
  "Release"
}

Includes = {}
Includes["spdlog"] = "%{wks.location}/masterX/libs/spdlog/include"
Includes["GLFW"] = "%{wks.location}/masterX/libs/GLFW/include"


Libs = {}

include "masterX/libs/GLFW"

include "sandbox"
include "masterX"

filter "configurations:Debug"
  defines "MX_DEBUG"
  symbols "On"
filter "configurations:Release"
  optimize "On"
