project "math3D"

  kind "StaticLib"
  language "C++"
  cppdialect "c++17"
  location "%{wks.location}/build"
  targetdir "%{wks.location}/bin/bin/%{cfg.name}_%{cfg.architecture}"
  objdir "%{wks.location}/bin/obj/%{cfg.name}_%{cfg.architecture}"
  files
  {
      "math3D/prv/math3D/**.cpp"
  }

  includedirs "math3D/prv"

  defines "USE_INSTRINSICS"

  filter "configurations:Debug"
    symbols "on"
  filter "configurations:Release"
    optimize "Full"
