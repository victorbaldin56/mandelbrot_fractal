cmake_minimum_required(VERSION 3.25)
project(mandelbrot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_GENERATOR "Ninja")

set(CMAKE_CXX_FLAGS "-mavx2 -std=c++17 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations\
                    -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual\
                    -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy\
                    -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security\
                    -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor\
                    -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self\
                    -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel\
                    -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods\
                    -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum\
                    -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros\
                    -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing\
                    -Wno-old-style-cast -Wno-varargs -Wstack-protector -fstrict-overflow\
                    -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE ")

if (${DEBUG})                
    string(APPEND CMAKE_CXX_FLAGS "-fcheck-new\
                    -fsized-deallocation -fstack-check -fstack-protector\
-O0 -D _DEBUG -ggdb3 -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,leak,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr")
else ()
    string(APPEND CMAKE_CXX_FLAGS "-DNDEBUG ")
endif ()

if (${O0})
    string(APPEND CMAKE_CXX_FLAGS "-O0")
endif ()
    
if (${O3})
    string(APPEND CMAKE_CXX_FLAGS "-O3")
endif ()

if (${Ofast})
    string(APPEND CMAKE_CXX_FLAGS "-Ofast -march=native")
endif()

add_executable(mandelbrot src/main.cpp src/plot.cpp src/mandelbrot_dumb.cpp src/mandelbrot_avx.cpp)
target_link_libraries(mandelbrot sfml-graphics sfml-window sfml-system)
