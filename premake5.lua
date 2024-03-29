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
Includes["glad"] = "%{wks.location}/masterX/libs/glad/include"
Includes["Imgui"] = "%{wks.location}/masterX/libs/Imgui"
Includes["stbImage"] = "%{wks.location}/masterX/libs/stb_image"
Includes["glm"] = "%{wks.location}/masterX/libs/glm"

include "masterX/libs/GLFW"
include "masterX/libs/glad"
include "masterX/libs/Imgui"
include "masterX/libs/stb_image"

--include "sandbox"
include "mxge"
include "masterX"
