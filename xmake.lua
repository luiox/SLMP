-- define project
set_project("SLMP")
set_xmakever("2.3.2")
set_version("1.0.0", {build = "%Y%m%d%H%M"})

-- set common flags
--set_warnings("all", "error")
set_languages("c99")
--add_cxflags("-Wno-error=deprecated-declarations", "-fno-strict-aliasing", "-Wno-error=expansion-to-defined","-Wno-error=unused-variable")
--add_mxflags("-Wno-error=deprecated-declarations", "-fno-strict-aliasing", "-Wno-error=expansion-to-defined")

-- add build modes
add_rules("mode.release", "mode.debug")

target("test")
    set_kind("binary")
    add_files("test/*.cpp")
