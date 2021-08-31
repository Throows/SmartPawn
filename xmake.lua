add_rules("mode.debug", "mode.release")
add_rules("plugin.vsxmake.autoupdate")

--add_requires("spdlog", "glfw", "glad")
add_requires("spdlog", "sfml")

set_runtimes("MD")
set_languages("cxx17")
set_rundir("./bin/$(os)_$(arch)_$(mode)")
set_targetdir("./bin/$(os)_$(arch)_$(mode)")

set_project("SmartPawn")

target("SPEngine")
    set_version("0.0.1")
    set_kind("shared")

    add_headerfiles("src/SPEngine/**.h")
    add_includedirs("src/SPEngine", {public = true})
    add_files("src/SPEngine/**.cpp")

    --add_packages("spdlog", "glfw", "glad") 
    add_packages("spdlog", "sfml") 

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

target("SPIntelligence")
    set_version("0.0.1")
    set_kind("shared")
    add_deps("SPEngine")

    add_headerfiles("src/SPIntelligence/**.h")
    add_includedirs("src/SPIntelligence", {public = true})
    add_files("src/SPIntelligence/**.cpp")

    --add_packages("spdlog", "glfw", "glad") 
    add_packages("spdlog", "sfml") 
    
    set_runtimes(is_mode("debug") and "MDd" or "MD")

    if is_plat("windows") then
        add_syslinks("opengl32")
    elseif is_plat("macosx") then
        add_frameworks("CoreFoundation", "CoreGraphics", "CoreText", "CoreServices")
    end

    set_symbols("debug")

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
    add_includedirs("src/SPIntelligence")
    add_files("src/SmartPawnViewer/**.cpp")

    add_files("bin/windows_x64_debug/SPEngine.lib")


    set_pcxxheader("src/SmartPawnViewer/Core/pch.h");

    --add_packages("spdlog", "glfw", "glad") 
    add_packages("spdlog", "sfml") 

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
