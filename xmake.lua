add_rules("mode.debug", "mode.release")

add_requires("spdlog", "sfml")

set_runtimes("MD")
set_languages("cxx17")
set_rundir("./bin/$(os)_$(arch)_$(mode)")
set_targetdir("./bin/$(os)_$(arch)_$(mode)")

set_project("SmartPawn")

target("SPEngine")
    set_version("0.0.1")
    set_kind("shared")

    add_files("src/spengine/*.cpp")
    add_files("src/spengine/engine/*.cpp")

    add_headerfiles("src/spengine/engine/*.h")
    add_headerfiles("src/spengine/*.h")

    add_includedirs("src/spengine", {public = true})
    --add_includedirs("src/spengine/engine", {public = true})
    --add_includedirs("src", {public = true})

    set_pcxxheader("src/spengine/SPpch.h")

    add_packages("spdlog")

    set_symbols("debug")

    if is_plat("windows") then
        add_defines("SP_PLATFORM_WIN")
    elseif is_plat("macos") then
        add_defines("SP_PLATFORM_DARWIN")
    end 
    add_defines("SP_EXPORT_DLL")

target_end()

target("SmartPawnViewer")
    set_version("0.0.1")
    set_kind("binary")
    add_deps("SPEngine")

    --add_linkdirs("bin/$(os)_$(arch)_$(mode)")

    --add_files("bin/$(os)_$(arch)_$(mode)/*.lib")
    --add_files("bin/$(os)_$(arch)_$(mode)/*.dll")
    add_files("src/smartpawnviewer/*.cpp")
    add_headerfiles("src/smartpawnviewer/*.h")

    add_packages("spdlog", "sfml") 
    add_syslinks("opengl32")

    set_symbols("debug")

    if is_plat("windows") then
        add_defines("SP_PLATFORM_WIN")
    elseif is_plat("macos") then
        add_defines("SP_PLATFORM_DARWIN")
    end 
target_end()