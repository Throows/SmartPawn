add_rules("mode.debug", "mode.release")
add_rules("plugin.vsxmake.autoupdate")
add_requires("spdlog", "sfml", "pybind11", "python")
set_languages("c89", "cxx20")
set_rundir("./bin/$(os)_$(arch)_$(mode)")
set_targetdir("./bin/$(os)_$(arch)_$(mode)")
set_warnings("allextra")

set_allowedplats("windows", "macosx")
set_allowedmodes("debug", "release")
set_defaultmode("debug")

if is_mode("release") then 
    set_runtimes("MD")
  set_symbols("debug", "hidden")
else 
    set_runtimes("MDd")
end

set_project("SmartPawn")

target("SmartPawnViewer")
    set_version("1.0.1")
    set_kind("binary")

    add_headerfiles("src/smartpawnviewer/**.hpp")
    add_includedirs("src/smartpawnviewer")
    add_files("src/smartpawnviewer/**.cpp")
    set_pcxxheader("src/smartpawnviewer/Core/pch.hpp");
    add_packages("spdlog", "sfml", "pybind11", "python") 

    if is_plat("windows") then
        add_syslinks("opengl32")
        add_defines("SP_PLATFORM_WIN")
        if is_mode("release") then
            add_cxxflags("/SUBSYSTEM:WINDOWS", {force = true})
            add_cxxflags("/ENTRY:WinMainCRTStartup", {force = true})
            add_defines("WIN_START")
        else 
            add_cxxflags("/SUBSYSTEM:CONSOLE", {force = true})
            add_cxxflags("/ENTRY:mainCRTStartup", {force = true})
        end
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