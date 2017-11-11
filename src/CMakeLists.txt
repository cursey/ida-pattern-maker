set(SRC 
    Plugin.hpp
    Plugin.cpp

    Main.cpp
)

add_library(PatternMaker SHARED ${SRC})
target_compile_definitions(PatternMaker PRIVATE __IDP__ __X64__ __NT__ __VC__ UNICODE _UNICODE NO_OBSOLETE_FUNCS)
target_link_libraries(PatternMaker PUBLIC ida)

add_library(PatternMaker64 SHARED ${SRC})
target_compile_definitions(PatternMaker64 PRIVATE __IDP__ __X64__ __NT__ __VC__ UNICODE _UNICODE NO_OBSOLETE_FUNCS)
target_compile_definitions(PatternMaker64 PRIVATE __EA64__)
target_link_libraries(PatternMaker64 PUBLIC ida64)
