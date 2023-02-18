add_rules("mode.debug", "mode.release")
add_rules("plugin.vsxmake.autoupdate")
add_requires("spdlog", "brew::sfml", "brew::pybind11", "python")
set_runtimes("MD")
set_languages("cxx20")
set_rundir("./bin/$(os)_$(arch)_$(mode)")
set_targetdir("./bin/$(os)_$(arch)_$(mode)")

set_project("SmartPawn")

target("SPEngine")
    set_version("0.0.1")
    set_kind("shared")

    add_headerfiles("src/SPEngine/**.hpp")
    add_includedirs("src/SPEngine", {public = true})
    add_files("src/SPEngine/**.cpp")
    add_packages("spdlog", "brew::sfml", "brew::pybind11", "python") 

    if is_plat("windows") then
        add_syslinks("opengl32")
        add_defines("SP_PLATFORM_WIN")
    elseif is_plat("macosx") then
        add_frameworks("CoreFoundation", "CoreGraphics", "CoreText", "CoreServices")
        add_defines("SP_PLATFORM_DARWIN")
    end

    set_symbols("debug", "hidden")
    set_runtimes("MDd")
    
    after_build(function (target) 
        os.cp("$(projectdir)/resources/**", "$(projectdir)/bin/$(os)_$(arch)_$(mode)/resources/")
    end)
    
target_end()

target("SmartPawnViewer")
    set_version("0.0.1")
    set_kind("binary")
    add_deps("SPEngine")

    add_headerfiles("src/smartpawnviewer/**.hpp")
    add_includedirs("src/smartpawnviewer")
    add_files("src/smartpawnviewer/**.cpp")
    set_pcxxheader("src/smartpawnviewer/Core/pch.hpp");
    add_packages("spdlog", "brew::sfml", "brew::pybind11", "python") 

    if is_plat("windows") then
        add_syslinks("opengl32")
        add_defines("SP_PLATFORM_WIN")
    elseif is_plat("macosx") then
        add_frameworks("CoreFoundation", "CoreGraphics", "CoreText", "CoreServices")
        add_defines("SP_PLATFORM_DARWIN")
    end

    set_symbols("debug", "hidden")
    
    after_build(function (target) 
        os.cp("$(projectdir)/resources/**", "$(projectdir)/bin/$(os)_$(arch)_$(mode)/resources/")
    end)

target_end()
