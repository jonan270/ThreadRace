workspace "workspace"
   configurations { "Debug", "Release" }

project "ThreadRace"
    kind "ConsoleApp"
    language "C++"
    location "./"
    targetdir "bin/%{cfg.buildcfg}"

    files {"src/**.c", "src/**.cpp", "src/**.h", "src/**.hpp"}

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
