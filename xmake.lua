set_languages("c++23")
add_rules("mode.debug")
add_rules("mode.release")
add_rules("mode.releasedbg")
add_requires("glfw")

target("live2d-demo")
    set_kind("binary")
    set_exceptions("cxx")
    add_files("src/**.cpp", "src/**.cppm")
    add_headerfiles("src/**.hpp", "src/**.h")
    add_headerfiles("include/**.hpp", "include/**.h")
    add_sysincludedirs("include")
    set_policy("build.c++.modules", true)
    add_packages("glfw")
    if is_plat("windows") then
        add_sysincludedirs("include/platform/windows")
        add_syslinks("lib/windows/Live2DCubismCore.lib")
        add_defines("CSM_TARGET_WIN_GL=1")
    else
        if is_plat("linux") then
            add_syslinks("lib/linux/libLive2DCubismCore.a")
            add_defines("CSM_TARGET_LINUX_GL=1")
        elseif is_plat("macosx") then
            add_syslinks("lib/macos/libLive2DCubismCore.a")
            add_defines("CSM_TARGET_MAC_GL=1")
        end
        add_sysincludedirs("include/platform/unix")
    end
