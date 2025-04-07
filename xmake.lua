---------------------------------
--! @file xmake.lua
--! @author Argore
--! @brief Template C++ configuration
--! @version 0.1
--! @date 2025-04-04
--! 
--! @copyright Copyright (c) 2025 Argore
---------------------------------

set_languages("clatest", "cxxlatest")
add_requires("libsdl")

add_rules "mode.debug"
add_rules "mode.release"

target "soggy"
    set_kind "binary" 
    
    set_basename "soggy_$(mode)_$(arch)"

    set_targetdir "bin"
    set_objectdir "build/obj"
    
    add_includedirs "src/"
    add_headerfiles{ "src/**.h", "src/**.hpp" }
    add_files{ "src/**.c", "src/**.cpp" }

    add_packages("libsdl")
target_end()
