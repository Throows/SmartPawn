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

    add_headerfiles("src/SPEngine/**.h")
    add_includedirs("src/SPEngine", {public = true})
    add_files("src/SPEngine/**.cpp")
    add_packages("spdlog", "brew::sfml", "brew::pybind11", "python") 

    if is_plat("windows") then
        add_syslinks("opengl32")
    elseif is_plat("macosx") then
        add_frameworks("CoreFoundation", "CoreGraphics", "CoreText", "CoreServices")
    end

    set_symbols("debug", "hidden")
    set_runtimes("MDd")

    if is_plat("windows") then
        add_defines("SP_PLATFORM_WIN")
    elseif is_plat("macos") then
        add_defines("SP_PLATFORM_DARWIN")
    end
    
    after_build(function (target) 
        os.cp("$(projectdir)\\resources\\**", "$(projectdir)\\bin\\$(os)_$(arch)_$(mode)\\resources\\")
    end)

    add_defines("DLL_EXPORT")
    
target_end()

target("SmartPawnViewer")
    set_version("0.0.1")
    set_kind("binary")
    add_deps("SPEngine")

    add_headerfiles("src/SmartPawnViewer/**.h")
    add_includedirs("src/SmartPawnViewer")
    add_files("src/SmartPawnViewer/**.cpp")
    set_pcxxheader("src/SmartPawnViewer/Core/pch.h");
    add_packages("spdlog", "brew::sfml", "brew::pybind11", "python") 

    if is_plat("windows") then
        add_syslinks("opengl32")
    elseif is_plat("macosx") then
        add_frameworks("CoreFoundation", "CoreGraphics", "CoreText", "CoreServices")
    end

    set_symbols("debug", "hidden")

    if is_plat("windows") then
        add_defines("SP_PLATFORM_WIN")
    elseif is_plat("macos") then
        add_defines("SP_PLATFORM_DARWIN")
    end
    
    after_build(function (target) 
        os.cp("$(projectdir)\\resources\\**", "$(projectdir)\\bin\\$(os)_$(arch)_$(mode)\\resources\\")
    end)

target_end()
