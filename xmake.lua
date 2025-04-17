add_rules("mode.debug", "mode.release")

set_languages("c++17")
set_warnings("all", "error")

add_includedirs("include")
add_includedirs("include/metal-cpp")
add_includedirs("include/metal-cpp-extensions")

add_frameworks("Foundation", "Metal", "MetalKit")

target("nebula")
    set_kind("binary")
    add_files("src/nebula/*.cpp")

target("learn-metal")
    set_kind("phony")
    add_deps("00-window", "01-primitive", "02-argbuffers", "03-animation", 
             "04-instancing", "05-perspective", "06-lighting", "07-texturing", 
             "08-compute", "09-compute-to-render", "10-frame-debugging")

target("00-window")
    set_kind("binary")
    add_files("src/learn-metal/00-window/*.cpp")

target("01-primitive")
    set_kind("binary")
    add_files("src/learn-metal/01-primitive/*.cpp")

target("02-argbuffers")
    set_kind("binary")
    add_files("src/learn-metal/02-argbuffers/*.cpp")

target("03-animation")
    set_kind("binary")
    add_files("src/learn-metal/03-animation/*.cpp")

target("04-instancing")
    set_kind("binary")
    add_files("src/learn-metal/04-instancing/*.cpp")

target("05-perspective")
    set_kind("binary")
    add_files("src/learn-metal/05-perspective/*.cpp")

target("06-lighting")
    set_kind("binary")
    add_files("src/learn-metal/06-lighting/*.cpp")

target("07-texturing")
    set_kind("binary")
    add_files("src/learn-metal/07-texturing/*.cpp")

target("08-compute")
    set_kind("binary")
    add_files("src/learn-metal/08-compute/*.cpp")

target("09-compute-to-render")
    set_kind("binary")
    add_files("src/learn-metal/09-compute-to-render/*.cpp")

target("10-frame-debugging")
    set_kind("binary")
    add_files("src/learn-metal/10-frame-debugging/*.cpp")



--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro definition
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

