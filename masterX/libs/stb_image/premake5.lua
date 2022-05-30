project "stb_image"

  kind "StaticLib"
  language "C++"
  
  location "%{wks.location}/build"
  targetdir "%{wks.location}/bin/bin/%{cfg.name}_%{cfg.architecture}"
  objdir "%{wks.location}/bin/obj/%{cfg.name}_%{cfg.architecture}"
  files "**.cpp"