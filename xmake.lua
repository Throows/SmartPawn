add_rules("mode.debug", "mode.release")
add_rules("plugin.vsxmake.autoupdate")
add_requires("spdlog", "sfml", "pybind11", "python")
set_languages("cxx20")
set_rundir("./bin/$(os)_$(arch)_$(mode)")
set_targetdir("./bin/$(os)_$(arch)_$(mode)")
set_symbols("debug", "hidden")

if is_mode("release") then 
    set_runtimes("MD")
    if is_plat("windows") then
        add_cxxflags("/SUBSYSTEM:WINDOWS", "/ENTRY:WinMainCRTStartup")
    end 
elseif is_mode("debug") then
    set_runtimes("MDd")
    if is_plat("windows") then
        add_cxxflags("/SUBSYSTEM:CONSOLE", "/ENTRY:mainCRTStartup")
    end
end

set_project("SmartPawn")

target("SPEngine")
    set_version("0.0.1")
    set_kind("shared")

    add_headerfiles("src/SPEngine/**.hpp")
    add_includedirs("src/SPEngine", {public = true})
    add_files("src/SPEngine/**.cpp")
    add_packages("spdlog", "sfml", "pybind11", "python") 

    if is_plat("windows") then
        add_syslinks("opengl32")
        add_defines("SP_PLATFORM_WIN")
    elseif is_plat("macosx") then
        add_frameworks("CoreFoundation", "CoreGraphics", "CoreText", "CoreServices")
        add_defines("SP_PLATFORM_DARWIN")
    end 
    
target_end()

target("SmartPawnViewer")
    set_version("0.0.1")
    set_kind("binary")
    add_deps("SPEngine")

    add_headerfiles("src/smartpawnviewer/**.hpp")
    add_includedirs("src/smartpawnviewer")
    add_files("src/smartpawnviewer/**.cpp")
    set_pcxxheader("src/smartpawnviewer/Core/pch.hpp");
    add_packages("spdlog", "sfml", "pybind11", "python") 

    if is_plat("windows") then
        add_syslinks("opengl32")
        add_defines("SP_PLATFORM_WIN")
    elseif is_plat("macosx") then
        add_frameworks("CoreFoundation", "CoreGraphics", "CoreText", "CoreServices")
        add_defines("SP_PLATFORM_DARWIN")
    end
    
    after_build(function (target) 
        os.cp("$(projectdir)/resources/*", "$(projectdir)/bin/$(os)_$(arch)_$(mode)/resources/")
        os.cp("$(projectdir)/src/Plugins/*", "$(projectdir)/bin/$(os)_$(arch)_$(mode)/Plugins/")
        os.rm("$(projectdir)/bin/$(os)_$(arch)_$(mode)/Records/*")
    end)

target_end()
