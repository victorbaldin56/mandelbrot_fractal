cmake_minimum_required(VERSION 3.25)
project(mandelbrot)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -mavx2 -std=c++17 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations\
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
                    -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -D _DEBUG\
                    -ggdb3 -fsanitize=address,undefined")

set(CMAKE_CXX_FLAGS_RELEASE "-D NDEBUG -Ofast -march=native -mavx2 -std=c++17 -Wall")

add_executable(mandelbrot src/main.cpp src/plot.cpp src/mandelbrot_dumb.cpp src/mandelbrot_avx.cpp
               src/performance_test.cpp)
target_link_libraries(mandelbrot sfml-graphics sfml-window sfml-system fontconfig)
