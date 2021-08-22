project "sita"
    location "sita"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir(tdir)
    objdir(odir)

    files
    {
        "%{prj.name}/include/**.h",
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/**.c",
        "%{prj.name}/vendor/**.cpp",
        "%{prj.name}/vendor/**.h",
    }

    sysincludedirs
    {
        "vendor/src",
        "vendor/include",
        "%{prj.name}/vendor",
    }

    includedirs
    {
        "%{prj.name}/include",
    }

	postbuildcommands
	{
		"python ../tools/_postbuild.py project=%{prj.name}",
		"{COPY} %{prj.name}.build.meta ../" .. tdir,
	}

    filter "system:windows"
        systemversion "latest"

        files
        {
            "%{prj.name}/vendor/**.natvis",
        }

        defines
        {
            "SITA_WIN"
        }

    filter "system:linux"
        links
        {
            "spdlog",
        }

        defines
        {
            "SITA_LINUX"
        }

    filter "configurations:debug"
        runtime "Debug"
        symbols "on"

        defines
        {
            "SITA_DEBUG"
        }

    filter "configurations:release"
        runtime "Release"
        symbols "off"
        optimize "on"

		defines
        {
            "SITA_RELEASE"
        }
